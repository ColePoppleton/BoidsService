#ifndef BOIDSSERVICE_BOIDSSYSTEM_H
#define BOIDSSERVICE_BOIDSSYSTEM_H

#include <QVector3D>
#include <QList>

namespace BoidsService {

    struct Boid {
        QVector3D position;
        QVector3D velocity;
    };

    class BoidsSystem {
    public:
        BoidsSystem(int numBoids, float sphereRadius);
        ~BoidsSystem();

        void update(float deltaTime);
        const QList<Boid>& getBoids() const;

        // Weights
        void setAlignmentWeight(float weight);
        float getAlignmentWeight() const;
        void setCohesionWeight(float weight);
        float getCohesionWeight() const;
        void setSeparationWeight(float weight);
        float getSeparationWeight() const;

        // Radii
        void setAlignmentRadius(float radius);
        float getAlignmentRadius() const;
        void setCohesionRadius(float radius);
        float getCohesionRadius() const;
        void setSeparationRadius(float radius);
        float getSeparationRadius() const;

        // Velocity
        void setMaxVelocity(float velocity);
        float getMaxVelocity() const;

    private:
        QList<Boid> boids;
        float radius;
        float maxVelocity = 10.0f;

        float alignmentWeight = 1.0f;
        float cohesionWeight = 1.0f;
        float separationWeight = 1.0f;

        float alignmentRadius = 50.0f;
        float cohesionRadius = 50.0f;
        float separationRadius = 25.0f;

        QVector3D sphericalToCartesian(float latitude, float longitude) const;
        void applyRules(Boid& boid, const QList<Boid>& otherBoids);
    };

}

#endif