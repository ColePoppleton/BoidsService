cmake_minimum_required(VERSION 3.20)
project(BoidsService)
set(PROJECT_VERSION "1.0.0")

# Include the CMakePackageConfigHelpers module
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(Qt6_DIR "C:/Qt/6.9.0/mingw_64/lib/cmake/Qt6")
find_package(Qt6 COMPONENTS Gui REQUIRED)

include_directories(include)

add_library(BoidsService STATIC
        src/BoidsSystem.cpp
        include/BoidsService/BoidsSystem.h
        tests/boidsystem_test_utils.cpp
        tests/boidsystem_test_utils.h
)

target_link_libraries(BoidsService PRIVATE Qt6::Gui)
target_include_directories(BoidsService PUBLIC ${Qt6Gui_INCLUDE_DIRS})

set_target_properties(BoidsService PROPERTIES PUBLIC_HEADER "include/BoidsService/BoidsSystem.h")

add_executable(boidsystem_tests tests/boidsystem_tests.cpp tests/boidsystem_test_utils.cpp)
target_link_libraries(boidsystem_tests BoidsService Qt6::Gui)

# Install the library and headers
install(TARGETS BoidsService
        EXPORT BoidsServiceTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY include/BoidsService/ DESTINATION include)

# Create a CMake configuration file
install(EXPORT BoidsServiceTargets
        FILE BoidsServiceConfig.cmake
        NAMESPACE BoidsService::
        DESTINATION lib/cmake/BoidsService)

# Create a BoidsServiceConfigVersion.cmake file
write_basic_package_version_file(
        "${CMAKE_BINARY_DIR}/lib/cmake/BoidsService/BoidsServiceConfigVersion.cmake"
        VERSION "${PROJECT_VERSION}"
        COMPATIBILITY AnyNewerVersion
)

# Export the BoidsServiceConfigVersion.cmake file
install(FILES
        "${CMAKE_BINARY_DIR}/lib/cmake/BoidsService/BoidsServiceConfigVersion.cmake"
        DESTINATION lib/cmake/BoidsService
)
