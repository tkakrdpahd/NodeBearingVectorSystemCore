# NodeBearingVectorSystem

NodeBearingVectorSystem is a modular and extensible library designed to handle vector-based computations, including basic 3D vector operations, node vector management, and bearing vector control.

## Build and Test

### Prerequisites
- CMake (version 3.20 or higher)
- Ninja build system (optional but recommended)
- vcpkg for dependency management

### Building the Project
```bash
mkdir build
cd build
cmake -G Ninja ..
ninja
```

### Running the Program
After building, execute the program:
```bash
./NodeBearingVectorSystem
```

### Running Tests
Navigate to the `tests` directory and run the test executable:
```bash
cd tests
./test_nodebearingvectorsystem
```

### Dependencies
The project uses the following libraries:
- [Drogon](https://github.com/drogonframework/drogon) for API development.
- [nlohmann/json](https://github.com/nlohmann/json) for JSON parsing.
- [imgui](https://github.com/ocornut/imgui) for GUI elements.
- [SDL2](https://libsdl.org/) and [OpenGL](https://www.opengl.org/) for graphical support.
- [Vulkan](https://vulkan.lunarg.com/) for high-performance rendering.
- [GoogleTest](https://github.com/google/googletest) for unit testing.
