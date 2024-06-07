/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color
*/

#include "Color.hpp"

using std::abs;

[[nodiscard]] double raytracer::Color::getRed() const
{
    return mRed;
}

[[nodiscard]] double raytracer::Color::getGreen() const
{
    return mGreen;
}

[[nodiscard]] double raytracer::Color::getBlue() const
{
    return mBlue;
}

void raytracer::Color::setRed(const double red)
{
    mRed = red;
}

void raytracer::Color::setGreen(const double green)
{
    mGreen = green;
}

void raytracer::Color::setBlue(const double blue)
{
    mBlue = blue;
}

ostream &operator<<(ostream &os, const raytracer::Color &c)
{
    os << static_cast<int>(c.getRed() * 255) << " "
        << static_cast<int>(c.getGreen() * 255) << " "
        << static_cast<int>(c.getBlue() * 255) << "\n";
    return os;
}

raytracer::Color raytracer::Color::operator*(const int other) const
{
    return raytracer::Color(mRed * other, mGreen * other, mBlue * other);
}

raytracer::Color raytracer::Color::operator*(const double other) const
{
    return raytracer::Color(mRed * other, mGreen * other, mBlue * other);
}

raytracer::Color raytracer::Color::operator*(const Color &other) const
{
    return raytracer::Color(
        mRed * other.mRed,
        mGreen * other.mGreen,
        mBlue * other.mBlue
    );
}

raytracer::Color &raytracer::Color::operator/=(const int other)
{
    mRed /= other;
    mGreen /= other;
    mBlue /= other;
    return *this;
}

raytracer::Color &raytracer::Color::operator+=(const Color &other)
{
    mRed += other.mRed;
    mGreen += other.mGreen;
    mBlue += other.mBlue;
    return *this;
}

raytracer::Color &raytracer::Color::operator+=(const double other)
{
    mRed = mRed + other;
    mGreen = mGreen + other;
    mBlue = mBlue + other;
    return *this;
}

raytracer::Color raytracer::Color::operator+(const double other) const
{
    return raytracer::Color(mRed + other, mGreen + other, mBlue + other);
}

raytracer::Color raytracer::Color::operator/(const int other) const
{
    return raytracer::Color(mRed / other, mGreen / other, mBlue / other);
}

void raytracer::Color::clamp()
{
    mRed = mRed < 0.0 ? 0.0 : mRed;
    mRed = mRed > 1.0 ? 1.0 : mRed;
    mGreen = mGreen < 0.0 ? 0.0 : mGreen;
    mGreen = mGreen > 1.0 ? 1.0 : mGreen;
    mBlue = mBlue < 0.0 ? 0.0 : mBlue;
    mBlue = mBlue > 1.0 ? 1.0 : mBlue;
}

