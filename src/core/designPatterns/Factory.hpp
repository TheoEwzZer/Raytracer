/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Factory
*/

#pragma once

#include "../../lights/directionalLight/DirectionalLight.hpp"
#include "../../lights/ILight.hpp"
#include "../../lights/pointLight/PointLight.hpp"
#include "../../primitives/cone/Cone.hpp"
#include "../../primitives/cylinder/Cylinder.hpp"
#include "../../primitives/IPrimitive.hpp"
#include "../../primitives/plane/Plane.hpp"
#include "../../primitives/sphere/Sphere.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

using std::function;
using std::make_unique;
using std::unique_ptr;
using std::unordered_map;

namespace raytracer {
    class Factory {
        public:
            enum class PrimitiveType { SPHERE, PLANE, CYLINDER, CONE };
            enum class LightType { POINT, DIRECTIONAL };
            Factory();
            ~Factory() = default;

            template <typename Type>
            void registerPrimitive(const PrimitiveType type)
            {
                mCreatorsPrimitives[type] = [this]() {
                    return make_unique<Type>();
                };
            }

            template <typename Type>
            void registerLight(const LightType type)
            {
                mCreatorsLights[type] = [this]() {
                    return make_unique<Type>();
                };
            }

            unique_ptr<IPrimitive> createPrimitive(PrimitiveType type);
            unique_ptr<ILight> createLight(LightType type);
        private:
            using CreatorPrimitives = function<unique_ptr<IPrimitive>()>;
            unordered_map<PrimitiveType, CreatorPrimitives> mCreatorsPrimitives;

            using CreatorLights = function<unique_ptr<ILight>()>;
            unordered_map<LightType, CreatorLights> mCreatorsLights;
    };
}
