/**
 * LinerSegment.h
 * Linked file: LinerSegment.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 9, 2024
 * Last Modified: Nov 11, 2024
 * 
 * Purpose: 
 * 1. Create B-Spline line
 * 2. Create Polygon Vertex based on LOD
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

#ifndef LINERSEGMENT_H
#define LINERSEGMENT_H

#include <vector>

#include "CoordinateConverter.h"
#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"

class LinerSegment
{
private:
    std::shared_ptr<std::vector<Vector3>> _linerSegmentCache;
public:
    LinerSegment(/* args */);
    ~LinerSegment();
};

#endif // LINERSEGMENT_H
