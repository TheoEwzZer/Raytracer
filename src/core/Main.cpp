/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main
*/

#include "RayTracer.hpp"
#include "error/Error.hpp"

using std::cerr;

int main(int argc, char **argv)
{
    core::RayTracer rayTracer(argc, argv);

    try {
        return rayTracer.run();
    } catch (const raytracer::ArgumentError &e) {
        cerr << e.what() << '\n';
        return 84;
    } catch (const raytracer::FileParseError &e) {
        cerr << e.what() << '\n';
        return 84;
    }
}
