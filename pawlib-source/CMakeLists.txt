# Specify the verison being used.
cmake_minimum_required(VERSION 3.1)

#Name your project here
project("PawLIB")
set(TARGET_NAME "pawlib")

message("Using ${CONFIG_FILENAME}.config")
include(${CMAKE_HOME_DIRECTORY}/../${CONFIG_FILENAME}.config)

# Compiler and Version check...
# Allow Clang 3.4
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.4")
        message(FATAL_ERROR "Clang is too old. >= v3.4 required. Aborting build.")
    endif()
    set(COMPILERTYPE "clang")
    message("Clang 3.4 or later detected. Proceeding...")
# Allow GCC 5.x
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5")
        message(FATAL_ERROR "GCC is too old. >= v5.x required. Aborting build.")
    endif()
    set(COMPILERTYPE "gcc")
    message("GCC 5.x or later detected. Proceeding...")
# Allow compilers that simulate GCC 5.x.
elseif(CMAKE_CXX_SIMULATE_ID STREQUAL "GNU")
    if(CMAKE_CXX_SIMULATE_VERSION VERSION_LESS "5")
        message(FATAL_ERROR "Not simulating GCC 5.x. Aborting build.")
    endif()
    set(COMPILERTYPE "gcc")
    message("GCC (5.x or later) simulation detected. Proceeding...")
else()
    message(FATAL_ERROR "Not using or simulating a compatible compiler (minimum GCC 5.x, Clang 3.4). Other compilers are not yet supported. Aborting build.")
endif()

# Target C++14
set(CMAKE_CXX_STANDARD 14)
# Disable extensions (turns gnu++14 to c++14)
set(CMAKE_CXX_EXTENSIONS OFF)

# Target 32-bit or 64-bit, based on ARCH variable.
if(ARCH EQUAL 32)
    message("Triggered 32-bit build (-m32).")
    add_definitions(-m32)
elseif(ARCH EQUAL 64)
    message("Triggered 64-bit build (-m64).")
    add_definitions(-m64)
# If 32-bit or 64-bit wasn't specified, just use the default.
elseif(NOT ARCH)
    message("Building for default architecture.")
else()
    message(FATAL_ERROR "Invalid architecture (${ARCH}) specified. Aborting build.")
endif()

# Our global compiler flags.
add_definitions(-Wall -Wextra -Werror)

if(COMPILERTYPE STREQUAL "gcc")
    # TODO: This is necessary for GCC 7.0 and onward
    # TEMPORARY until C++17 (https://dzone.com/articles/implicit-fallthrough-in-gcc-7)
    add_definitions(-Wimplicit-fallthrough=0)

    # Set debug flags. -g is a default.
    #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ")
    # Set release flags. -O3 is a default.
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -fexpensive-optimizations")
elseif(COMPILERTYPE STREQUAL "clang")
    # Use libc++ if requested.
    if(LLVM)
        add_definitions(-stdlib=libc++)
        message("Using LLVM libc++...")
    endif()
    # Set debug flags. -g is a default.
    #set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ")
    # Set release flags. -O3 is a default.
    #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ")
endif()

if(LD)
    message("Using ${LD} linker...")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=${LD}")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../lib/$<CONFIG>")

include_directories(include)

# Include headers of dependencies.
include_directories(${CPGF_DIR}/include)

add_library(${TARGET_NAME} STATIC
    include/pawlib/avl_tree.hpp
    include/pawlib/base_flex_array.hpp
    include/pawlib/binconv.hpp
    include/pawlib/core_types.hpp
    include/pawlib/core_types_tests.hpp
    include/pawlib/flex_array.hpp
    include/pawlib/flex_array_tests.hpp
    include/pawlib/flex_bit_tests.hpp
    include/pawlib/flex_bit.hpp
    include/pawlib/flex_map.hpp
    include/pawlib/flex_queue.hpp
    include/pawlib/flex_queue_tests.hpp
    include/pawlib/flex_stack.hpp
    include/pawlib/flex_stack_tests.hpp
    include/pawlib/goldilocks.hpp
    include/pawlib/goldilocks_shell.hpp
    include/pawlib/iochannel.hpp
    include/pawlib/onechar.hpp
    include/pawlib/onestring.hpp
    include/pawlib/onestringbase.hpp
    include/pawlib/onestring_tests.hpp
    include/pawlib/pawsort.hpp
    include/pawlib/pawsort_tests.hpp
    include/pawlib/pool.hpp
    include/pawlib/pool_tests.hpp
    include/pawlib/quickstring.hpp
    include/pawlib/rigid_stack.hpp
    include/pawlib/singly_linked_list.hpp
    include/pawlib/stdutils.hpp

    src/binconv.cpp
    src/core_types.cpp
    src/core_types_tests.cpp
    src/flex_array_tests.cpp
    src/flex_bit_tests.cpp
    src/flex_queue_tests.cpp
    src/flex_stack_tests.cpp
    src/goldilocks.cpp
    src/goldilocks_shell.cpp
    src/iochannel.cpp
    src/onechar.cpp
    src/onestring.cpp
    src/onestringbase.cpp
    src/onestring_tests.cpp
    src/pawsort_tests.cpp
    src/pool_tests.cpp
    src/quickstring.cpp
    src/stdutils.cpp

)

# Link against dependencies.
target_link_libraries(${TARGET_NAME} ${CPGF_DIR}/lib/libcpgf.a)

if(COMPILERTYPE STREQUAL "clang")
    if(SAN STREQUAL "address")
        add_definitions(-O1 -fsanitize=address -fno-optimize-sibling-calls -fno-omit-frame-pointer)
        set_property(TARGET ${TARGET_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -fsanitize=address")
        message("Compiling with AddressSanitizer.")
    elseif(SAN STREQUAL "leak")
        add_definitions(-fsanitize=leak)
        set_property(TARGET ${TARGET_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -fsanitize=leak")
        message("Compiling with LeakSanitizer.")
    elseif(SAN STREQUAL "memory")
        if(LLVM)
            add_definitions(-O1 -fsanitize=memory -fno-optimize-sibling-calls -fno-omit-frame-pointer -fsanitize-memory-track-origins)
            set_property(TARGET ${TARGET_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -fsanitize=memory")
            message("Compiling with MemorySanitizer.")
        else()
            message("Skipping MemorySanitizer: requires libc++")
        endif()
    elseif(SAN STREQUAL "thread")
        add_definitions(-O1 -fsanitize=thread)
        set_property(TARGET ${TARGET_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -fsanitize=thread")
        message("Compiling with ThreadSanitizer.")
    elseif(SAN STREQUAL "undefined")
        add_definitions(-fsanitize=undefined)
        set_property(TARGET ${TARGET_NAME} APPEND_STRING PROPERTY LINK_FLAGS " -fsanitize=undefined")
        message("Compiling with UndefiniedBehaviorSanitizer.")
    endif()
endif()
