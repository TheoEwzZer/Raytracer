/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Core
*/

#include "Image.hpp"
#include "RayTracer.hpp"
#include "Scene.hpp"
#include "SceneParser.hpp"
#include <filesystem>
#include "error/Error.hpp"

using std::cout;
using std::cerr;
using std::string;
using std::vector;
using std::ifstream;

void core::RayTracer::printHelp() const
{
    cout << "USAGE: ./raytracer <SCENE_FILE>\n";
    cout << "\tSCENE_FILE: scene configuration\n";
}

int core::RayTracer::run() const
{
    string sceneFile;
    ifstream file;
    raytracer::Scene scene;
    string baseFilename;
    string outputFilename;
    bool useSFML = false;
    bool isFastRender = false;
    string arg;

    if (mArgc < 2) {
        printHelp();
        return 84;
    }
    for (int i = 1; i < mArgc; i++) {
        arg = mArgv[i];
        if ((arg == "--help") || (arg == "-h")) {
            printHelp();
            return 0;
        } else if ((arg == "--graphical") || (arg == "-g")) {
            useSFML = true;
        } else if ((arg == "--fast") || (arg == "-f")) {
            isFastRender = true;
        } else {
            sceneFile = arg;
        }
    }
    if (sceneFile.empty()) {
        throw raytracer::ArgumentError("Error: no scene file provided");
    }
    file.open(sceneFile);
    if (!file.is_open()) {
        throw raytracer::FileParseError("Error: can't open file " + sceneFile);
    }
    core::SceneParser parser(scene.mCamera);
    try {
        parser.parseFile(sceneFile);
    } catch (const raytracer::SceneParserError &e) {
        cerr << e.what() << "\n";
        return 84;
    }
    if (!parser.hasBasicElementInFiles()) {
        return 84;
    }
    raytracer::Image image(
        static_cast<unsigned int>(scene.mCamera.width),
        static_cast<unsigned int>(scene.mCamera.height),
        useSFML
    );
    scene.setFastRender(isFastRender);
    scene.init(parser);
    scene.render(image);
    const std::filesystem::path p(sceneFile);
    baseFilename = p.stem().string();
    outputFilename = "screenshots/" + baseFilename + ".ppm";
    if (useSFML) {
        image.display(sceneFile, outputFilename, isFastRender);
    } else {
        image.displayPPM(outputFilename);
    }
    return 0;
}
