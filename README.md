# NodeBearingVectorSystem

NodeBearingVectorSystem is a modular and extensible library designed to handle vector-based computations, including basic 3D vector operations, node vector management, and bearing vector control.

## Components

### 1. **Vector3**
`Vector3` is the fundamental data structure for representing 3D vectors. It is used as the base component for `NodeVector` and `BearingVector`.

#### Properties:
- `float x, y, z`: Cartesian coordinates of the vector.

#### Constructor:
```cpp
Vector3(float x, float y, float z);
```

### 2. **NodeVector**
`NodeVector` acts similarly to a vertex, combining an index with a `Vector3` to represent a specific point in space.

#### Properties:
- `int index`: A unique identifier for the node.
- `Vector3 vec`: The vector representing the node's position.

#### Constructor:
```cpp
NodeVector(int index, const Vector3& vec);
```

### 3. **BearingVector**
`BearingVector` is used to define control points with additional forces and directional vectors.

#### Properties:
- `NodeVector node`: The associated node for the bearing vector.
- `Vector3 force`: The force vector applied to the node.
- `Vector3 vec`: The directional vector for the bearing.

#### Constructor:
```cpp
BearingVector(const NodeVector& node, const Vector3& force, const Vector3& vec);
```

## Managers
### ObjectManager
#### ERD
![ObjectManager ERD](./img/ObjectManagerERD.svg)

### SceneManager
#### ERD

### ServerManager
#### ERD

## Flow
### ERD

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
