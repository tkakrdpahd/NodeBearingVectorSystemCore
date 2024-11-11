/**
 * main.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 11, 2024
 */

#include <iostream>
#include "Vector3.h"

int main() {
    // Create two Vector3 instances for testing
    Vector3 v1(3.0f, 4.0f, 5.0f);
    Vector3 v2(1.0f, 2.0f, 3.0f);

    // Test vector addition
    Vector3 v_add = v1 + v2;
    std::cout << "v1 + v2 = (" << v_add.x << ", " << v_add.y << ", " << v_add.z << ")\n";

    // Test vector subtraction
    Vector3 v_sub = v1 - v2;
    std::cout << "v1 - v2 = (" << v_sub.x << ", " << v_sub.y << ", " << v_sub.z << ")\n";

    // Test scalar multiplication
    Vector3 v_mul = v1 * 2.0f;
    std::cout << "v1 * 2.0 = (" << v_mul.x << ", " << v_mul.y << ", " << v_mul.z << ")\n";

    // Test scalar division
    Vector3 v_div = v1 / 2.0f;
    std::cout << "v1 / 2.0 = (" << v_div.x << ", " << v_div.y << ", " << v_div.z << ")\n";

    // Test dot product
    float dot_product = v1.dot(v2);
    std::cout << "v1 . v2 = " << dot_product << "\n";

    // Test cross product
    Vector3 v_cross = v1.cross(v2);
    std::cout << "v1 x v2 = (" << v_cross.x << ", " << v_cross.y << ", " << v_cross.z << ")\n";

    // Test magnitude
    float v1_magnitude = v1.magnitude();
    std::cout << "|v1| = " << v1_magnitude << "\n";

    // Test element access using operator[]
    std::cout << "v1[0] = " << v1[0] << ", v1[1] = " << v1[1] << ", v1[2] = " << v1[2] << "\n";

    return 0;
}
