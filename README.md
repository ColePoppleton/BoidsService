# BoidsService Library

[![CMake](https://github.com/ColePoppleton/BoidsService/actions/workflows/cmake.yml/badge.svg)](https://github.com/ColePoppleton/BoidsService/actions/workflows/cmake.yml)

This C++ library implements a Boids system, a model for simulating flocking behavior often used in computer graphics and simulations. This specific implementation is designed as a foundational component for a larger system simulating marine life migratory patterns, particularly in conjunction with neural network predictions and environmental data.  It uses Qt for vector math.

## Overview

The `BoidsService` library provides a `BoidsSystem` class that manages a collection of `Boid` objects. The system simulates the movement of these boids based on the classic Boids rules: alignment, cohesion, and separation. This library offers the flexibility to adjust the weights and radii associated with each rule, allowing for fine-tuning of the flocking behavior. The simulation takes place on the surface of a sphere.

## Features

*   **Boids Simulation:** Implements the core Boids rules for simulating flocking behavior.
*   **Spherical Movement:** Constrains boid movement to the surface of a sphere.
*   **Configurable Parameters:** Allows adjustment of alignment, cohesion, and separation weights and radii.
*   **Qt Dependency:** Uses Qt's `QVector3D` for vector calculations.
*   **CMake Build System:** Easy to integrate into existing projects using CMake.
*   **Unit Tests:** Includes unit tests to ensure the correctness of the Boids system.

## Getting Started

### Prerequisites

*   CMake (version 3.20 or higher)
*   C++ compiler with C++20 support
*   Qt 6.9.0

### Building the Library

1.  **Clone the repository:**

    ```bash
    git clone https://github.com/ColePoppleton/BoidsService.git
    cd BoidsService
    ```

2.  **Create a build directory:**

    ```bash
    mkdir build
    cd build
    ```

3.  **Configure the project with CMake:**

    *   **Important:** Adjust the `Qt6_DIR` variable to point to your Qt installation directory.

    ```bash
    cmake -DQt6_DIR="C:/Qt/6.9.0/mingw_64/lib/cmake/Qt6" ..
    ```

    *   Replace `"C:/Qt/6.9.0/mingw_64/lib/cmake/Qt6"` with the correct path to your Qt installation. This path will vary based on your OS and Qt version. On Linux, it might be `/opt/Qt/6.9.0/gcc_64/lib/cmake/Qt6` or similar. On macOS, it could be something like `/Users/yourusername/Qt/6.9.0/macos/lib/cmake/Qt6`.  Use Qt Maintenance Tool to verify the exact path.

4.  **Build the library:**

    ```bash
    cmake --build .
    ```

5.  **Install the library (optional):**

    ```bash
    cmake --install .
    ```

### Using the Library in Your Project

1.  **Include the `BoidsService` header file:**

    ```c++
    #include <BoidsService/BoidsSystem.h>
    ```

2.  **Link against the `BoidsService` library in your CMakeLists.txt:**

    ```cmake
    find_package(BoidsService REQUIRED)
    target_link_libraries(your_target BoidsService::BoidsService)
    ```

## Testing
The library includes unit tests built with CMake. To run the tests, execute the following commands in the build directory:

```bash
cmake --build . --target boidsystem_tests
./boidsystem_tests
```
Use code with caution.

## Contributing
Contributions are not welcome! This is a repository for a final year dissertation, it will be opened to contributions in July 2026.

License
This project is licensed under the MIT License.
