# NodeBearingVectorSystem

NodeBearingVectorSystem is a modular and extensible library designed to handle vector-based computations, including basic 3D vector operations, node vector management, and bearing vector control.

## License
This project is dual-licensed under the following terms:

### 1. **GNU General Public License v3.0 (GPL 3.0)**
- Redistribution and modification are permitted under the terms of the GPL 3.0, as published by the Free Software Foundation.
- A copy of the GPL 3.0 license is included in `LICENSE-GPLv3.txt`.

### 2. **Commercial License**
- For commercial use, you must obtain a commercial license.
- Details of the commercial license are included in `LICENSE-Commercial.txt`.

For further licensing inquiries, please contact us directly.

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
