# Specify the verison being used as well as the language.
cmake_minimum_required(VERSION 3.1)

#Name your project here
project("PawLIB")

# Compiler and Version check...
# Allow GCC 5.x
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5")
        message(FATAL_ERROR "GCC is too old (<v5.x) required. Aborting build.")
    endif()
    message("GCC 5.x detected. Proceeding...")
# Allow compilers that simulate GCC 5.x.
elseif(CMAKE_CXX_SIMULATE_ID STREQUAL "GNU")
    if(CMAKE_CXX_SIMULATE_VERSION VERSION_LESS "5")
        message(FATAL_ERROR "Not simulating GCC 5.x. Aborting build.")
    endif()
    message("GCC 5.x simulation detected. Proceeding...")
else()
    message(FATAL_ERROR "Not using or simulating GCC. Other compilers are not yet supported. Aborting build.")
endif()

# Target C++14
set(CMAKE_CXX_STANDARD 14)
# Disable extensions (turns gnu++14 to c++14)
set(CMAKE_CXX_EXTENSIONS OFF)

# Our global compiler flags.
add_definitions(-Wall -Wextra -Werror)

# Set debug flags. -g is a default.
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ")
# Set release flags. -O3 is a default.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -fexpensive-optimizations")

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
