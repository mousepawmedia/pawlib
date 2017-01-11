# Specify the verison being used as well as the language.
cmake_minimum_required(VERSION 3.1)

#Name your project here
project("PawLIB")

message("Using ${CONFIG_FILENAME}.config")
include(${CMAKE_HOME_DIRECTORY}/../${CONFIG_FILENAME}.config)

# Compiler and Version check...
# Allow GCC 5.x
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
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
# Allow Clang 3.4
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.4")
        message(FATAL_ERROR "Clang is too old. >= v3.4 required. Aborting build.")
    endif()
    set(COMPILERTYPE "clang")
    message("Clang 3.4 or later detected. Proceeding...")
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

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../lib/$<CONFIG>")

include_directories(../cpgf/include)
include_directories(include)

add_library(pawlib STATIC
    include/avl_tree.hpp
    include/base_flex_array.hpp
    include/binconv.hpp
    include/core_types.hpp
    include/core_types_tests.hpp
    include/flex_array.hpp
    include/flex_array_tests.hpp
    include/flex_map.hpp
    include/flex_queue.hpp
    include/flex_queue_tests.hpp
    include/flex_stack.hpp
    include/flex_stack_tests.hpp
    include/goldilocks.hpp
    include/iochannel.hpp
    include/onechar.hpp
    include/onestring.hpp
    include/onestringbase.hpp
    include/onestring_tests.hpp
    include/pawsort.hpp
    include/pawsort_tests.hpp
    include/pool.hpp
    include/pool_tests.hpp
    include/quickstring.hpp
    include/rigid_stack.hpp
    include/singly_linked_list.hpp
    include/stdutils.hpp
    include/flex_bit_tests.hpp
    include/flex_bit.hpp

    src/binconv.cpp
    src/core_types.cpp
    src/core_types_tests.cpp
    src/flex_array_tests.cpp
    src/flex_queue_tests.cpp
    src/flex_stack_tests.cpp
    src/flex_bit_tests.cpp
    src/goldilocks.cpp
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

target_link_libraries(pawlib ${CMAKE_HOME_DIRECTORY}/../cpgf/lib/libcpgf.a)
