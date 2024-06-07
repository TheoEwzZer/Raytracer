/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene
*/

#include "Ray.hpp"
#include "Rectangle3D.hpp"
#include "Scene.hpp"
#include "SceneParser.hpp"
#include "designPatterns/Factory.hpp"
#include "math/Point3D.hpp"
#include <array>
#include <random>

using std::array;
using std::make_unique;
using std::size_t;
using std::tan;
using std::unique_ptr;
using std::numeric_limits;

raytracer::Color raytracer::Scene::getLightColor(
    const IPrimitive &primitive,
    const math::Point3D &intersectionPoint, const math::Vector3D &normal)
{
    Color color = primitive.mBaseColor * mAmbient;
    Color attenuation;
    double angle = 0.0;

    if (!mIsFastRender) {
        for (const auto &light : mLights) {
            angle = normal.dot(math::Vector3D::normalize(
                light.get()->mBaseOrigin - intersectionPoint
            ));
            if (angle <= 0.0) {
                continue;
            }
            attenuation = light.get()->getColorShadow(
                intersectionPoint, normal, mPrimitives
            ) * light.get()->getColorDistance(intersectionPoint);
            color += (attenuation * angle * primitive.mBaseColor * mDiffuse);
        }
    }
    color.clamp();
    return color;
}

raytracer::Color raytracer::Scene::getColor(
    const unsigned int x, const unsigned int y,
    const unsigned int height, const unsigned int width)
{
    Color color(0.0, 0.0, 0.0);
    math::Point3D intersectionPoint;
    math::Vector3D normal;
    const size_t nbPrimitives = mPrimitives.size();
    const int numSamples = mIsFastRender ? 1 : 10;
    double hitResult = 0.0;
    double u = 0.0;
    double v = 0.0;
    raytracer::Ray r;
    double closestHit = numeric_limits<double>::max();
    size_t closestPrimitiveIndex = numeric_limits<size_t>::max();

    for (int i = 0; i < numSamples; i++) {
        u = (static_cast<double>(x) + mDis(mGen)) / width;
        v = (static_cast<double>(y) + mDis(mGen)) / height;
        r = mCamera.ray(u, v);
        closestHit = numeric_limits<double>::max();
        closestPrimitiveIndex = numeric_limits<size_t>::max();
        for (size_t j = 0; j < nbPrimitives; j++) {
            hitResult = mPrimitives[j].get()->hits(r);
            if ((hitResult > 0.0) && (hitResult < closestHit)) {
                closestHit = hitResult;
                closestPrimitiveIndex = j;
            }
        }
        if (closestPrimitiveIndex != numeric_limits<size_t>::max()) {
            intersectionPoint = r.mOrigin + (r.mDirection * closestHit);
            normal = math::Vector3D::normalize(
                mPrimitives[closestPrimitiveIndex].get()->getNormal(
                    intersectionPoint
                )
            );
            color += getLightColor(
                *mPrimitives[closestPrimitiveIndex],
                intersectionPoint,
                normal
            );
        }
    }
    color /= numSamples;
    return color;
}

void raytracer::Scene::render(raytracer::Image &image)
{
    raytracer::Color color;
    const unsigned int height = image.getHeight();
    const unsigned int width = image.getWidth();

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            color = getColor(x, y, height, width);
            image.setPixel(x, y, color);
        }
    }
}

void raytracer::Scene::initPlanes(const vector<Plane> &planes,
    const size_t o, Factory &factory)
{
    const size_t nbPlanes = planes.size();
    map<string, math::Matrix<double>> matrix;
    double transformation = 0.0;

    for (size_t i = 0; i < nbPlanes; i++) {
        transformation = 0.0;
        mPrimitives.push_back(
            factory.createPrimitive(Factory::PrimitiveType::PLANE)
        );
        mPrimitives[i + o].get()->mBaseColor = planes[i].mColor;
        matrix = planes[i].mAllMatrix;
        if (planes[i].mAllMatrix.contains("translation")) {
            transformation = matrix["translation"](0, 1);
        }
        mPrimitives[i + o].get()->mBasePosition =
            static_cast<int>(planes[i].mPosition + transformation);
        mPrimitives[i + o].get()->mBaseAxis = planes[i].mAxis;
        mPrimitives[i + o].get()->mBaseAllMatrix = planes[i].mAllMatrix;
        mPrimitives[i + o].get()->mBaseRotation = planes[i].mVectorRotation;
    }
}

void raytracer::Scene::initSpheres(const vector<Sphere> &spheres,
    const size_t o, Factory &factory)
{
    const size_t nbSpheres = spheres.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbSpheres; i++) {
        mPrimitives.push_back(
            factory.createPrimitive(Factory::PrimitiveType::SPHERE)
        );
        if (spheres[i].mAllMatrix.contains("translation")) {
            matrix = spheres[i].mAllMatrix;
            mPrimitives[i + o].get()->mBaseCenter = math::Point3D(
                spheres[i].mX + matrix["translation"](0, 3),
                spheres[i].mY + matrix["translation"](1, 3),
                spheres[i].mZ + matrix["translation"](2, 3)
            );
        } else {
            mPrimitives[i + o].get()->mBaseCenter = math::Point3D(
                static_cast<double>(spheres[i].mX),
                static_cast<double>(spheres[i].mY),
                static_cast<double>(spheres[i].mZ)
            );
        }
        if (spheres[i].mAllMatrix.contains("scale")) {
            matrix = spheres[i].mAllMatrix;
            mPrimitives[i + o].get()->mBaseRadius = spheres[i].mRadius
            * (matrix["scale"](0, 0)
            * matrix["scale"](1, 1)
            * matrix["scale"](2, 2));
        } else {
            mPrimitives[i + o].get()->mBaseRadius = spheres[i].mRadius;
        }
        mPrimitives[i + o].get()->mBaseColor = spheres[i].mColor;
        mPrimitives[i + o].get()->mBaseAllMatrix = spheres[i].mAllMatrix;
        mPrimitives[i + o].get()->mBaseRotation = spheres[i].mVectorRotation;
    }
}

void raytracer::Scene::initCylinders(const vector<Cylinder> &cylinders,
    const size_t o, Factory &factory)
{
    const size_t nbCylinders = cylinders.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbCylinders; i++) {
        mPrimitives.push_back(
            factory.createPrimitive(Factory::PrimitiveType::CYLINDER)
        );
        mPrimitives[i + o].get()->mBaseColor = cylinders[i].mColor;
        if (cylinders[i].mAllMatrix.contains("translation")) {
            matrix = cylinders[i].mAllMatrix;
            mPrimitives[i + o].get()->mBaseCenter = math::Point3D(
                cylinders[i].mX + matrix["translation"](0, 3),
                cylinders[i].mY + matrix["translation"](1, 3),
                cylinders[i].mZ + matrix["translation"](2, 3)
            );
        } else {
            mPrimitives[i + o].get()->mBaseCenter = math::Point3D(
                static_cast<double>(cylinders[i].mX),
                static_cast<double>(cylinders[i].mY),
                static_cast<double>(cylinders[i].mZ)
            );
        }
        if (cylinders[i].mAllMatrix.contains("scale")) {
            matrix = cylinders[i].mAllMatrix;
            mPrimitives[i + o].get()->mBaseRadius = cylinders[i].mRadius
            * matrix["scale"](0, 0);
            mPrimitives[i + o].get()->mBaseHeight = cylinders[i].mHeight
            * matrix["scale"](1, 1);
        } else {
            mPrimitives[i + o].get()->mBaseRadius = cylinders[i].mRadius;
            mPrimitives[i + o].get()->mBaseHeight = cylinders[i].mHeight;
        }
        mPrimitives[i + o].get()->mBaseAllMatrix = cylinders[i].mAllMatrix;
        mPrimitives[i + o].get()->mBaseRotation = cylinders[i].mVectorRotation;
    }
}

void raytracer::Scene::initCones(const vector<Cone> &cones,
    const size_t o, Factory &factory)
{
    const size_t nbCones = cones.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbCones; i++) {
        mPrimitives.push_back(
            factory.createPrimitive(Factory::PrimitiveType::CONE)
        );
        mPrimitives[i + o].get()->mBaseColor = cones[i].mColor;
        if (cones[i].mAllMatrix.contains("translation")) {
            matrix = cones[i].mAllMatrix;
            mPrimitives[i + o].get()->mBaseCenter = math::Point3D(
                cones[i].mX + matrix["translation"](0, 3),
                cones[i].mY + matrix["translation"](1, 3),
                cones[i].mZ + matrix["translation"](2, 3)
            );
        } else {
            mPrimitives[i + o].get()->mBaseCenter = math::Point3D(
                static_cast<double>(cones[i].mX),
                static_cast<double>(cones[i].mY),
                static_cast<double>(cones[i].mZ)
            );
        }
        if (cones[i].mAllMatrix.contains("scale")) {
            matrix = cones[i].mAllMatrix;
            mPrimitives[i + o].get()->mBaseRadius = cones[i].mRadius
            * matrix["scale"](0, 0);
            mPrimitives[i + o].get()->mBaseHeight = cones[i].mHeight
            * matrix["scale"](1, 1);
        } else {
            mPrimitives[i + o].get()->mBaseRadius = cones[i].mRadius;
            mPrimitives[i + o].get()->mBaseHeight = cones[i].mHeight;
        }
        mPrimitives[i + o].get()->mBaseAllMatrix = cones[i].mAllMatrix;
        mPrimitives[i + o].get()->mBaseRotation = cones[i].mVectorRotation;
    }
}

void raytracer::Scene::initPoints(const vector<PointLight> &points,
    const size_t o, Factory &factory)
{
    const size_t nbPoints = points.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbPoints; i++) {
        mLights.push_back(
            factory.createLight(Factory::LightType::POINT)
        );
        if (points[i].mAllMatrix.contains("translation")) {
            matrix = points[i].mAllMatrix;
            mLights[i + o].get()->mBaseOrigin = math::Point3D(
                points[i].mOrigin.mX + matrix["translation"](0, 3),
                points[i].mOrigin.mY + matrix["translation"](1, 3),
                points[i].mOrigin.mZ + matrix["translation"](2, 3)
            );
        } else {
            mLights[i + o].get()->mBaseOrigin = math::Point3D(
                points[i].mOrigin.mX,
                points[i].mOrigin.mY,
                points[i].mOrigin.mZ
            );
        }
        mLights[i + o].get()->mBaseColor = Color(
            points[i].mColor.getRed(),
            points[i].mColor.getGreen(),
            points[i].mColor.getBlue()
        );
        mLights[i + o].get()->mBaseVectorRotation = points[i].mVectorRotation;
    }
}

void raytracer::Scene::initDirectionals(const vector<DirectionalLight> &directionals,
    const size_t o, Factory &factory)
{
    const size_t nbDirectionals = directionals.size();
    map<string, math::Matrix<double>> matrix;

    for (size_t i = 0; i < nbDirectionals; i++) {
        mLights.push_back(
            factory.createLight(Factory::LightType::DIRECTIONAL)
        );
        if (directionals[i].mAllMatrix.contains("translation")) {
            matrix = directionals[i].mAllMatrix;
            mLights[i + o].get()->mBaseOrigin = math::Point3D(
                directionals[i].mOrigin.mX + matrix["translation"](0, 3),
                directionals[i].mOrigin.mY + matrix["translation"](1, 3),
                directionals[i].mOrigin.mZ + matrix["translation"](2, 3)
            );
        } else {
            mLights[i + o].get()->mBaseOrigin = math::Point3D(
                directionals[i].mOrigin.mX,
                directionals[i].mOrigin.mY,
                directionals[i].mOrigin.mZ
            );
        }
        mLights[i + o].get()->mBaseDirection = math::Vector3D(
            directionals[i].mDirection.mX,
            directionals[i].mDirection.mY,
            directionals[i].mDirection.mZ
        );
        mLights[i + o].get()->mBaseColor = Color(
            directionals[i].mColor.getRed(),
            directionals[i].mColor.getGreen(),
            directionals[i].mColor.getBlue()
        );
        mLights[i + o].get()->mBaseVectorRotation = directionals[i].mVectorRotation;
    }
}

void raytracer::Scene::init(const core::SceneParser &sceneParser)
{
    Factory factory;
    const vector<Cylinder> cylinders = sceneParser.getCylinders();
    const vector<DirectionalLight> directionalLights =
        sceneParser.getDirectionalLights();
    const vector<Plane> planes = sceneParser.getPlanes();
    const vector<PointLight> pointLights = sceneParser.getPointLights();
    const vector<Sphere> spheres = sceneParser.getSpheres();
    const vector<Cone> cones = sceneParser.getCones();
    map<string, math::Matrix<double>> matrix;

    initPlanes(planes, mPrimitives.size(), factory);
    initSpheres(spheres, mPrimitives.size(), factory);
    initCylinders(cylinders, mPrimitives.size(), factory);
    initCones(cones, mPrimitives.size(), factory);
    initPoints(pointLights, mLights.size(), factory);
    initDirectionals(directionalLights, mLights.size(), factory);
    mCamera.fieldOfView = mCamera.fieldOfView * (M_PI / 180.0);
    const double screenDistance =  1 / (2 * ::tan(mCamera.fieldOfView / 2.0));
    const double aspectRatio = static_cast<double>(
        mCamera.width
    ) / static_cast<double>(mCamera.height);
    const double z = mCamera.posZ - screenDistance;
    const math::Point3D screenOrigin(mCamera.posX, mCamera.posY, z);
    const math::Vector3D bottomSide(-aspectRatio, -1, z);
    const math::Vector3D leftSide(aspectRatio, 1, z);
    mCamera.mScreen = Rectangle3D(screenOrigin, bottomSide, leftSide);
    mCamera.mOrigin = screenOrigin;
    mAmbient = sceneParser.getAmbient();
    mDiffuse = sceneParser.getDiffuse();
}

void raytracer::Scene::setFastRender(const bool isFastRender)
{
    mIsFastRender = isFastRender;
}
