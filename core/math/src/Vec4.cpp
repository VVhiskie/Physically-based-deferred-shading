#include <math.h>
#include <Vec4.h>

namespace math
{
    vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
    vec4::vec4(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {};
    vec4::vec4(const vec4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {};
    vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

    vec4& vec4::add(const vec4& other)
    {
        x += other.x; y += other.y; z += other.z; w += other.w;
        return *this;
    }

    vec4& vec4::substract(const vec4& other)
    {
        x -= other.x; y -= other.y; z -= other.z; w -= other.w;
        return *this;
    }

    vec4& vec4::multiply(const vec4& other)
    {
        x *= other.x; y *= other.y; z *= other.z; w *= other.w;
        return *this;
    }

    vec4& vec4::divide(const vec4& other)
    {
        x /= other.x; y /= other.y; z /= other.z; w /= other.w;
        return *this;
    }

    vec4& vec4::add(float scalar)
    {
        x += scalar; y += scalar; z += scalar; w += scalar;
        return *this;
    }

    vec4& vec4::substract(float scalar)
    {
        x -= scalar; y -= scalar; z -= scalar; w -= scalar;
        return *this;
    }

    vec4& vec4::multiply(float scalar)
    {
        x *= scalar; y *= scalar; z *= scalar; w *= scalar;
        return *this;
    }

    vec4& vec4::divide(float scalar)
    {
        x /= scalar; y /= scalar; z /= scalar; w /= scalar;
        return *this;
    }

    vec4& vec4::operator +=(const vec4& other) { return add(other); }
    vec4& vec4::operator -=(const vec4& other) { return substract(other); }
    vec4& vec4::operator *=(const vec4& other) { return multiply(other); }
    vec4& vec4::operator /=(const vec4& other) { return divide(other); }

    vec4& vec4::operator +=(float scalar) { return add(scalar); }
    vec4& vec4::operator -=(float scalar) { return substract(scalar); }
    vec4& vec4::operator *=(float scalar) { return multiply(scalar); }
    vec4& vec4::operator /=(float scalar) { return divide(scalar); }

    vec4& vec4::operator +(const vec4& other) const { return vec4(*this).add(other); }
    vec4& vec4::operator -(const vec4& other) const { return vec4(*this).substract(other); }
    vec4& vec4::operator *(const vec4& other) const { return vec4(*this).multiply(other); }
    vec4& vec4::operator /(const vec4& other) const { return vec4(*this).divide(other); }

    vec4& vec4::operator +(float scalar) const { return vec4(*this).add(scalar); }
    vec4& vec4::operator -(float scalar) const { return vec4(*this).substract(scalar); }
    vec4& vec4::operator *(float scalar) const { return vec4(*this).multiply(scalar); }
    vec4& vec4::operator /(float scalar) const { return vec4(*this).divide(scalar); }
    
    float vec4::magnitude() const { return sqrt(x*x + y*y + z*z + w*w); }
    float vec4::dot(const vec4& other) const { return x * other.x + y * other.y + z * other.z + w * other.w;}
    vec4 vec4::normalize() const { return *this / magnitude(); }
}