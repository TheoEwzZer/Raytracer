/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Point3D
*/

#include "Point3D.hpp"

math::Point3D math::Point3D::operator+(const math::Vector3D &v) const
{
    return math::Point3D(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

math::Point3D math::Point3D::operator+(
    const math::Point3D &p) const
{
    return math::Point3D(mX + p.mX, mY + p.mY, mZ + p.mZ);
}

math::Point3D math::Point3D::operator+=(const math::Vector3D &v)
{
    mX += v.mX;
    mY += v.mY;
    mZ += v.mZ;
    return *this;
}

math::Point3D math::Point3D::operator-(const math::Vector3D &v) const
{
    return math::Point3D(mX - v.mX, mY - v.mY, mZ - v.mZ);
}


math::Vector3D math::Point3D::operator-(const math::Point3D &p) const
{
    return math::Vector3D(mX - p.mX, mY - p.mY, mZ - p.mZ);
}
