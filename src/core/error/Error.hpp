/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-theo.fabiano
** File description:
** Error
*/

#pragma once

#include <stdexcept>
#include <string>

using std::exception;
using std::string;

namespace raytracer {
    class ArgumentError : public exception {
        public:
            explicit ArgumentError(const string &text) : mText(text) {}

            const char *what() const noexcept override {
                return mText.c_str();
            }
        private:
            string mText;
    };

    class FileParseError : public exception {
        public:
            explicit FileParseError(const string &text) : mText(text) {}

            const char *what() const noexcept override {
                return mText.c_str();
            }
        private:
            string mText;
    };

    class LibraryError : public exception {
        public:
            explicit LibraryError(const string &text) : mText(text) {}

            const char *what() const noexcept override {
                return mText.c_str();
            }
        private:
            string mText;
    };

    class MatrixError : public exception {
        public:
            explicit MatrixError(const string &text) : mText(text) {}

            const char *what() const noexcept override {
                return mText.c_str();
            }
        private:
            string mText;
    };

    class SceneParserError : public exception {
        public:
            explicit SceneParserError(const string &text) : mText(text) {}

            const char *what() const noexcept override {
                return mText.c_str();
            }
        private:
            string mText;
    };
}
