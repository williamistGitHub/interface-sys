cmake_minimum_required(VERSION 3.1)
project(
    CInterfaceSys
    VERSION 1.0.1
    DESCRIPTION "A dynamic library interface system for C99."
    HOMEPAGE_URL "https://www.github.com/williamistGitHub/interface-sys"
    LANGUAGES C CXX
)
set(CMAKE_C_STANDARD 99)

option(BUILD_EXAMPLES "Build interface system example project(s)" OFF)
option(_ISYS_DEBUG "Build debugging print statements into the library. Not intended for users." OFF)

include_directories(include)

# Interface system static library
file(GLOB_RECURSE LIB_SRC src/*.c)
file(GLOB_RECURSE LIB_HDR include/*.h)
add_library(interface_sys STATIC ${LIB_SRC} ${LIB_HDR})
target_include_directories(interface_sys PUBLIC include)
set_property(TARGET interface_sys PROPERTY POSITION_INDEPENDENT_CODE ON)
add_compile_definitions(ISYS_DEBUG=${_ISYS_DEBUG})

# Tests
# We dont build tests by default, since that would be bad for users of the library
option(BUILD_TESTING "Build tests for the interface system" OFF)
include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

# I want to eventually move this into multiple CMakeLists.txt files in each example's folder, but for now, this works.
if(${BUILD_EXAMPLES})

    # Basic example
    file(GLOB_RECURSE EXAMPLE_BASIC_HDR examples/basic/include/*.h)

    file(GLOB_RECURSE EXAMPLE_BASIC_DLL_SRC examples/basic/dll/src/*.c)
    add_library(example_basic_dll SHARED ${EXAMPLE_BASIC_DLL_SRC} ${EXAMPLE_BASIC_HDR})
    target_include_directories(example_basic_dll PRIVATE examples/basic/include) # include shared headers
    target_link_libraries(example_basic_dll interface_sys) # link interface system

    file(GLOB_RECURSE EXAMPLE_BASIC_EXE_SRC examples/basic/exe/src/*.c)
    add_executable(example_basic_exe ${EXAMPLE_BASIC_EXE_SRC}  ${EXAMPLE_BASIC_HDR})
    target_include_directories(example_basic_exe PRIVATE examples/basic/include) # include shared headers
    target_link_libraries(example_basic_exe interface_sys) # link interface system
    add_dependencies(example_basic_exe example_basic_dll) # tell cmake that the exe needs the dll without linking (its done dynamically)

endif()