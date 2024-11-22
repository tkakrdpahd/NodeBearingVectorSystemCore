/**
 * SurfaceSegment.h
 * Linked file: SurfaceSegment.cpp
 * Security: Confidential
 * Author: Minseok Doo
 * Date: Oct 7, 2024
 * Last Modified: Nov 11, 2024
 * 
 * Purpose of Class:
 * Purpose: Index buffer for LinearSegment and Surface
 * 
 * Equations:
 * Equ(1): \quad \overline{AB} = \sum_{i=1}^N ab_i' \\
 * Equ(2): \quad \overline{BC} = \sum_{i=1}^N bc_i' \\
 * Equ(3): \quad \overline{AC} = \sum_{i=1}^N ac_i' \\
 * Equ(4): \quad t_i = \frac{i}{N}, \quad i = 0, 1, 2, \dots, N \\
 * Equ(5): \quad P_{AB}(t_i) = A + t_i (B - A) \\
 * Equ(6): \quad P_{BC}(t_i) = B + t_i (C - B) \\
 * Equ(7): \quad P_{AC}(t_i) = A + t_i (C - A) \\
 * Equ(8): \quad L_{nn_i}(s) = P_{AB}(t_i) + s \big( P_{BC}(t_i) - P_{AB}(t_i) \big), \quad s \in [0, 1] \\
 * Equ(9): \quad L_{AC}(r) = A + r (C - A), \quad r \in [0, 1] \\
 * Equ(10): \quad P_{AB}(t_i) + s \big( P_{BC}(t_i) - P_{AB}(t_i) \big) = A + r (C - A)
 */

#ifndef SURFACESEGMENT_H
#define SURFACESEGMENT_H

#include <vector>
#include <memory>

#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"

class SurfaceSegment
{
private:
    /* data */
public:
    SurfaceSegment(/* args */);
    ~SurfaceSegment();
};

#endif // SURFACESEGMENT_H