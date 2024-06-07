/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

using std::pow;
using std::swap;

math::Vector3D raytracer::Cylinder::rotateX(math::Vector3D vectorBase)
{
    map<string, math::Matrix<double>>::iterator it = mBaseAllMatrix.find("rotationX");
    if (it == mBaseAllMatrix.end()) {
        return (vectorBase);
    }
    math::Vector3D result;
    result.mX = vectorBase.mX * it->second(0, 0) +
                vectorBase.mY * it->second(0, 1) +
                vectorBase.mZ * it->second(0, 2);

    result.mY = vectorBase.mX * it->second(1, 0) +
                vectorBase.mY * it->second(1, 1) +
                vectorBase.mZ * it->second(1, 2);

    result.mZ = vectorBase.mX * it->second(2, 0) +
                vectorBase.mY * it->second(2, 1) +
                vectorBase.mZ * it->second(2, 2);
    return result;
}

math::Vector3D raytracer::Cylinder::rotateY(math::Vector3D vectorBase)
{
    map<string, math::Matrix<double>>::iterator it = mBaseAllMatrix.find("rotationY");
    if (it == mBaseAllMatrix.end()) {
        return (vectorBase);
    }
    math::Vector3D result;
    result.mX = vectorBase.mX * it->second(0, 0) +
                vectorBase.mY * it->second(0, 1) +
                vectorBase.mZ * it->second(0, 2);

    result.mY = vectorBase.mX * it->second(1, 0) +
                vectorBase.mY * it->second(1, 1) +
                vectorBase.mZ * it->second(1, 2);

    result.mZ = vectorBase.mX * it->second(2, 0) +
                vectorBase.mY * it->second(2, 1) +
                vectorBase.mZ * it->second(2, 2);
    return result;
}

math::Vector3D raytracer::Cylinder::rotateZ(math::Vector3D vectorBase)
{
    map<string, math::Matrix<double>>::iterator it = mBaseAllMatrix.find("rotationZ");
    if (it == mBaseAllMatrix.end()) {
        return (vectorBase);
    }
    math::Vector3D result;
    result.mX = vectorBase.mX * it->second(0, 0) +
                vectorBase.mY * it->second(0, 1) +
                vectorBase.mZ * it->second(0, 2);

    result.mY = vectorBase.mX * it->second(1, 0) +
                vectorBase.mY * it->second(1, 1) +
                vectorBase.mZ * it->second(1, 2);

    result.mZ = vectorBase.mX * it->second(2, 0) +
                vectorBase.mY * it->second(2, 1) +
                vectorBase.mZ * it->second(2, 2);
    return result;
}

math::Vector3D raytracer::Cylinder::rotateVector(math::Vector3D dir)
{
    dir = rotateX(dir);
    dir = rotateY(dir);
    dir = rotateZ(dir);
    return (dir);
}

double raytracer::Cylinder::hits(const Ray &ray)
{
    const math::Vector3D rotatedDir = rotateVector(ray.mDirection);
    const math::Vector3D rotatedCenter = rotateVector(
        math::Vector3D(ray.mOrigin.mX, ray.mOrigin.mY, ray.mOrigin.mZ));
    const math::Vector3D oc =
    math::Point3D(rotatedCenter.mX, rotatedCenter.mY, rotatedCenter.mZ) - mBaseCenter;
    const double a = rotatedDir.dot(rotatedDir)
        - pow(rotatedDir.mZ, 2);
    const double b = 2.0
        * (oc.dot(rotatedDir) - (rotatedDir.mZ * oc.mZ));
    const double c = oc.dot(oc) - pow(oc.mZ, 2) - pow(mBaseRadius, 2);
    const double discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0) {
        return -1.0;
    }
    double t0 = (-b - ::sqrt(discriminant)) / (2.0 * a);
    double t1 = (-b + ::sqrt(discriminant)) / (2.0 * a);
    if (t0 > t1) {
        swap(t0, t1);
    }
    const double y0 = rotatedCenter.mZ + (t0 * rotatedDir.mZ);
    const double y1 = rotatedCenter.mZ + (t1 * rotatedDir.mZ);
    if (y0 < mBaseCenter.mZ) {
        if (y1 < mBaseCenter.mZ) {
            return -1;
        } else {
            return t0 + (
                    (t1 - t0) * ((mBaseCenter.mZ - y0) / (y1 - y0))
                );
        }
    } else if (y0 > (mBaseCenter.mZ + mBaseHeight)) {
        if (y1 > (mBaseCenter.mZ + mBaseHeight)) {
            return -1;
        } else {
            return t0 + (
                (t1 - t0) * (((mBaseCenter.mZ + mBaseHeight) - y0) / (y1 - y0))
            );
        }
    } else {
        return t0;
    }
}

math::Vector3D raytracer::Cylinder::getNormal(const math::Point3D &point) const
{
    math::Vector3D normal = point - mBaseCenter;
    normal.mZ = 0;

    normal.normalize();
    return normal;
}
