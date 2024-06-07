/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color
*/

#pragma once

#include <iostream>

using std::ostream;

namespace raytracer {
    class Color {
        public:
            Color() = default;
            Color(const double red, const double green, const double blue)
                : mRed(red), mGreen(green), mBlue(blue) {}
            ~Color() = default;

            Color &operator+=(const Color &other);
            Color &operator+=(const double other);
            Color &operator/=(const int other);
            Color operator*(const Color &other) const;
            Color operator*(const double other) const;
            Color operator*(const int other) const;
            Color operator+(const double other) const;
            Color operator/(const int other) const;

            [[nodiscard]] double getRed() const;
            [[nodiscard]] double getGreen() const;
            [[nodiscard]] double getBlue() const;
            void setRed(const double red);
            void setGreen(const double green);
            void setBlue(const double blue);
            void clamp();
        private:
            double mRed = 0;
            double mGreen = 0;
            double mBlue = 0;
    };
}

ostream &operator<<(ostream &os, const raytracer::Color &c);
