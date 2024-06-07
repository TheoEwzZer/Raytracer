/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IPrimitive
*/

#pragma once

#include "../core/Color.hpp"
#include "../core/Ray.hpp"
#include "../core/math/Point3D.hpp"
#include <iostream>
#include <map>
#include <vector>

using std::vector;
using std::string;
using std::map;

namespace raytracer {
    class IPrimitive {
        public:
            IPrimitive() = default;
            virtual ~IPrimitive() = default;

            virtual double hits(const Ray &ray) = 0;
            virtual math::Vector3D getNormal(const math::Point3D &point) const = 0;

            Color mBaseColor;
            math::Point3D mBaseCenter;
            int mBaseRadius;
            string mBaseAxis;
            int mBasePosition;
            int mBaseHeight;
            map<string, math::Matrix<double>> mBaseAllMatrix;
            math::Vector3D mBaseRotation;
    };
}
