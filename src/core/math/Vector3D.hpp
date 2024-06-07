/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Vector3D
*/

#pragma once

#include <iostream>
#include <cmath>

namespace math {
    class Vector3D {
        public:
            Vector3D() = default;
            Vector3D(
                const double x, const double y, const double z
            ) : mX(x), mY(y), mZ(z) {}
            ~Vector3D() = default;

            double length() const;
            [[nodiscard]] double dot(const Vector3D &other) const;

            Vector3D operator*(const Vector3D &other) const;
            Vector3D operator*(const double &other) const;
            Vector3D operator*=(const Vector3D &other);
            Vector3D operator*=(const double &other);
            Vector3D operator+(const Vector3D &other) const;
            Vector3D operator+=(const Vector3D &other);
            Vector3D operator-(const Vector3D &other) const;
            Vector3D operator-=(const Vector3D &other);
            Vector3D operator/(const Vector3D &other) const;
            Vector3D operator/(const double &other) const;
            Vector3D operator/=(const Vector3D &other);

            void normalize();
            static Vector3D normalize(const Vector3D &vector);

            double mX = 0;
            double mY = 0;
            double mZ = 0;
    };
}
