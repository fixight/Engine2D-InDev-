#pragma once



class Vector2D
{
public:
    float X;
    float Y;

    
    Vector2D() : X(0.0f), Y(0.0f) {}
    Vector2D(float x, float y) : X(x), Y(y) {}

    
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
        return Vector2D(X / scalar, Y / scalar);
    }

    
    float Length() const {
        return std::sqrt(X * X + Y * Y);
    }


    Vector2D Normalized() const {
        float len = Length();
        return (len > 0) ? *this / len : Vector2D(0, 0);
    }
};