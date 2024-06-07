/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Matrix
*/

#pragma once

#include "Vector3D.hpp"
#include "../error/Error.hpp"
#include <initializer_list>
#include <iostream>
#include <vector>
#include <format>

using std::cout;
using std::initializer_list;
using std::size_t;
using std::string;
using std::vector;
using std::format;

namespace math {

    template<typename T>
    class Matrix {
    public:
        Matrix(const size_t rows, const size_t cols)
            : mRows(rows), mCols(cols) {
            createMatrice();
            createInverseMatrice();
            setMatrixInverseIndentity();
            inverse();
        };

        Matrix() : mRows(0), mCols(0) {};

        math::Vector3D apply(const math::Vector3D &vectorToApply, const bool isInverse)
        {
            if (mMatrix.size() == 0) {
                return vectorToApply;
            }
            vector<T> tempData {
                                    vectorToApply.mX,
                                    vectorToApply.mY,
                                    vectorToApply.mZ,
                                    1.0};
            vector<vector<T>> res = createMatrixExtern(4, 1);
            if (!isInverse) {
                for (size_t x = 0; x < 4; x++) {
                    for (size_t y = 0; y < 1; y++) {
                        T sum = 0;
                        for (size_t z = 0; z < 4; z++) {
                            sum += mMatrix[x].at(z) * tempData[z];
                        }
                        res[x].at(y) = sum;
                    }
                }
            } else {
                inverse();
                for (size_t x = 0; x < 4; x++) {
                    for (size_t y = 0; y < 1; y++) {
                        T sum = 0;
                        for (size_t z = 0; z < 4; z++) {
                            sum += mInverseMatrix[x].at(z) * tempData[z];
                        }
                        res[x].at(y) = sum;
                    }
                }
            }
            return (math::Vector3D(res[0].at(0), res[1].at(0), res[2].at(0)));
        }

        T &operator()(const size_t row, const size_t col)
        {
            if ((row >= mRows) || (col >= mCols)) {
                const string error = (row >= mRows) ?
                    format("Row bigger than size->({}/{})", row, mRows) :
                    format("Col bigger than size->({}/{})", col, mCols);
                throw raytracer::MatrixError(error);
            }
            return mMatrix[row].at(col);
        };

        void operator+=(Matrix<T> &other)
        {
            checkSameSize(other);
            for (size_t y = 0; y < mRows; y++) {
                for (size_t x = 0; x < mCols; x++) {
                    mMatrix[y].at(x) += other(y, x);
                }
            }
        };

        void operator-=(Matrix<T> &other)
        {
            checkSameSize(other);
            for (size_t y = 0; y < mRows; y++) {
                for (size_t x = 0; x < mCols; x++) {
                    mMatrix[y].at(x) -= other(y, x);
                }
            }
        };

        void operator*=(Matrix<T> &other)
        {
            const size_t twoCols = other.getNbCols();
            if (mCols != other.getNbRows()) {
                throw raytracer::MatrixError("Size different for operator*=");
            }
            vector<vector<T>> res = vector<vector<T>>(mRows);
            for (size_t i = 0; i < mRows; i++) {
                res[i] = vector<T>(twoCols);
            }
            for (size_t x = 0; x < mRows; x++) {
                for (size_t y = 0; y < twoCols; y++) {
                    T sum = 0;
                    for (size_t z = 0; z < mCols; z++) {
                        sum += mMatrix[x].at(z) * other(z, y);
                    }
                    res[x].at(y) = sum;
                }
            }
            mMatrix = res;
        };

        void operator*=(T coef)
        {
            for (size_t y = 0; y < mRows; y++) {
                for (size_t x = 0; x < mCols; x++) {
                    mMatrix[y].at(x) *= coef;
                }
            }
        };

        Matrix<T> &operator=(Matrix<T> other)
        {
            if (this != &other) {
                mRows = other.getNbRows();
                mCols = other.getNbCols();
                mMatrix = other.mMatrix;
                mInverseMatrix = other.mInverseMatrix;
            }
            return (*this);
        };

        void operator=(const initializer_list<initializer_list<T>> &list)
        {
            size_t x = 0;
            size_t y = 0;

            if ((mRows == 0) && (mCols == 0)) {
                mRows = list.size();
                mCols = list.begin()->size();
                createMatrice();
                createInverseMatrice();
                setMatrixInverseIndentity();
                inverse();
            }
            for (auto &elem : list) {
                for (auto &elem2 : elem) {
                    mMatrix[y].at(x) = elem2;
                    x++;
                }
                y++;
                x = 0;
            }
        };

        [[nodiscard]] size_t getNbRows() const
        {
            return mRows;
        };

        [[nodiscard]] size_t getNbCols() const
        {
            return mCols;
        };

        void displayMatrix()
        {
            for (size_t i = 0; i < mRows; i++) {
                for (size_t j = 0; j < mCols; j++) {
                    std::cout << "(" << i << ", " << j << ") = "
                    << mMatrix[i].at(j) << "\n";
                }
            }
        }

    private:
        vector<vector<T>> mMatrix = vector<vector<T>>();
        vector<vector<T>> mInverseMatrix = vector<vector<T>>();
        size_t mRows;
        size_t mCols;

        void checkSameSize(const Matrix<T> &other) const
        {
            if ((mRows != other.getNbRows()) || (mCols != other.getNbCols())) {
                throw MatrixError(mRows != other.getNbRows() ?
                "Sizes are different (rows differents)":
                "Sizes are different (cols differents)");
            }
        };

        void createMatrice()
        {
            mMatrix = vector<vector<T>>(mRows);
            for (size_t i = 0; i < mRows; i++) {
                mMatrix[i] = vector<T>(mCols);
            }
        }

        void createInverseMatrice()
        {
            mInverseMatrix = vector<vector<T>>(mRows);
            for (size_t i = 0; i < mRows; i++) {
                mInverseMatrix[i] = vector<T>(mCols);
            }
        }

        void setMatrixIndentity()
        {
            if (mRows == mCols) {
                for (size_t i = 0; i < mRows; i++) {
                    mMatrix[i][i] = 1;
                }
            }
        }

        void setMatrixInverseIndentity()
        {
            if (mRows == mCols) {
                for (size_t i = 0; i < mRows; i++) {
                    mInverseMatrix[i][i] = 1;
                }
            }
        }

        vector<vector<T>> createMatrixExtern(size_t rows, size_t cols)
        {
            vector<vector<T>> newMatrix = vector<vector<T>>(rows);
            for (size_t i = 0; i < rows; i++) {
                newMatrix[i] = vector<T>(cols);
            }
            return newMatrix;
        }
        void inverse()
        {
            vector<vector<T>> tmpMatrix = mMatrix;
            for (size_t i = 0; i < mRows; i++) {
                size_t pivotRow = i;
                for (size_t j = i + 1; j < mRows; j++) {
                    if (abs(tmpMatrix[j][i]) > abs(tmpMatrix[pivotRow][i])) {
                        pivotRow = j;
                    }
                }
                if (pivotRow != i) {
                    tmpMatrix[i].swap(tmpMatrix[pivotRow]);
                    mInverseMatrix[i].swap(mInverseMatrix[pivotRow]);
                }
                const double pivot = tmpMatrix[i][i];
                for (size_t j = 0; j < mCols; ++j) {
                    tmpMatrix[i][j] /= pivot;
                    mInverseMatrix[i][j] /= pivot;
                }
                for (size_t k = 0; k < mRows; ++k) {
                    if (k != i) {
                        const double factor = tmpMatrix[k][i];
                        for (size_t j = 0; j < mCols; ++j) {
                            tmpMatrix[k][j] -= factor * tmpMatrix[i][j];
                            mInverseMatrix[k][j] -= factor * mInverseMatrix[i][j];
                        }
                    }
                }
            }
        }
    };

    template<typename T>
    Matrix<T> operator+(Matrix<T> one, Matrix<T> two)
    {
        size_t oneRows = one.getNbRows();
        size_t oneCols = one.getNbCols();
        if ((oneRows != two.getNbRows()) || (oneCols != two.getNbCols())) {
            throw raytracer::MatrixError("Size different for operator+");
        }
        Matrix<T> result(oneRows, oneCols);
        for (size_t x = 0; x < oneRows; x++) {
            for (size_t y = 0; y < oneCols; y++) {
                result(x, y) = one(x, y) + two(x, y);
            }
        }
        return result;
    };

    template<typename T>
    Matrix<T> operator-(Matrix<T> one, Matrix<T> two)
    {
        size_t oneRows = one.getNbRows();
        size_t oneCols = one.getNbCols();
        if ((oneRows != two.getNbRows()) || (oneCols != two.getNbCols())) {
            throw raytracer::MatrixError("Size different for operator-");
        }
        Matrix<T> result(oneRows, oneCols);
        for (size_t x = 0; x < oneRows; x++) {
            for (size_t y = 0; y < oneCols; y++) {
                result(x, y) = one(x, y) - two(x, y);
            }
        }
        return result;
    };

    template<typename T>
    Matrix<T> operator*(Matrix<T> &one, Matrix<T> &two)
    {
        size_t oneRows = one.getNbRows();
        const size_t oneCols = one.getNbCols();
        size_t twoRows = two.getNbRows();
        const size_t twoCols = two.getNbCols();
        if (oneCols != twoRows) {
            throw raytracer::MatrixError("Size different for operator*");
        }
        Matrix<T> result(oneRows, twoCols);
        for (size_t x = 0; x < oneRows; x++) {
            for (size_t y = 0; y < twoCols; y++) {
                T sum = 0;
                for (size_t z = 0; z < oneCols; z++) {
                    sum += one(x, z) * two(z, y);
                }
                result(x, y) = sum;
            }
        }
        return result;
    }

    template<typename T>
    Matrix<T> operator*(T coef, Matrix<T> &one)
    {
        const size_t oneRows = one.getNbRows();
        const size_t oneCols = one.getNbCols();
        Matrix<T> result(oneRows, oneCols);

        for (size_t x = 0; x < oneRows; x++) {
            for (size_t y = 0; y < oneCols; y++) {
                result(x, y) = one(x, y) * coef;
            }
        }
        return result;
    }
}
