/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PointLight
*/

#pragma once

#include "../../core/Color.hpp"
#include "../../core/math/Matrix.hpp"
#include "../../core/math/Point3D.hpp"
#include "../../primitives/IPrimitive.hpp"
#include "../ILight.hpp"
#include <iostream>
#include <map>

using std::string;
using std::map;

namespace raytracer {
    class PointLight : public ILight {
        public:
            PointLight() = default;
            PointLight(const int originX, const int originY, const int originZ,
                const Color &color,
                const map<string, math::Matrix<double>> &allMatrix,
                const math::Vector3D vectorRatation)
                : mOrigin(originX, originY, originZ), mColor(color),
                mAllMatrix(allMatrix), mVectorRotation(vectorRatation) {}
            ~PointLight() override = default;

            double getColorDistance(const math::Point3D &intersectionPoint) override;
            Color getColorShadow(
                const math::Point3D &intersectionPoint,
                const math::Vector3D &normal,
                const vector<unique_ptr<IPrimitive>> &primitives
            ) override;
            double findClosestHit(
                const vector<unique_ptr<IPrimitive>> &primitives,
                const Ray &shadowRay
            ) const;

            math::Point3D mOrigin;
            Color mColor;
            map<string, math::Matrix<double>> mAllMatrix;
            math::Vector3D mVectorRotation;
    };
}