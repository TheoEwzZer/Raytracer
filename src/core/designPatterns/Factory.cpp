/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Factory
*/

#include "Factory.hpp"
#include "../error/Error.hpp"

using enum raytracer::Factory::LightType;
using enum raytracer::Factory::PrimitiveType;

raytracer::Factory::Factory()
{
    registerLight<raytracer::DirectionalLight>(DIRECTIONAL);
    registerLight<raytracer::PointLight>(POINT);
    registerPrimitive<raytracer::Cone>(CONE);
    registerPrimitive<raytracer::Cylinder>(CYLINDER);
    registerPrimitive<raytracer::Plane>(PLANE);
    registerPrimitive<raytracer::Sphere>(SPHERE);
}

unique_ptr<raytracer::IPrimitive> raytracer::Factory::createPrimitive(
    const PrimitiveType type)
{
    if (mCreatorsPrimitives.contains(type)) {
        return mCreatorsPrimitives[type]();
    }
    throw raytracer::FileParseError("Primitive type not found");
}

unique_ptr<raytracer::ILight> raytracer::Factory::createLight(
    const LightType type)
{
    if (mCreatorsLights.contains(type)) {
        return mCreatorsLights[type]();
    }
    throw raytracer::FileParseError("Light type not found");
}
