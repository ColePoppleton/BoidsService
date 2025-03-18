#include "boidsystem_test_utils.h"

namespace BoidsService {
    namespace Tests {

        bool compareVectors(const QVector3D& v1, const QVector3D& v2, float tolerance) {
            return qFuzzyCompare(v1.x(), v2.x()) &&
                   qFuzzyCompare(v1.y(), v2.y()) &&
                   qFuzzyCompare(v1.z(), v2.z());
        }

        void reportTestResult(const std::string& testName, bool passed) {
            std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
        }

    } // namespace Tests
} // namespace BoidsService