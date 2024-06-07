/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene
*/

#pragma once

#include "Camera.hpp"
#include "Color.hpp"
#include "Image.hpp"
#include "SceneParser.hpp"
#include "designPatterns/Factory.hpp"
#include "../lights/ILight.hpp"
#include "../primitives/plane/Plane.hpp"
#include "../primitives/sphere/Sphere.hpp"
#include <iostream>
#include <memory>
#include <random>

using std::unique_ptr;
using std::mt19937;
using std::uniform_real_distribution;

namespace raytracer {
    class Scene {
        public:
            Scene() = default;
            ~Scene() = default;

            void render(Image &image);
            void init(const core::SceneParser &sceneParser);
            void initPlanes(const vector<Plane> &planes,
                const size_t o, Factory &factory);
            void initSpheres(const vector<Sphere> &spheres,
                const size_t o, Factory &factory);
            void initCylinders(const vector<Cylinder> &cylinders,
                const size_t o, Factory &factory);
            void initCones(const vector<Cone> &cones,
                const size_t o, Factory &factory);
            void initPoints(const vector<PointLight> &points,
                const size_t o, Factory &factory);
            void initDirectionals(const vector<DirectionalLight> &directionals,
                const size_t o, Factory &factory);
            Color getColor(
                const unsigned int x, const unsigned int y,
                const unsigned int height, const unsigned int width
            );
            Color getLightColor(const IPrimitive &primitive,
                const math::Point3D &intersectionPoint,
                const math::Vector3D &normal);
            Camera mCamera;
            double mAmbient = 0.0;
            double mDiffuse = 0.0;
            vector<unique_ptr<IPrimitive>> mPrimitives;
            vector<unique_ptr<ILight>> mLights;
            mt19937 mGen = mt19937(std::random_device()());
            uniform_real_distribution<double> mDis =
                uniform_real_distribution<double>(0.0, 1.0);
            void setFastRender(const bool isFastRender);
            bool mIsFastRender;
    };
}
