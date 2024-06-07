/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Image
*/

#pragma once

#include "Color.hpp"
#include <iostream>
#include <map>
#include <tuple>
#include "designPatterns/Observer.hpp"

using std::map;
using std::tuple;
using std::string;
using std::unique_ptr;

namespace raytracer {
    class Image {
        public:
            Image(const unsigned int width, const unsigned int height,
                const bool useSFML);
            ~Image() = default;

            unique_ptr<sf::RenderWindow> initializeWindow(
                const unsigned int width, const unsigned int height,
                const bool useSFML);
            void setPixel(const unsigned int x, const unsigned int y,
                const Color &color);
            void display(const string &sceneFile, const string &filepath,
                const bool isFastRenderer);
            void displayPPM(const string &filepath);

            [[nodiscard]] unsigned int getWidth() const;
            [[nodiscard]] unsigned int getHeight() const;
            void refreshPicture(const string &sceneFile, const string &filepath,
                const bool isFastRenderer);
        private:
            unsigned int mWidth;
            unsigned int mHeight;
            map<tuple<int, int>, Color> mPixels;
            std::unique_ptr<sf::RenderWindow> mWindow;
            sf::Texture mTexture;
            sf::Sprite mSprite;
    };
}
