/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#pragma once

#include "Ray.hpp"
#include "Rectangle3D.hpp"
#include "math/Matrix.hpp"
#include <iostream>
#include <map>

using std::map;
using std::string;

namespace raytracer {
    class Camera {
        public:
            Camera() = default;
            ~Camera() = default;

            Ray ray(const double u, const double v) const;
            math::Point3D calculateScreenPos(const double u, const double v) const;
            math::Vector3D calculateDirection(const math::Point3D &screenPos) const;

            int width = 0;
            int height = 0;
            int posX = 0;
            int posY = 0;
            int posZ = 0;
            double fieldOfView = 0.0;
            Rectangle3D mScreen;
            math::Point3D mOrigin;
            map<string, math::Matrix<double>> mAllMatrix;
            math::Vector3D mVectorRotation;
    };
}
