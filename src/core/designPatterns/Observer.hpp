/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Observer
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <memory>

using std::string;
using std::function;
using std::unordered_map;
using std::vector;
using std::unique_ptr;

namespace raytracer {
    class IInputObserver {
        public:
            IInputObserver() = default;
            virtual ~IInputObserver() = default;
            virtual void onKeyPressed(const sf::Keyboard::Key k,
                const string &path) = 0;
    };

    class InputManager {
        public:
            InputManager() = default;
            ~InputManager() = default;

            void addObserver(unique_ptr<IInputObserver> observer);
            void actionKeyPressed(sf::Keyboard::Key k, const string &path);
            void bindKeyAction(
                const sf::Keyboard::Key k, const function<void(string)> &action
            );
        private:
            vector<unique_ptr<IInputObserver>> mObservers;
            unordered_map<
                sf::Keyboard::Key,
                function<void(string)>> mKeyActionsManager;
    };

    class InputObserver : public IInputObserver {
        public:
            InputObserver() = default;
            ~InputObserver() override = default;
            void onKeyPressed(
                const sf::Keyboard::Key k, const string &path
            ) override;
            void bindKeyAction(
                const sf::Keyboard::Key k, const function<void(string)> &action
            );
        private:
            unordered_map<
                sf::Keyboard::Key,
                function<void(string)>> mKeyActionsObserver;
    };
}
