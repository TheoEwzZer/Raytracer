/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#include "Camera.hpp"
#include "Ray.hpp"
#include "math/Point3D.hpp"
#include "math/Vector3D.hpp"
#include "Rectangle3D.hpp"

math::Point3D raytracer::Camera::calculateScreenPos(
    const double u, const double v) const
{
    math::Point3D screenPos = mScreen.pointAt(u, v);

    screenPos.mX += posX;
    screenPos.mY += posY;
    return screenPos;
}

math::Vector3D raytracer::Camera::calculateDirection(
    const math::Point3D &screenPos) const
{
    const math::Point3D cameraPos(posX, posY, posZ);
    math::Vector3D dir = screenPos - cameraPos;

    dir.normalize();
    return dir;
}

raytracer::Ray raytracer::Camera::ray(const double u, const double v) const
{
    const math::Point3D screenPos = calculateScreenPos(u, v);
    const math::Vector3D dir = calculateDirection(screenPos);

    return Ray(mOrigin, dir);
}
