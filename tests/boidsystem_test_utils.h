#ifndef BOIDSSERVICE_TEST_UTILS_H
#define BOIDSSERVICE_TEST_UTILS_H

#include <iostream>
#include <QtMath>
#include <QVector3D>

namespace BoidsService {
    namespace Tests {

        bool compareVectors(const QVector3D& v1, const QVector3D& v2, float tolerance);
        void reportTestResult(const std::string& testName, bool passed);

    } // namespace Tests
} // namespace BoidsService

#endif // BOIDSSERVICE_TEST_UTILS_H