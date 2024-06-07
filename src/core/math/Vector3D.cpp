/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Vector3D
*/

#include "Vector3D.hpp"

using std::sqrt;

double math::Vector3D::length() const
{
    return sqrt((mX * mX) + (mY * mY) + (mZ * mZ));
}

math::Vector3D math::Vector3D::operator+(const Vector3D &other) const
{
    return math::Vector3D(mX + other.mX, mY + other.mY, mZ + other.mZ);
}

math::Vector3D math::Vector3D::operator-(const Vector3D &other) const
{
    return math::Vector3D(mX - other.mX, mY - other.mY, mZ - other.mZ);
}

math::Vector3D math::Vector3D::operator*(const double &other) const
{
    return math::Vector3D(mX * other, mY * other, mZ * other);
}

math::Vector3D math::Vector3D::operator+=(const Vector3D &other)
{
    mX += other.mX;
    mY += other.mY;
    mZ += other.mZ;
    return *this;
}

math::Vector3D math::Vector3D::operator-=(const Vector3D &other)
{
    mX -= other.mX;
    mY -= other.mY;
    mZ -= other.mZ;
    return *this;
}

math::Vector3D math::Vector3D::operator*(const Vector3D &other) const
{
    return math::Vector3D(mX * other.mX, mY * other.mY, mZ * other.mZ);
}


math::Vector3D math::Vector3D::operator*=(const Vector3D &other)
{
    mX *= other.mX;
    mY *= other.mY;
    mZ *= other.mZ;
    return *this;
}

math::Vector3D math::Vector3D::operator/(const Vector3D &other) const
{
    return math::Vector3D(mX / other.mX, mY / other.mY, mZ / other.mZ);
}

math::Vector3D math::Vector3D::operator/=(const Vector3D &other)
{
    mX /= other.mX;
    mY /= other.mY;
    mZ /= other.mZ;
    return *this;
}

math::Vector3D math::Vector3D::operator*=(const double &other)
{
    mX *= other;
    mY *= other;
    mZ *= other;
    return *this;
}

math::Vector3D math::Vector3D::operator/(const double &other) const
{
    return math::Vector3D(mX / other, mY / other, mZ / other);
}

double math::Vector3D::dot(const Vector3D &other) const
{
    return (mX * other.mX) + (mY * other.mY) + (mZ * other.mZ);
}

void math::Vector3D::normalize()
{
    const double len = length();

    mX /= len;
    mY /= len;
    mZ /= len;
}

math::Vector3D math::Vector3D::normalize(const Vector3D &vector)
{
    const double len = vector.length();

    return math::Vector3D(vector.mX / len, vector.mY / len, vector.mZ / len);
}
