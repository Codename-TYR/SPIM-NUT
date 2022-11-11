#ifndef CRAPVECTORS_H
#define CRAPVECTORS_H


class CrapVector2
{
    float _x,_y;
public:
    CrapVector2();
    CrapVector2(float x, float y);
    float x() const;
    float y() const;
};

class CrapVector3
{
    float _x,_y,_z;
public:
    constexpr CrapVector3() noexcept;
    constexpr CrapVector3(float x, float y, float z) noexcept;

    float x() const;
    float y() const;
    float z() const;

    constexpr inline void setX(float x) noexcept;
    constexpr inline void setY(float y) noexcept;
    constexpr inline void setZ(float z) noexcept;

    float length();
    void normalize();

    constexpr friend inline CrapVector3 operator +(const CrapVector3& v1, const CrapVector3& v2) noexcept;
    constexpr friend inline CrapVector3 operator -(const CrapVector3& v1, const CrapVector3& v2) noexcept;
    constexpr friend inline CrapVector3 operator*(const CrapVector3& v1, const float& f) noexcept;
    constexpr friend inline CrapVector3 operator -(const CrapVector3& v1) noexcept;
    constexpr inline CrapVector3& operator *=(CrapVector3& vector) noexcept;
    constexpr inline CrapVector3& operator /=(CrapVector3& vector) noexcept;
    constexpr friend inline CrapVector3 operator+=(const CrapVector3& v1, const CrapVector3& v2) noexcept;
    constexpr inline CrapVector3& operator *=(float f) noexcept;
    constexpr inline CrapVector3& operator /=(float f) noexcept;

    constexpr static inline float dotProduct(const CrapVector3& v1, const CrapVector3& v2) noexcept;
    constexpr static inline CrapVector3 crossProduct(const CrapVector3& v1, const CrapVector3& v2) noexcept;
};

class CrapVector4
{
    float _x,_y,_z,_w;
public:
    constexpr CrapVector4() noexcept;
    constexpr CrapVector4(float x, float y, float z, float w) noexcept;
    float x() const;
    float y() const;
    float z() const;
    float w() const;

    constexpr inline void setX(float x) noexcept;
    constexpr inline void setY(float y) noexcept;
    constexpr inline void setZ(float z) noexcept;
    constexpr inline void setW(float w) noexcept;

    constexpr friend inline CrapVector4 operator +(const CrapVector4& v1, const CrapVector4& v2) noexcept;
    constexpr friend inline CrapVector4 operator -(const CrapVector4& v1, const CrapVector4& v2) noexcept;
    constexpr friend inline CrapVector4 operator*(const CrapVector4& v1, const float& f) noexcept;
    constexpr friend inline CrapVector4 operator -(const CrapVector4& v1) noexcept;
    constexpr inline CrapVector4& operator *=(CrapVector4& vector) noexcept;
    constexpr inline CrapVector4& operator /=(CrapVector4& vector) noexcept;
    constexpr friend inline CrapVector4 operator+=(const CrapVector4& v1, const CrapVector4& v2) noexcept;
    constexpr inline CrapVector4& operator *=(float f) noexcept;
    constexpr inline CrapVector4& operator /=(float f) noexcept;

    constexpr inline CrapVector3 toVector3D() const noexcept;
};

#endif // CRAPVECTORS_H
