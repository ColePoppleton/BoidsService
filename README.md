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

## API Reference

### `BoidsSystem` Class

The main class for managing and simulating the Boids system.

```c++
namespace BoidsService {

class BoidsSystem {
public:
    /**
     * @brief Constructs a BoidsSystem object.
     *
     * @param numBoids The number of boids in the system.
     * @param sphereRadius The radius of the sphere on which the boids move.  Defaults to 1.0 if radius <= 0.
     */
    BoidsSystem(int numBoids, float sphereRadius);

    /**
     * @brief Destroys the BoidsSystem object.
     */
    ~BoidsSystem();

    /**
     * @brief Updates the boid positions based on the Boids rules.
     *
     * @param deltaTime The time elapsed since the last update (in seconds).
     */
    void update(float deltaTime);

    /**
     * @brief Returns the list of boids in the system.
     *
     * @return A const reference to the list of boids.
     */
    const QList<Boid>& getBoids() const;

    /**
     * @brief Sets the weight of the alignment rule.
     *
     * @param weight The alignment weight (clamped between 0.0 and 10.0).
     */
    void setAlignmentWeight(float weight);

    /**
     * @brief Gets the weight of the alignment rule.
     *
     * @return The alignment weight.
     */
    float getAlignmentWeight() const;

    /**
     * @brief Sets the weight of the cohesion rule.
     *
     * @param weight The cohesion weight (clamped between 0.0 and 10.0).
     */
    void setCohesionWeight(float weight);

    /**
     * @brief Gets the weight of the cohesion rule.
     *
     * @return The cohesion weight.
     */
    float getCohesionWeight() const;

    /**
     * @brief Sets the weight of the separation rule.
     *
     * @param weight The separation weight (clamped between 0.0 and 10.0).
     */
    void setSeparationWeight(float weight);

    /**
     * @brief Gets the weight of the separation rule.
     *
     * @return The separation weight.
     */
    float getSeparationWeight() const;

    /**
     * @brief Sets the radius for the alignment rule.
     *
     * @param radius The alignment radius (must be non-negative).
     */
    void setAlignmentRadius(float radius);

    /**
     * @brief Gets the radius for the alignment rule.
     *
     * @return The alignment radius.
     */
    float getAlignmentRadius() const;

    /**
     * @brief Sets the radius for the cohesion rule.
     *
     * @param radius The cohesion radius (must be non-negative).
     */
    void setCohesionRadius(float radius);

    /**
     * @brief Gets the radius for the cohesion rule.
     *
     * @return The cohesion radius.
     */
    float getCohesionRadius() const;

    /**
     * @brief Sets the radius for the separation rule.
     *
     * @param radius The separation radius (must be non-negative).
     */
    void setSeparationRadius(float radius);

    /**
     * @brief Gets the radius for the separation rule.
     *
     * @return The separation radius.
     */
    float getSeparationRadius() const;

    /**
     * @brief Sets the maximum velocity of the boids.
     *
     * @param velocity The maximum velocity (must be non-negative).
     */
    void setMaxVelocity(float velocity);

    /**
     * @brief Gets the maximum velocity of the boids.
     *
     * @return The maximum velocity.
     */
    float getMaxVelocity() const;

private:
    /**
     * @brief Converts spherical coordinates (latitude, longitude) to Cartesian coordinates.
     *
     * @param latitude The latitude in radians.
     * @param longitude The longitude in radians.
     * @return The Cartesian coordinates as a QVector3D.
     */
    QVector3D sphericalToCartesian(float latitude, float longitude) const;

    /**
     * @brief Applies the Boids rules to a single boid, considering its neighbors.
     *
     * @param boid The boid to update.
     * @param otherBoids The list of all other boids in the system.
     */
    void applyRules(Boid& boid, const QList<Boid>& otherBoids);

private:
    QList<Boid> boids;
    float radius;
    float alignmentWeight = 1.0f;
    float cohesionWeight = 1.0f;
    float separationWeight = 1.0f;
    float alignmentRadius = 1.0f;
    float cohesionRadius = 1.0f;
    float separationRadius = 1.0f;
    float maxVelocity = 5.0f;
};

} // namespace BoidsService
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
