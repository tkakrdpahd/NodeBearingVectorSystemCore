/* LinerSegment.cpp
 * Implementation of the LinerSegment class
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 9, 2024
 * 
 * Equations
 * Equ(1): R_i = R_z(\theta_i) R_y(\phi_i)
 * Equ(2): R_z(\theta_i) = \begin{pmatrix}
 * \cos{\theta_i} & -\sin{\theta_i} & 0 \\
 * \sin{\theta_i} & \cos{\theta_i} & 0 \\
 * 0 & 0 & 1 \\
 * \end{pmatrix}
 * Equ(3): R_y(\phi_i) = \begin{pmatrix}
 * \cos{\phi_i} & 0 & \sin{\phi_i} \\
 * 0 & 1 & 0 \\
 * -\sin{\phi_i} & 0 & \cos{\phi_i} \\
 * \end{pmatrix}
 * Equ(4): \vec{V}_{\text{total}, s} = \sum_{i=1}^{D_s} d_{s,i} \cdot \left( \vec{B}_i \otimes \vec{F}_i \right)
 * Equ(5): \vec{P}_{\text{final}, s} = \vec{N}_{\text{Cartesian}} + \vec{V}_{\text{total}, s}
 * Equ(6): L_{d,\text{in}} = L_{\text{min}} + \left(L_{\text{max}} - L_{\text{min}}\right) \cdot |\vec{B}_{d,\text{in}}|
 * Equ(7): L_{d,\text{out}} = L_{\text{min}} + \left(L_{\text{max}} - L_{\text{min}}\right) \cdot |\vec{B}_{d,\text{out}}|
 * Equ(8): \vec{B}(t) = \sum_{i=0}^{n} \binom{n}{i} (1 - t)^{n - i} t^i \vec{P}_i, \quad 0 \leq t \leq 1
 * Equ(9): \vec{P}_0 = \vec{N}_1
 * Equ(10): \vec{P}_i = \vec{N}_1 + \vec{C}_{1,i}, \quad 1 \leq i \leq D_1
 * Equ(11): \vec{P}_{D_1+1} = \alpha \left( \vec{N}_1 + \vec{C}_{1,D_1} \right) + (1 - \alpha) \left( \vec{N}_2 - \vec{C}_{2,D_2} \right)
 * Equ(12): \vec{P}_{D_1+1+j} = \vec{N}_2 - \vec{C}_{2,D_2 - j + 1}, \quad 1 \leq j \leq D_2
 * Equ(13): \vec{P}_n = \vec{N}_2
 * Equ(14): \kappa(t) = \frac{|\vec{B}^{\prime\prime}(t) \times \vec{B}^\prime(t)|}{|\vec{B}^\prime(t)|^3}
 */

#include "LinerSegment.h"
#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"

// Sample Bezier curve based on the input nodes and bearing vectors
void LinerSegment::SamplingBezierCurve() {
    // Number of samples for Bezier curve
    const int sampleCount = 100;
    std::vector<Vector3> sampledPoints;

    // Calculate control points for Bezier curve based on provided equations
    std::vector<Vector3> controlPoints;
    controlPoints.push_back(_startNode.vector);

    // Calculate internal control points based on start node bearing vectors (Equations 10 and 11)
    for (int i = 0; i < _startNodeBearingVectors.size(); ++i) {
        controlPoints.push_back(_startNode.vector + _startNodeBearingVectors[i].vector);
    }

    // Intermediate control point between start and end nodes (Equation 11)
    Vector3 P_D1_plus_1 = (_startNode.vector + _startNodeBearingVectors.back().vector) * 0.5 +
                          (_endNode.vector - _endNodeBearingVectors.back().vector) * 0.5;
    controlPoints.push_back(P_D1_plus_1);

    // Control points based on end node bearing vectors (Equations 12 and 13)
    for (int j = 0; j < _endNodeBearingVectors.size(); ++j) {
        controlPoints.push_back(_endNode.vector - _endNodeBearingVectors[_endNodeBearingVectors.size() - j - 1].vector);
    }

    controlPoints.push_back(_endNode.vector);

    // Sample Bezier curve points based on control points (Equation 8)
    for (int i = 0; i <= sampleCount; ++i) {
        double t = static_cast<double>(i) / sampleCount;
        Vector3 point(0.0, 0.0, 0.0);
        int n = controlPoints.size() - 1;

        // Bernstein basis polynomial and control points multiplication
        for (int j = 0; j <= n; ++j) {
            double bernstein = std::pow(1 - t, n - j) * std::pow(t, j) * 
                               (std::tgamma(n + 1) / (std::tgamma(j + 1) * std::tgamma(n - j + 1)));
            point = point + controlPoints[j] * bernstein;
        }
        sampledPoints.push_back(point);
    }

    // Display sampled points
    for (const auto& point : sampledPoints) {
        std::cout << "Sampled Point: " << point << std::endl;
    }
}

// Sample vertex points based on Level of Detail (LOD)
void LinerSegment::SamplingVertex() {
    // Placeholder for LOD calculation and vertex sampling
    std::cout << "Sampling vertices based on LOD" << std::endl;
    // Implementation will depend on LOD parameters and specific requirements
}
