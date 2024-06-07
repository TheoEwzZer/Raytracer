/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Rectangle3D
*/

#include "Rectangle3D.hpp"

double raytracer::Rectangle3D::calculateX(const double u) const
{
    return ((2 * u) - 1) * mLeftSide.mX;
}

double raytracer::Rectangle3D::calculateY(const double v) const
{
    return 1 - (2 * v);
}

double raytracer::Rectangle3D::calculateZ() const
{
    return mOrigin.mZ;
}

math::Point3D raytracer::Rectangle3D::pointAt(
    const double u, const double v) const
{
    const math::Point3D point(calculateX(u), calculateY(v), calculateZ());

    return point;
}
