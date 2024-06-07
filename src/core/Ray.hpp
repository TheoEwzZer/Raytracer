/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Ray
*/

#pragma once

#include "math/Point3D.hpp"
#include "math/Vector3D.hpp"

namespace raytracer {
    class Ray {
        public:
            Ray() = default;
            Ray(const math::Point3D &origin, const math::Vector3D &direction)
                : mOrigin(origin), mDirection(direction) {}
            ~Ray() = default;

            math::Point3D mOrigin = {0, 0, 0};
            math::Vector3D mDirection = {0, 0, 1};
    };
}
