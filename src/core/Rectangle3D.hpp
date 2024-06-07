/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Rectangle3D
*/

#pragma once

#include <iostream>
#include "math/Point3D.hpp"
#include "math/Vector3D.hpp"

namespace raytracer {
    class Rectangle3D {
        public:
            Rectangle3D() = default;
            Rectangle3D(const math::Point3D &origin,
                const math::Vector3D &bottomSide,
                const math::Vector3D &leftSide)
                : mOrigin(origin), mBottomSide(bottomSide),
                mLeftSide(leftSide) {}
            ~Rectangle3D() = default;

            [[nodiscard]] math::Point3D pointAt(double u, double v) const;
            [[nodiscard]] double calculateX(double u) const;
            [[nodiscard]] double calculateY(double v) const;
            [[nodiscard]] double calculateZ() const;
        private:
            math::Point3D mOrigin;
            math::Vector3D mBottomSide;
            math::Vector3D mLeftSide;
    };
}
