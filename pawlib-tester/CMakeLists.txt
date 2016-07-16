# Specify the verison being used as well as the language.
cmake_minimum_required(VERSION 3.1)

#Name your project here
project("PawLIB Tester")

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
add_definitions(-Wall -Wextra)

# Set debug flags. -g is a default.
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ")
# Set release flags. -O3 is a default.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -fexpensive-optimizations")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../bin/$<CONFIG>")

include_directories(../cpgf/include)
include_directories(../pawlib-source/include)
include_directories(include)

add_executable(pawlib-tester
    main.cpp
    include/TestSystem.hpp
    src/TestSystem.cpp
)

target_link_libraries(pawlib-tester ${CMAKE_HOME_DIRECTORY}/../cpgf/lib/libcpgf.a)
target_link_libraries(pawlib-tester ${CMAKE_HOME_DIRECTORY}/../pawlib-source/lib/$<CONFIG>/libpawlib.a)
