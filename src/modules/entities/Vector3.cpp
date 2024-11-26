/**
 * Vector3.cpp
 * Security: Confidential
 * Author: Minseok Doo
 * Created Date: Oct 24, 2024
 * Last Modified: Nov 18, 2024
 */

#include "Vector3.h"
#include <cmath> // sqrt, abs

// Default and parameterized constructor
Vector3::Vector3(float xVal, float yVal, float zVal) {
    values[0] = xVal;
    values[1] = yVal;
    values[2] = zVal;
}

// JSON Serialization
json Vector3::toJson() const {
    return json{{"x", x}, {"y", y}, {"z", z}};
}

Vector3 Vector3::fromJson(const json& j) {
    return Vector3(j.at("x").get<float>(), j.at("y").get<float>(), j.at("z").get<float>());
}

// Overloaded output operator
std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

// Vector addition
Vector3 Vector3::operator+(const Vector3& v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3& Vector3::operator+=(const Vector3& v) {
    x += v.x; y += v.y; z += v.z;
    return *this;
}

// Vector subtraction
Vector3 Vector3::operator-(const Vector3& v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3& Vector3::operator-=(const Vector3& v) {
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
}

// Scalar multiplication (Vector3 * float)
Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3& Vector3::operator*=(float scalar) {
    x *= scalar; y *= scalar; z *= scalar;
    return *this;
}

// Hadamard product (Vector3 * Vector3)
Vector3 Vector3::operator*(const Vector3& v) const {
    return Vector3(x * v.x, y * v.y, z * v.z);
}

// Scalar division
Vector3 Vector3::operator/(float scalar) const {
    return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3& Vector3::operator/=(float scalar) {
    x /= scalar; y /= scalar; z /= scalar;
    return *this;
}

// Equality operator
bool Vector3::operator==(const Vector3& other) const {
    return std::abs(x - other.x) < 1e-5f &&
           std::abs(y - other.y) < 1e-5f &&
           std::abs(z - other.z) < 1e-5f;
}

// Inequality operator
bool Vector3::operator!=(const Vector3& other) const {
    return !(*this == other);
}

// Dot product
float Vector3::dot(const Vector3& v) const {
    return x * v.x + y * v.y + z * v.z;
}

// Cross product
Vector3 Vector3::cross(const Vector3& v) const {
    return Vector3(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

// Vector magnitude
float Vector3::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Normalize the vector
Vector3 Vector3::normalized() const {
    float mag = magnitude();
    if (mag == 0.0f)
        return Vector3(0.0f, 0.0f, 0.0f);
    return *this / mag;
}

// Check if the vector is zero
bool Vector3::isZero() const {
    return std::abs(x) < 1e-5f && std::abs(y) < 1e-5f && std::abs(z) < 1e-5f;
}

// Distance between two vectors
float Vector3::distance(const Vector3& v) const {
    return (*this - v).magnitude();
}

// Friend function for scalar multiplication (float * Vector3)
Vector3 operator*(float scalar, const Vector3& v) {
    return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
}

// Access individual elements via operator[]
float Vector3::operator[](int index) const {
    return values[index];
}

float& Vector3::operator[](int index) {
    return values[index];
}
