#include "crapvectors.h"
#include <math.h>

CrapVector2::CrapVector2() : _x{0}, _y{0}
{

}

CrapVector2::CrapVector2(float x, float y) : _x{x}, _y{y}
{

}

float CrapVector2::x() const
{
    return _x;
}

float CrapVector2::y() const
{
    return _y;
}

constexpr inline CrapVector3::CrapVector3() noexcept : _x{0}, _y{0}, _z{0}
{

}

constexpr inline CrapVector3::CrapVector3(float x, float y, float z) noexcept : _x{x}, _y{y}, _z{z}
{

}

float CrapVector3::x() const
{
    return _x;
}

float CrapVector3::y() const
{
    return _y;
}

float CrapVector3::z() const
{
    return _z;
}

constexpr void CrapVector3::setX(float x) noexcept
{
    _x = x;
}

constexpr void CrapVector3::setY(float y) noexcept
{
    _y = y;
}

constexpr void CrapVector3::setZ(float z) noexcept
{
    _z = z;
}

float CrapVector3::length()
{
    float out;
    out = (_x * _x) + (_y * _y) + (_z * _z);
    out = std::pow(out, 0.5f);
    return out;
}

void CrapVector3::normalize()
{
    float l = length();
    _x /= l;
    _y /= l;
    _z /= l;
}

constexpr inline CrapVector3 operator+(const CrapVector3& v1, const CrapVector3& v2) noexcept
{
    CrapVector3 out = v1;
    out._x += v2._x;
    out._y += v2._y;
    out._z += v2._z;
    return out;
}

constexpr inline CrapVector3 operator-(const CrapVector3& v1, const CrapVector3& v2) noexcept
{
    CrapVector3 out = v1;
    out._x -= v2._x;
    out._y -= v2._y;
    out._z -= v2._z;
    return out;
}

constexpr inline CrapVector3 operator*(const CrapVector3& v1, const float& f) noexcept
{
    CrapVector3 out = v1;
    out._x *= f;
    out._y *= f;
    out._z *= f;
    return out;
}

constexpr inline CrapVector3 operator-(const CrapVector3& v1) noexcept
{
    CrapVector3 out = v1;
    out._x *= -1;
    out._y *= -1;
    out._z *= -1;
    return out;
}

constexpr inline CrapVector3 operator+=(const CrapVector3& v1, const CrapVector3& v2) noexcept
{
    CrapVector3 out = v1;
    out._x += v2._x;
    out._y += v2._y;
    out._z += v2._z;
    return out;
}

constexpr inline CrapVector3 &CrapVector3::operator*=(CrapVector3& vector) noexcept
{
    _x *= vector._x;
    _y *= vector._y;
    _z *= vector._z;
    return *this;
}

constexpr inline CrapVector3 &CrapVector3::operator/=(CrapVector3& vector) noexcept
{
    _x /= vector._x;
    _y /= vector._y;
    _z /= vector._z;
    return *this;
}

constexpr inline float CrapVector3::dotProduct(const CrapVector3 &v1, const CrapVector3 &v2) noexcept
{
    return v1._x * v2._x + v1._y * v2._y + v1._z * v2._z;
}

constexpr inline CrapVector3 CrapVector3::crossProduct(const CrapVector3 &v1, const CrapVector3 &v2) noexcept
{
    CrapVector3 out;
    out._x = v1._y * v2._z - v1._z * v2._y;
    out._y = v1._z * v2._x - v1._x * v2._z;
    out._z = v1._x * v2._y - v1._y * v2._x;
    return out;
}


constexpr inline CrapVector3 &CrapVector3::operator*=(float f) noexcept
{
    _x *= f;
    _y *= f;
    _z *= f;
    return *this;
}

constexpr inline CrapVector3 &CrapVector3::operator/=(float f) noexcept
{
    _x /= f;
    _y /= f;
    _z /= f;
    return *this;
}

constexpr inline CrapVector4::CrapVector4() noexcept : _x{0}, _y{0}, _z{0}, _w{0}
{

}

constexpr inline CrapVector4::CrapVector4(float x, float y, float z, float w) noexcept : _x{x}, _y{y}, _z{z}, _w{w}
{

}

float CrapVector4::x() const
{
    return _x;
}

float CrapVector4::y() const
{
    return _y;
}

float CrapVector4::z() const
{
    return _z;
}

float CrapVector4::w() const
{
    return _w;
}

constexpr void CrapVector4::setX(float x) noexcept
{
    _x = x;
}

constexpr void CrapVector4::setY(float y) noexcept
{
    _y = y;
}

constexpr void CrapVector4::setZ(float z) noexcept
{
    _z = z;
}
constexpr void CrapVector4::setW(float w) noexcept
{
    _w = w;
}

constexpr inline CrapVector4 operator+(const CrapVector4& v1, const CrapVector4& v2) noexcept
{
    CrapVector4 out = v1;
    out._x += v2._x;
    out._y += v2._y;
    out._z += v2._z;
    return out;
}

constexpr inline CrapVector4 operator-(const CrapVector4& v1, const CrapVector4& v2) noexcept
{
    CrapVector4 out = v1;
    out._x -= v2._x;
    out._y -= v2._y;
    out._z -= v2._z;
    return out;
}
constexpr inline CrapVector4 operator*(const CrapVector4& v1, const float& f) noexcept
{
    CrapVector4 out = v1;
    out._x *= f;
    out._y *= f;
    out._z *= f;
    return out;
}

constexpr inline CrapVector4 operator-(const CrapVector4& v1) noexcept
{
    CrapVector4 out = v1;
    out._x *= -1;
    out._y *= -1;
    out._z *= -1;
    return out;
}

constexpr inline CrapVector4 operator+=(const CrapVector4& v1, const CrapVector4& v2) noexcept
{
    CrapVector4 out = v1;
    out._x += v2._x;
    out._y += v2._y;
    out._z += v2._z;
    return out;
}

constexpr inline CrapVector4 &CrapVector4::operator*=(CrapVector4& vector) noexcept
{
    _x *= vector._x;
    _y *= vector._y;
    _z *= vector._z;
    return *this;
}

constexpr inline CrapVector4 &CrapVector4::operator/=(CrapVector4& vector) noexcept
{
    _x /= vector._x;
    _y /= vector._y;
    _z /= vector._z;
    return *this;
}

constexpr inline CrapVector3 CrapVector4::toVector3D() const noexcept
{
    CrapVector3 out{_x,_y,_z};
    return out;
}

constexpr inline CrapVector4 &CrapVector4::operator*=(float f) noexcept
{
    _x *= f;
    _y *= f;
    _z *= f;
    return *this;
}

constexpr inline CrapVector4 &CrapVector4::operator/=(float f) noexcept
{
    _x /= f;
    _y /= f;
    _z /= f;
    return *this;
}
