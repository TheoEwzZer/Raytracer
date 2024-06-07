/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SceneParser
*/

#include "SceneParser.hpp"
#include <format>

using std::cerr;
using std::size_t;
using std::string;
using std::vector;
using std::ifstream;
using std::format;

void core::SceneParser::parseCamera(const libconfig::Config &cfg)
{
    if (cfg.exists("camera")) {
        try {
            const libconfig::Setting &cameraSetting = cfg.lookup("camera");
            const libconfig::Setting &resolution = cameraSetting["resolution"];
            const libconfig::Setting &position = cameraSetting["position"];
            map<string, math::Matrix<double>> allMatrix;
            math::Vector3D vectorRotation;
            mCamera.width = resolution["width"];
            mCamera.height = resolution["height"];
            mCamera.posX = position["x"];
            mCamera.posY = position["y"];
            mCamera.posZ = position["z"];
            mCamera.fieldOfView = cameraSetting["fieldOfView"];
            parseRotation(cameraSetting, allMatrix, vectorRotation);
            parseTranslation(cameraSetting, allMatrix);
            calcFinalTransformationMatrix(allMatrix);
            mCamera.mAllMatrix = allMatrix;
            mCamera.mVectorRotation = vectorRotation;
        } catch (const libconfig::SettingNotFoundException &) {
            cerr << "One or many configuration are missing or incorrect "
                 << "with Camera\n";
        }
    }
}

void core::SceneParser::parseSpheres(
    const libconfig::Setting &spheresSetting)
{
    const int spheresLength = spheresSetting.getLength();
    raytracer::Color colors;
    int x = 0;
    int y = 0;
    int z = 0;
    int r = 0;

    for (int i = 0; i < spheresLength; i++) {
        map<string, math::Matrix<double>> allMatrix;
        math::Vector3D vectorRotation;
        x = spheresSetting[i]["x"];
        y = spheresSetting[i]["y"];
        z = spheresSetting[i]["z"];
        r = spheresSetting[i]["r"];
        const libconfig::Setting &color = spheresSetting[i]["color"];
        colors = raytracer::Color(color["r"], color["g"], color["b"]);
        parseTranslation(spheresSetting[i], allMatrix);
        parseRotation(spheresSetting[i], allMatrix, vectorRotation);
        parseScale(spheresSetting[i], allMatrix);
        calcFinalTransformationMatrix(allMatrix);
        mSpheres.emplace_back(x, y, z, r, colors, allMatrix, vectorRotation);
    }
}

void core::SceneParser::parsePlanes(
    const libconfig::Setting &planesSetting)
{
    const int planesLength = planesSetting.getLength();
    raytracer::Color colors;
    int position = 0;
    string axis;
    math::Vector3D vectorRotation(0, 0, 0);

    for (int i = 0; i < planesLength; i++) {
        map<string, math::Matrix<double>> allMatrix;
        axis = static_cast<string>(planesSetting[i]["axis"]);
        position = planesSetting[i]["position"];
        try {
            const double rotation = planesSetting[i]["rotation"];
            const double translation = planesSetting[i]["translation"];
            allMatrix["translation"] = {
                {1.0, translation},
                {0.0, 1.0}
            };
            if (axis == "Z") {
                allMatrix["rotation"] = {
                    {::cos(rotation), -::sin(rotation), 0.0, 0.0},
                    {::sin(rotation), ::cos(rotation), 0.0, 0.0},
                    {0.0, 0.0, 1.0, 0.0},
                    {0.0, 0.0, 0.0, 1.0}
                };
                allMatrix["translation"] = {
                    {1.0, 0.0, 0.0, 1.0},
                    {0.0, 1.0, 0.0, 1.0},
                    {0.0, 0.0, 1.0, translation},
                    {0.0, 0.0, 0.0, 1.0}
                };
                vectorRotation.mZ = rotation;
            }
            if (axis == "X") {
                allMatrix["rotation"] = {
                    {1.0, 0.0, 0.0, 0.0},
                    {0.0, ::cos(rotation), -::sin(rotation), 0.0},
                    {0.0, ::sin(rotation), ::cos(rotation), 0.0},
                    {0.0, 0.0, 0.0, 1.0}
                };
                allMatrix["translation"] = {
                    {1.0, 0.0, 0.0, translation},
                    {0.0, 1.0, 0.0, 1.0},
                    {0.0, 0.0, 1.0, 1.0},
                    {0.0, 0.0, 0.0, 1.0}
                };
                vectorRotation.mX = rotation;
            }
            if (axis == "Y") {
                allMatrix["rotation"] = {
                    {::cos(rotation), 0.0, ::sin(rotation), 0.0},
                    {0.0, 1.0, 0.0, 0.0},
                    {-::sin(::sin(rotation)), 0, ::cos(rotation), 0.0},
                    {0.0, 0.0, 0.0, 1.0}
                };
                allMatrix["translation"] = {
                    {1.0, 0.0, 0.0, 1.0},
                    {0.0, 1.0, 0.0, translation},
                    {0.0, 0.0, 1.0, 1.0},
                    {0.0, 0.0, 0.0, 1.0}
                };
                vectorRotation.mY = rotation;
            }
        calcFinalTransformationMatrix(allMatrix);
        } catch (const libconfig::SettingNotFoundException &) {
        }
        const libconfig::Setting &color = planesSetting[i]["color"];
        colors = raytracer::Color(color["r"], color["g"], color["b"]);
        mPlanes.emplace_back(axis, position, colors, allMatrix, vectorRotation);
    }
}

void core::SceneParser::parseCylinders(
    const libconfig::Setting &cylindersSetting)
{
    const int cylindersLength = cylindersSetting.getLength();
    raytracer::Color colors;
    int x = 0;
    int y = 0;
    int z = 0;
    int radius = 0;
    int height = 0;

    for (int i = 0; i < cylindersLength; i++) {
        map<string, math::Matrix<double>> allMatrix;
        math::Vector3D vectorRotation;
        x = cylindersSetting[i]["x"];
        y = cylindersSetting[i]["y"];
        z = cylindersSetting[i]["z"];
        radius = cylindersSetting[i]["r"];
        height = cylindersSetting[i]["h"];
        const libconfig::Setting &color = cylindersSetting[i]["color"];
        colors = raytracer::Color(color["r"], color["g"], color["b"]);
        parseTranslation(cylindersSetting[i], allMatrix);
        parseRotation(cylindersSetting[i], allMatrix, vectorRotation);
        parseScale(cylindersSetting[i], allMatrix);
        calcFinalTransformationMatrix(allMatrix);
        mCylinders.emplace_back(
            x, y, z, radius, height, colors, allMatrix, vectorRotation
        );
    }
}

void core::SceneParser::parseCones(const libconfig::Setting &conesSetting)
{
    const int conesLength = conesSetting.getLength();
    raytracer::Color colors;
    int x = 0;
    int y = 0;
    int z = 0;
    int radius = 0;
    int height = 0;

    for (int i = 0; i < conesLength; i++) {
        map<string, math::Matrix<double>> allMatrix;
        math::Vector3D vectorRotation;
        x = conesSetting[i]["x"];
        y = conesSetting[i]["y"];
        z = conesSetting[i]["z"];
        radius = conesSetting[i]["r"];
        height = conesSetting[i]["h"];
        const libconfig::Setting &color = conesSetting[i]["color"];
        colors = raytracer::Color(color["r"], color["g"], color["b"]);
        parseTranslation(conesSetting[i], allMatrix);
        parseRotation(conesSetting[i], allMatrix, vectorRotation);
        parseScale(conesSetting[i], allMatrix);
        calcFinalTransformationMatrix(allMatrix);
        mCones.emplace_back(
            x, y, z, radius, height, colors, allMatrix, vectorRotation
        );
    }
}

void core::SceneParser::parsePrimitive(const libconfig::Config &cfg)
{
    if (cfg.exists("primitives")) {
        try {
            const libconfig::Setting &primitiveSetting =
                cfg.lookup("primitives");

            if (primitiveSetting.exists("spheres")) {
                const libconfig::Setting &spheres = primitiveSetting["spheres"];
                parseSpheres(spheres);
            }
            if (primitiveSetting.exists("planes")) {
                const libconfig::Setting &planes = primitiveSetting["planes"];
                parsePlanes(planes);
            }
            if (primitiveSetting.exists("cylinders")) {
                const libconfig::Setting &cylinders = primitiveSetting["cylinders"];
                parseCylinders(cylinders);
            }
            if (primitiveSetting.exists("cones")) {
                const libconfig::Setting &cones = primitiveSetting["cones"];
                parseCones(cones);
            }
        } catch (const libconfig::SettingNotFoundException &) {
            cerr << "One or many configuration are missing or incorrect with Primitive\n";
        }
    }
}

void core::SceneParser::parseLights(const libconfig::Config &cfg)
{
    if (cfg.exists("lights")) {
        try {
            const libconfig::Setting &lightsSetting = cfg.lookup("lights");
            const libconfig::Setting &pointSetting = lightsSetting["point"];
            const libconfig::Setting &directionalSetting =
                lightsSetting["directional"];
            const int pointsLength =  pointSetting.getLength();
            const int directionalLength = directionalSetting.getLength();

            for (int i = 0; i < pointsLength; i++) {
                map<string, math::Matrix<double>> allMatrixPoint;
                math::Vector3D vectorRotation;
                const libconfig::Setting &origin = pointSetting[i]["origin"];
                const libconfig::Setting &color = pointSetting[i]["color"];
                raytracer::Color colors(color["r"], color["g"], color["b"]);
                parseTranslation(pointSetting[i], allMatrixPoint);
                parseRotation(pointSetting[i], allMatrixPoint, vectorRotation);
                parseScale(pointSetting[i], allMatrixPoint);
                calcFinalTransformationMatrix(allMatrixPoint);
                mPointLights.emplace_back(
                    origin["x"], origin["y"], origin["z"],
                    colors, allMatrixPoint, vectorRotation
                );
            }
            for (int i = 0; i < directionalLength; i++) {
                map<string, math::Matrix<double>> allMatrixDirectional;
                math::Vector3D vectorRotation;
                const libconfig::Setting &origin = directionalSetting[i]["origin"];
                const libconfig::Setting &direction =
                    directionalSetting[i]["direction"];
                const libconfig::Setting &color = directionalSetting[i]["color"];
                raytracer::Color colors(color["r"], color["g"], color["b"]);
                parseTranslation(directionalSetting[i], allMatrixDirectional);
                parseRotation(directionalSetting[i], allMatrixDirectional, vectorRotation);
                parseScale(directionalSetting[i], allMatrixDirectional);
                calcFinalTransformationMatrix(allMatrixDirectional);
                mDirectionalLights.emplace_back(
                    origin["x"], origin["y"], origin["z"],
                    direction["x"], direction["y"], direction["z"],
                    colors, allMatrixDirectional, vectorRotation
                );
            }
            mAmbient = lightsSetting["ambient"];
            mDiffuse = lightsSetting["diffuse"];
        } catch (const libconfig::SettingNotFoundException &) {
            cerr << "One or many configuration are missing or incorrect with Lights\n";
        }
    }
}

vector<Cylinder> core::SceneParser::getCylinders() const
{
    return mCylinders;
}

vector<Sphere> core::SceneParser::getSpheres() const
{
    return mSpheres;
}

vector<Cone> core::SceneParser::getCones() const
{
    return mCones;
}

vector<Plane> core::SceneParser::getPlanes() const
{
    return mPlanes;
}

vector<PointLight> core::SceneParser::getPointLights() const
{
    return mPointLights;
}

vector<DirectionalLight> core::SceneParser::getDirectionalLights() const
{
    return mDirectionalLights;
}

double core::SceneParser::getAmbient() const
{
    return mAmbient;
}

double core::SceneParser::getDiffuse() const
{
    return mDiffuse;
}

void core::SceneParser::parseRotation(const libconfig::Setting &fileconfigRotation,
    map<string, math::Matrix<double>> &allMatrix,
    math::Vector3D &vectorRotation)
{
    double rotationX = 0.0;
    double rotationY = 0.0;
    double rotationZ = 0.0;
    try {
        const libconfig::Setting &rotation = fileconfigRotation["rotation"];
        try {
            rotationX = rotation["x"];
        } catch (const libconfig::ConfigException &) {
            try {
                rotationX = static_cast<double>(static_cast<int>(rotation["x"]));
            } catch (const libconfig::ConfigException &) {
                cerr << "Not found rotation in axe X or value incorrect\n";
                ::exit(84);
            }
        }
        try {
            rotationY = rotation["y"];
        } catch (const libconfig::ConfigException &) {
            try {
                rotationY = static_cast<double>(static_cast<int>(rotation["y"]));
            } catch (const libconfig::ConfigException &) {
                cerr << "Not found rotation in axe Y or value incorrect\n";
                ::exit(84);
            }
        }
        try {
            rotationZ = rotation["z"];
        } catch (const libconfig::ConfigException &) {
            try {
                rotationZ = static_cast<double>(static_cast<int>(rotation["z"]));
            } catch (const libconfig::ConfigException &) {
                cerr << "Not found rotation in axe Z or value incorrect\n";
                ::exit(84);
            }
        }
        rotationX = (rotationX * M_PI) / 180.0;
        rotationY = (rotationY * M_PI) / 180.0;
        rotationZ = (rotationZ * M_PI) / 180.0;
        allMatrix["rotationX"] = {
            {1.0, 0.0, 0.0, 0.0},
            {0.0, ::cos(rotationX), -::sin(rotationX), 0.0},
            {0, ::sin(rotationX), ::cos(rotationX), 0.0},
            {0.0, 0.0, 0.0, 1.0}
        };
        allMatrix["rotationY"] = {
            {::cos(rotationY), 0.0, ::sin(rotationY), 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {-::sin(rotationY), 0, ::cos(rotationY), 0.0},
            {0.0, 0.0, 0.0, 1.0}
        };
        allMatrix["rotationZ"] = {
            {::cos(rotationZ), -::sin(rotationZ), 0.0, 0.0},
            {::sin(rotationZ), ::cos(rotationZ), 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0}
        };
    } catch (const libconfig::SettingNotFoundException &) {
    }
    vectorRotation = math::Vector3D(rotationX, rotationY, rotationZ);
}

void core::SceneParser::parseTranslation(const libconfig::Setting &fileconfigTranslation,
    map<string, math::Matrix<double>> &allMatrix)
{
    double translationX = 0;
    double translationY = 0;
    double translationZ = 0;
    try {
        const libconfig::Setting &translation = fileconfigTranslation["translation"];
        try {
            translationX = translation["x"];
        } catch (const libconfig::ConfigException &) {
            try {
                translationX = static_cast<double>(static_cast<int>(translation["x"]));
            } catch (const libconfig::ConfigException &) {
                cerr << "Not found translation in axe X or value incorrect\n";
                ::exit(84);
            }
        }
        try {
            translationY = translation["y"];
        } catch (const libconfig::ConfigException &) {
            try {
                translationY = static_cast<double>(static_cast<int>(translation["y"]));
            } catch (const libconfig::ConfigException &) {
                cerr << "Not found translation in axe Y or value incorrect\n";
                ::exit(84);
            }
        }
        try {
            translationZ = translation["z"];
        } catch (const libconfig::ConfigException &) {
            try {
                translationZ = static_cast<double>(static_cast<int>(translation["z"]));
            } catch (const libconfig::ConfigException &) {
                cerr << "Not found translation in axe Z or value incorrect\n";
                ::exit(84);
            }
        }
        allMatrix["translation"] = {
            {1.0, 0.0, 0.0, translationX},
            {0.0, 1.0, 0.0, translationY},
            {0.0, 0.0, 1.0, translationZ},
            {0.0, 0.0, 0.0, 1.0}
        };
    } catch (const libconfig::SettingNotFoundException &) {
    }
}

void core::SceneParser::parseScale(const libconfig::Setting &fileconfigScale,
    map<string, math::Matrix<double>> &allMatrix)
{
    double scaleX = 1.0;
    double scaleY = 1.0;
    double scaleZ = 1.0;
    try {
        const libconfig::Setting &scale = fileconfigScale["scale"];
        try {
            scaleX = scale["x"];
        } catch (const libconfig::ConfigException &) {
            try {
                scaleX = static_cast<double>(static_cast<int>(scale["x"]));
            } catch (const libconfig::ConfigException &) {
            }
        }
        try {
            scaleY = scale["y"];
        } catch (const libconfig::ConfigException &) {
            try {
                scaleY = static_cast<double>(static_cast<int>(scale["y"]));
            } catch (const libconfig::ConfigException &) {
            }
        }
        try {
            scaleZ = scale["z"];
        } catch (const libconfig::ConfigException &) {
            try {
                scaleZ = static_cast<double>(static_cast<int>(scale["z"]));
            } catch (const libconfig::ConfigException &) {
            }
        }
        allMatrix["scale"] = {
            {scaleX, 0.0, 0.0, 0.0},
            {0.0, scaleY, 0.0, 0.0},
            {0.0, 0.0, scaleZ, 0.0},
            {0.0, 0.0, 0.0, 1.0}
        };
    } catch (const libconfig::SettingNotFoundException &) {
    }
}

void core::SceneParser::calcFinalTransformationMatrix(
    map<string, math::Matrix<double>> &allMatrix
)
{
    allMatrix["final"] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    if (allMatrix.contains("translation")) {
        allMatrix["final"] *= allMatrix["translation"];
    }
    if (allMatrix.contains("scale")) {
        allMatrix["final"] *= allMatrix["scale"];
    }
    if (allMatrix.contains("rotation")) {
        allMatrix["final"] *= allMatrix["rotation"];
    } else {
        if (allMatrix.contains("rotationX")) {
            allMatrix["final"] *= allMatrix["rotationX"];
            allMatrix["final"] *= allMatrix["rotationY"];
            allMatrix["final"] *= allMatrix["rotationZ"];
        }
    }
}

void core::SceneParser::parseFile(const string &filename)
{
    ifstream file;
    const std::filesystem::path pathObj(filename);
    const string path = pathObj.parent_path().string();
    file.open(filename);
    if (!file.is_open()) {
        throw raytracer::SceneParserError(
            "Error: could not open file " + filename
        );
    }
    libconfig::Config configuationParser;
    try {
        configuationParser.readFile(filename.c_str());
    } catch (const libconfig::FileIOException &) {
        throw raytracer::SceneParserError("I/O error while reading file.");
    } catch (const libconfig::ParseException &pex) {
        const string fileError = pex.getFile();
        const string Error = pex.getError();
        throw raytracer::SceneParserError(
            format("Parse error at {}: {} - {}",
            fileError, pex.getLine(), Error)
        );
    }

    if (configuationParser.exists("import")) {
        const libconfig::Setting& imports = configuationParser.lookup("import");
        if (imports.getType() == libconfig::Setting::TypeList) {
            int size = imports.getLength();
            for (int i = 0; i < size; i++) {
                string filePath = imports[i];
                if (!path.empty()) {
                    filePath = path + "/" + filePath;
                }
                parseFile(filePath);
            }
        } else if (imports.getType() == libconfig::Setting::TypeString) {
            string filePath = imports;
            if (!path.empty()) {
                filePath = path + "/" + filePath;
            }
            parseFile(filePath);
        }
    }
    parseCamera(configuationParser);
    parsePrimitive(configuationParser);
    parseLights(configuationParser);
}

bool core::SceneParser::hasBasicElementInFiles()
{
    if ((mCamera.width == 0) || (mCamera.height == 0)) {
        cerr << "Camera setting not found in configuration(s) file(s)\n";
        return false;
    }
    if (mCylinders.empty() && mCones.empty()
        && mPlanes.empty() && mSpheres.empty()) {
        cerr << "Primitives not found in configuration(s) file(s)\n";
        return false;
    }
    if (mDirectionalLights.empty() && mPointLights.empty()) {
        cerr << "Light not found in configuration(s) file(s)\n";
        return false;
    }
    return true;
}
