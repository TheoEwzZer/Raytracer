/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Point3D
*/

#pragma once

#include "Vector3D.hpp"
#include <cmath>
#include <iostream>

namespace math {
    class Point3D {
        public:
            Point3D() = default;
            Point3D(
                const double x, const double y, const double z
            ) : mX(x), mY(y), mZ(z) {}
            ~Point3D() = default;

            Point3D operator+(const math::Vector3D &v) const;
            Point3D operator+(const Point3D &p) const;
            Point3D operator+=(const math::Vector3D &v);
            Point3D operator-(const math::Vector3D &v) const;
            math::Vector3D operator-(const Point3D &p) const;

            double mX = 0.0;
            double mY = 0.0;
            double mZ = 0.0;
    };
}
