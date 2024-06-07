/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ILight
*/

#pragma once

#include <iostream>
#include "../core/Color.hpp"
#include "../primitives/IPrimitive.hpp"
#include <memory>

using std::unique_ptr;

namespace raytracer {
    class ILight {
        public:
            virtual ~ILight() = default;

            virtual double getColorDistance(
                const math::Point3D &intersectionPoint
            ) = 0;
            virtual Color getColorShadow(
                const math::Point3D &intersectionPoint,
                const math::Vector3D &normal,
                const vector<unique_ptr<IPrimitive>> &primitives
            ) = 0;

            math::Point3D mBaseOrigin;
            math::Vector3D mBaseDirection;
            Color mBaseColor;
            math::Vector3D mBaseVectorRotation;
    };
}
