#include "./BoidsService/BoidsSystem.h"
#include <cstdlib>
#include <ctime>
#include <QtMath>
#include <algorithm>

namespace BoidsService {

    BoidsSystem::BoidsSystem(int numBoids, float sphereRadius) : radius(sphereRadius) {
        if(radius <= 0.0f){
            radius = 1.0f;
        }
        srand(time(0));
        for (int i = 0; i < numBoids; ++i) {
            Boid boid;
            float latitude = (rand() % 180) * M_PI / 180.0f;
            float longitude = (rand() % 360) * M_PI / 180.0f;
            boid.position = sphericalToCartesian(latitude, longitude);
            boid.velocity = QVector3D((rand() % 20) - 10, (rand() % 20) - 10, (rand() % 20) - 10);
            boids.append(boid);
        }
    }

    BoidsSystem::~BoidsSystem() {}

    void BoidsSystem::update(float deltaTime) {
        for (Boid& boid : boids) {
            applyRules(boid, boids);
            boid.position += boid.velocity * deltaTime;
            boid.position.normalize();
            boid.position *= radius;
            boid.velocity = boid.velocity.normalized() * std::clamp(boid.velocity.length(), 0.0f, maxVelocity);

        }
    }

    const QList<Boid>& BoidsSystem::getBoids() const {
        return boids;
    }

    void BoidsSystem::setAlignmentWeight(float weight) {
        alignmentWeight = std::clamp(weight, 0.0f, 10.0f);
    }

    float BoidsSystem::getAlignmentWeight() const{
        return alignmentWeight;
    }

    void BoidsSystem::setCohesionWeight(float weight) {
        cohesionWeight = std::clamp(weight, 0.0f, 10.0f);
    }

    float BoidsSystem::getCohesionWeight() const{
        return cohesionWeight;
    }

    void BoidsSystem::setSeparationWeight(float weight) {
        separationWeight = std::clamp(weight, 0.0f, 10.0f);
    }

    float BoidsSystem::getSeparationWeight() const{
        return separationWeight;
    }

    void BoidsSystem::setAlignmentRadius(float radius) {
        alignmentRadius = std::max(radius, 0.0f);
    }

    float BoidsSystem::getAlignmentRadius() const{
        return alignmentRadius;
    }

    void BoidsSystem::setCohesionRadius(float radius) {
        cohesionRadius = std::max(radius, 0.0f);
    }

    float BoidsSystem::getCohesionRadius() const{
        return cohesionRadius;
    }

    void BoidsSystem::setSeparationRadius(float radius) {
        separationRadius = std::max(radius, 0.0f);
    }

    float BoidsSystem::getSeparationRadius() const{
        return separationRadius;
    }

    void BoidsSystem::setMaxVelocity(float velocity){
        maxVelocity = std::max(0.0f, velocity);
    }

    float BoidsSystem::getMaxVelocity() const{
        return maxVelocity;
    }

    QVector3D BoidsSystem::sphericalToCartesian(float latitude, float longitude) const {
        float x = radius * qCos(latitude) * qCos(longitude);
        float y = radius * qCos(latitude) * qSin(longitude);
        float z = radius * qSin(latitude);
        return QVector3D(x, y, z);
    }

    void BoidsSystem::applyRules(Boid& boid, const QList<Boid>& otherBoids) {
        QVector3D alignment(0, 0, 0);
        QVector3D cohesion(0, 0, 0);
        QVector3D separation(0, 0, 0);

        int alignmentCount = 0;
        int cohesionCount = 0;
        int separationCount = 0;

        for (const Boid& otherBoid : otherBoids) {
            if (&boid == &otherBoid) continue;

            float distance = (boid.position - otherBoid.position).length();

            // Alignment
            if (distance < alignmentRadius) {
                alignment += otherBoid.velocity;
                alignmentCount++;
            }

            // Cohesion
            if (distance < cohesionRadius) {
                cohesion += otherBoid.position;
                cohesionCount++;
            }

            // Separation
            if (distance < separationRadius) {
                QVector3D diff = boid.position - otherBoid.position;
                if (distance > 0) {
                    separation += diff.normalized() / distance;
                }
                separationCount++;
            }
        }

        if (alignmentCount > 0) {
            alignment = (alignment / alignmentCount).normalized() * alignmentWeight;
        }

        if (cohesionCount > 0) {
            cohesion = ((cohesion / cohesionCount) - boid.position).normalized() * cohesionWeight;
        }

        if (separationCount > 0) {
            separation = (separation / separationCount).normalized() * separationWeight;
        }

        boid.velocity += alignment + cohesion + separation;
        boid.velocity.normalize();
    }

}