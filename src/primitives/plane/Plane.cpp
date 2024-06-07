/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plane
*/

#include "Plane.hpp"
#include "../../core/math/Vector3D.hpp"

using std::abs;

double raytracer::Plane::hits(const Ray &ray)
{
    math::Point3D position;

    if (mBaseAxis == "X") {
        position = math::Point3D(mBasePosition, 0.0, 0.0);
    } else if (mBaseAxis == "Y") {
        position = math::Point3D(0.0, 0.0, mBasePosition);
    } else if (mBaseAxis == "Z") {
        position = math::Point3D(0.0, mBasePosition, 0.0);
    } else {
        return -1.0;
    }
    return checkRayPlaneIntersection(ray, position);
}

double raytracer::Plane::checkRayPlaneIntersection(
    const Ray &ray, const math::Point3D &position) const
{
    const math::Vector3D normal = getNormal(position);
    const double epsilon = 1e-10;
    const double rayPlaneAngle = ray.mDirection.dot(normal);
    const math::Vector3D pointOnPlane = position - ray.mOrigin;
    const double t = pointOnPlane.dot(normal) / rayPlaneAngle;

    if (abs(rayPlaneAngle) < epsilon) {
        return -1.0;
    }
    return t;
}

math::Vector3D raytracer::Plane::getNormal(const math::Point3D &point) const
{
    (void)point;
    if (mBaseAxis == "X") {
        return math::Vector3D(1.0, 0.0, 0.0);
    }
    if (mBaseAxis == "Y") {
        return math::Vector3D(0.0, 0.0, 1.0);
    }
    if (mBaseAxis == "Z") {
        return math::Vector3D(0.0, 1.0, 0.0);
    }
    return math::Vector3D(0.0, 0.0, 0.0);
}
