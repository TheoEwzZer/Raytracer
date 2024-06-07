/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Observer
*/

#include "Observer.hpp"

using std::size_t;
using std::string;
using std::function;
using std::move;

void raytracer::InputManager::addObserver(unique_ptr<IInputObserver> observer)
{
    mObservers.push_back(move(observer));
}

void raytracer::InputManager::actionKeyPressed(
    const sf::Keyboard::Key k, const string &path)
{
    const size_t size = mObservers.size();

    for (size_t i = 0; i < size; i++) {
        mObservers[i]->onKeyPressed(k, path);
    }
}

void raytracer::InputManager::bindKeyAction(
    const sf::Keyboard::Key k, const function<void(string)> &action
    )
{
    mKeyActionsManager[k] = action;
}

void raytracer::InputObserver::bindKeyAction(
    const sf::Keyboard::Key k, const function<void(string)> &action
    )
{
    mKeyActionsObserver[k] = action;
}

void raytracer::InputObserver::onKeyPressed(const sf::Keyboard::Key k,
    const string &path)
{
    if (mKeyActionsObserver.contains(k)) {
        mKeyActionsObserver[k](path);
    }
}
