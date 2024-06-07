/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Plane
*/

#pragma once

#include "../../core/math/Matrix.hpp"
#include "../IPrimitive.hpp"
#include <map>

using std::string;
using std::map;

namespace raytracer {
    class Plane : public IPrimitive {
        public:
            Plane() = default;
            Plane(const string &axis, const int position, const Color &color,
            const map<string, math::Matrix<double>> &allMatrix,
            const math::Vector3D vectorRatation)
                : mAxis(axis), mPosition(position), mColor(color),
                mAllMatrix(allMatrix), mVectorRotation(vectorRatation) {}

            double hits(const Ray &ray) override;
            double checkRayPlaneIntersection(const Ray &ray,
                const math::Point3D &position) const;
            math::Vector3D getNormal(const math::Point3D &point) const override;

            string mAxis = "Z";
            int mPosition = 0;
            Color mColor;
            map<string, math::Matrix<double>> mAllMatrix;
            math::Vector3D mVectorRotation;
    };
}
