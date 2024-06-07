/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PointLight
*/

#include "PointLight.hpp"

using std::numeric_limits;

double raytracer::PointLight::getColorDistance(const math::Point3D &intersectionPoint)
{
    const double distance = (mBaseOrigin - intersectionPoint).length();
    const double attenuation = 1.0 / distance;

    return attenuation;
}

double raytracer::PointLight::findClosestHit(
    const vector<unique_ptr<IPrimitive>> &primitives,
    const Ray &shadowRay) const
{
    double closestHit = numeric_limits<double>::max();
    double hitResult = 0.0;

    for (const auto &primitive : primitives) {
        hitResult = primitive.get()->hits(shadowRay);
        if ((hitResult > 0.0) && (hitResult < closestHit)) {
            closestHit = hitResult;
        }
    }
    return closestHit;
}

raytracer::Color raytracer::PointLight::getColorShadow(
    const math::Point3D &intersectionPoint,
    const math::Vector3D &normal,
    const vector<unique_ptr<IPrimitive>> &primitives)
{
    const math::Vector3D lightDir = (mBaseOrigin - intersectionPoint);
    const Ray shadowRay(
        intersectionPoint + (normal * 0.01),
        math::Vector3D::normalize(lightDir)
    );
    const double closestHit = findClosestHit(primitives, shadowRay);

    if (closestHit < lightDir.length()) {
        return Color(0.0, 0.0, 0.0);
    }
    return mBaseColor;
}
