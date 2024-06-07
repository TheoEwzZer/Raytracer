/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Sphere
*/

#pragma once

#include "../../core/Ray.hpp"
#include "../../core/math/Matrix.hpp"
#include "../../core/math/Vector3D.hpp"
#include "../IPrimitive.hpp"
#include <map>

using std::map;

namespace raytracer {
    class Sphere : public IPrimitive {
        public:
            Sphere() = default;
            Sphere(const int x, const int y, const int z,
                const int radius, const Color &color,
                const map<string, math::Matrix<double>> &allMatrix,
                const math::Vector3D vectorRoation
            ) : mX(x), mY(y), mZ(z), mRadius(radius), mColor(color),
            mAllMatrix(allMatrix), mVectorRotation(vectorRoation) {}
            ~Sphere() override = default;

            double hits(const Ray &ray) override;
            math::Vector3D getNormal(const math::Point3D &point) const override;

            int mX = 0;
            int mY = 0;
            int mZ = 0;
            int mRadius = 0;
            Color mColor;
            map<string, math::Matrix<double>> mAllMatrix;
            math::Vector3D mVectorRotation;
    };
}
