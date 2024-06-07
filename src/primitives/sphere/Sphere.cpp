/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

using std::sqrt;

double raytracer::Sphere::hits(const Ray &ray)
{
    const math::Vector3D oc = ray.mOrigin - mBaseCenter;
    const double a = ray.mDirection.dot(ray.mDirection);
    const double b = 2.0 * oc.dot(ray.mDirection);
    const double c = oc.dot(oc) - (mBaseRadius * mBaseRadius);
    const double discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0) {
        return -1.0;
    }
    return (-b - ::sqrt(discriminant)) / (2.0 * a);
}

math::Vector3D raytracer::Sphere::getNormal(const math::Point3D &point) const
{
    math::Vector3D normal = point - mBaseCenter;

    normal.normalize();
    return normal;
}
