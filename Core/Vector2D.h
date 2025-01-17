#pragma once

#include <iostream>
#include <sstream>
#include <cmath>
#include <stdexcept>

class Vector2D {
public:
    float X;
    float Y;

    // Конструкторы
    Vector2D() : X(0.0f), Y(0.0f) {}
    explicit Vector2D(float scalar) : X(scalar), Y(scalar) {}
    Vector2D(float x, float y) : X(x), Y(y) {}

    // Операторы
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(X + other.X, Y + other.Y);
    }

    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(X - other.X, Y - other.Y);
    }

    Vector2D operator*(float scalar) const {
        return Vector2D(X * scalar, Y * scalar);
    }

    Vector2D operator/(float scalar) const {
        if (scalar == 0) {
            throw std::runtime_error("Division by zero");
        }
        return Vector2D(X / scalar, Y / scalar);
    }

    bool operator==(const Vector2D& other) const {
        return X == other.X && Y == other.Y;
    }

    bool operator!=(const Vector2D& other) const {
        return !(*this == other);
    }

    // Методы
    float Length() const {
        return std::sqrt(X * X + Y * Y);
    }

    Vector2D Normalized() const {
        float len = Length();
        return (len > 0) ? *this / len : Vector2D(0.0f, 0.0f);
    }

    std::string ToString() const {
        std::ostringstream Stream;
        Stream << X << "," << Y;
        return Stream.str();
    }

    // Статические методы
    static float DotProduct(const Vector2D& a, const Vector2D& b) {
        return a.X * b.X + a.Y * b.Y;
    }

    static Vector2D Zero() {
        return Vector2D(0.0f, 0.0f);
    }

    static Vector2D One() {
        return Vector2D(1.0f, 1.0f);
    }

    // Друзья для потокового ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
        os << "(" << vec.X << ", " << vec.Y << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector2D& vec) {
        is >> vec.X >> vec.Y;
        return is;
    }
};
