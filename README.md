# interface-sys

interface-sys is a C99 library for declaring interfaces that allow multiple dynamically loaded libraries and executables to communicate with each other, inspired by Valve Software's source engine.

## Usage

The system is built using CMake, for easy inclusion in any CMake-based project.

Here is an example `CMakeLists.txt` file for including it in your project:

```cmake
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable was added in cmake 3.14
project(YourProject)

include(FetchContent)

# disable building examples, dont need that for a project
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# declare and import interface sys
FetchContent_Declare(
    interface-sys
    GIT_REPOSITORY https://github.com/williamistGitHub/interface-sys.git
    GIT_TAG v1.0.0
)

FetchContent_MakeAvailable(interface-sys)

# your app code goes here
add_executable(YourProject)
target_sources(YourProject PRIVATE app.c)
target_link_libraries(YourProject PRIVATE interface-sys)
```

Look at the [examples](https://github.com/williamistGitHub/interface-sys/tree/main/examples) for how to use the library in code.

## Contributing

Found an issue with the library? Make an issue or pull request!
