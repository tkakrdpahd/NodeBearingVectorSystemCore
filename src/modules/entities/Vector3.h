/**
 * Vector3.h
 * Linked File: Vector3.cpp
 * Security: Confidential
 * Author: Minseok Doo
 * Created Date: Oct 24, 2024
 * Last Modified: Nov 18, 2024
 */

#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

// Json
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Vector3 {
public:
    union {
        float values[3]; // Internal storage as an array
        struct {
            float x, y, z; // Retain x, y, z members
        };
    };

    // JSON Serialization
    json toJson() const;
    static Vector3 fromJson(const json& j);

    // Default and parameterized constructor
    Vector3(float xVal = 0.0f, float yVal = 0.0f, float zVal = 0.0f);

    // Overloaded output operator
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);

    // Vector addition
    Vector3 operator+(const Vector3& v) const;
    Vector3& operator+=(const Vector3& v);

    // Vector subtraction
    Vector3 operator-(const Vector3& v) const;
    Vector3& operator-=(const Vector3& v);

    // Scalar multiplication (Vector3 * float)
    Vector3 operator*(float scalar) const;
    Vector3& operator*=(float scalar);

    // Hadamard product (Vector3 * Vector3)
    Vector3 operator*(const Vector3& v) const;

    // Scalar division
    Vector3 operator/(float scalar) const;
    Vector3& operator/=(float scalar);

    // Equality operator
    bool operator==(const Vector3& other) const;

    // Inequality operator
    bool operator!=(const Vector3& other) const;

    // Dot product
    float dot(const Vector3& v) const;

    // Cross product
    Vector3 cross(const Vector3& v) const;

    // Vector magnitude
    float magnitude() const;

    // Normalize the vector
    Vector3 normalized() const;

    // Check if the vector is zero
    bool isZero() const;

    // Distance between two vectors
    float distance(const Vector3& v) const;

    // Friend function for scalar multiplication (float * Vector3)
    friend Vector3 operator*(float scalar, const Vector3& v);

    // Access individual elements via operator[]
    float operator[](int index) const;
    float& operator[](int index);
};

#endif // VECTOR3_H
