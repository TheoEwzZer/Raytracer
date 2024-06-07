/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Core
*/

#pragma once

#include <iostream>
#include <fstream>

namespace core {
    class RayTracer {
        public:
            RayTracer(const int argc, char **const argv)
                : mArgc(argc), mArgv(argv) {}
            ~RayTracer() = default;

            void printHelp() const;
            int run() const;
        private:
            int mArgc;
            char **mArgv;
    };
}
