#include "boidsystem_test_utils.h"
#include <cstdlib>
#include <ctime>
#include "BoidsService/BoidsSystem.h"

using namespace BoidsService;
using namespace BoidsService::Tests;

int main() {
    srand(time(0));

    // --- Unit Tests ---

    // Test: BoidsSystem Initialization
    {
        std::string testName = "BoidsSystem Initialization";
        BoidsSystem boidsSystem(10, 100.0f);
        bool passed = (boidsSystem.getBoids().size() == 10);
        reportTestResult(testName, passed);
    }

    // Test: Boid Structure
    {
        std::string testName = "Boid Structure";
        BoidsSystem boidsSystem(1, 100.0f);
        Boid boid = boidsSystem.getBoids()[0];
        bool passed = true;
        if (boid.position.x() == 0 && boid.position.y() == 0 && boid.position.z() == 0) passed = false;
        if (boid.velocity.x() == 0 && boid.velocity.y() == 0 && boid.velocity.z() == 0) passed = false;
        reportTestResult(testName, passed);
    }

    // Test: Spherical Mapping
    {
        std::string testName = "Spherical Mapping";
        BoidsSystem boidsSystem(1, 100.0f);
        Boid boid = boidsSystem.getBoids()[0];
        bool passed = qFuzzyCompare(boid.position.length(), 100.0f);
        reportTestResult(testName, passed);
    }

    // Test: Setters and Getters
    {
        std::string testName = "Setters and Getters";
        BoidsSystem boidsSystem(1, 100.0f);
        boidsSystem.setAlignmentWeight(0.5f);
        boidsSystem.setCohesionWeight(0.75f);
        boidsSystem.setSeparationWeight(1.25f);
        boidsSystem.setAlignmentRadius(20.0f);
        boidsSystem.setCohesionRadius(30.0f);
        boidsSystem.setSeparationRadius(10.0f);
        boidsSystem.setMaxVelocity(15.0f);

        bool passed = qFuzzyCompare(boidsSystem.getAlignmentWeight(), 0.5f) &&
                      qFuzzyCompare(boidsSystem.getCohesionWeight(), 0.75f) &&
                      qFuzzyCompare(boidsSystem.getSeparationWeight(), 1.25f) &&
                      qFuzzyCompare(boidsSystem.getAlignmentRadius(), 20.0f) &&
                      qFuzzyCompare(boidsSystem.getCohesionRadius(), 30.0f) &&
                      qFuzzyCompare(boidsSystem.getSeparationRadius(), 10.0f) &&
                      qFuzzyCompare(boidsSystem.getMaxVelocity(), 15.0f);
        reportTestResult(testName, passed);
    }

    // --- Integration Tests ---

    // Test: Boids Update (Basic Movement)
    {
        std::string testName = "Boids Update (Basic Movement)";
        BoidsSystem boidsSystem(1, 100.0f);
        Boid initialBoid = boidsSystem.getBoids()[0];
        boidsSystem.update(1.0f);
        Boid updatedBoid = boidsSystem.getBoids()[0];
        bool passed = !compareVectors(initialBoid.position, updatedBoid.position, 0.001f);
        reportTestResult(testName, passed);
    }

    // Test: Boids Update (Boundary Handling)
    {
        std::string testName = "Boids Update (Boundary Handling)";
        BoidsSystem boidsSystem(1, 100.0f);
        Boid boid = boidsSystem.getBoids()[0];
        boid.position = QVector3D(1000.0f, 1000.0f, 1000.0f); // Force boid outside bounds
        boidsSystem.update(1.0f);
        boid = boidsSystem.getBoids()[0];
        bool passed = qFuzzyCompare(boid.position.length(), 100.0f); // Check if boid is back on the sphere
        reportTestResult(testName, passed);
    }

    // --- Functional Tests ---

    // Test: Boids Flock Behavior (Simplified)
    {
        std::string testName = "Boids Flock Behavior (Simplified)";
        BoidsSystem boidsSystem(10, 100.0f);
        boidsSystem.setAlignmentWeight(1.0f);
        boidsSystem.setCohesionWeight(1.0f);
        boidsSystem.setSeparationWeight(1.0f);
        QList<Boid> initialBoids = boidsSystem.getBoids();
        for (int i = 0; i < 10; ++i) {
            boidsSystem.update(0.1f);
        }
        QList<Boid> updatedBoids = boidsSystem.getBoids();

        // This is a very basic check; more sophisticated tests could be added
        float avgInitialX = 0, avgUpdatedX = 0;
        for (const Boid& boid : initialBoids) {
            avgInitialX += boid.position.x();
        }
        for (const Boid& boid : updatedBoids) {
            avgUpdatedX += boid.position.x();
        }
        avgInitialX /= initialBoids.size();
        avgUpdatedX /= updatedBoids.size();

        bool passed = !qFuzzyCompare(avgInitialX, avgUpdatedX); // Expect some movement
        reportTestResult(testName, passed);
    }

    return 0;
}