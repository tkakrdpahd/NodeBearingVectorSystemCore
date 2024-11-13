/** 
 * Vector3.h
 * Security: Confidential
 * Author: Minseok Doo
 * Created Date: Oct 24, 2024
 * Last Modified: Nov 13, 2024
 */

#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>  // Required for the sqrt() function

// Simple Vector3 struct using an internal array
struct Vector3 {
    union {
        float values[3];  // Internal storage as an array
        struct {          // Retains x, y, z members
            float x, y, z;
        };
    };

    // Constructor with default values
    Vector3(float xVal = 0, float yVal = 0, float zVal = 0) {
        values[0] = xVal;  // x
        values[1] = yVal;  // y
        values[2] = zVal;  // z
    }

    // Vector addition
    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    // Vector subtraction
    Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    // Scalar multiplication (Vector3 * float)
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // Scalar division
    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // Dot product
    float dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // Cross product
    Vector3 cross(const Vector3& v) const {
        return Vector3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    // Vector magnitude
    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Friend function for scalar multiplication (float * Vector3)
    friend Vector3 operator*(float scalar, const Vector3& v) {
        return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
    }

    // Access individual elements via operator[]
    float operator[](int index) const {
        return values[index];
    }

    float& operator[](int index) {
        return values[index];
    }
};

#endif // VECTOR3_H