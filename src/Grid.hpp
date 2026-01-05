#pragma once

#include "Point.hpp"

#include <vector>
#include <iostream>
#include <optional>

template <typename T>
struct Grid{
    Grid() = default;
    Grid(int xMax, int yMax) : mat(yMax, std::vector<T>(xMax)), xMax{xMax}, yMax{yMax}{}
    template<typename TRange> requires std::same_as<typename TRange::value_type::value_type, T>
    Grid(const TRange& rangeRange){
        yMax = rangeRange.size();
        mat.reserve(yMax);
        for(const auto &r : rangeRange){
            xMax = r.size();
            mat.emplace_back();
            mat.reserve(xMax);
            for(T e : r){
                mat.back().push_back(e);
            }
        }
    }

    T &at(const Point2D &p){
        return mat[p.y()][p.x()];
    }
    const T &at(const Point2D &p) const{
        return mat[p.y()][p.x()];
    }
    bool contains(const Point2D &p) const{
        return p.x() >= 0 && p.x() < xMax && p.y() >= 0 && p.y() < yMax;
    }

    std::optional<Point2D> findFirst(const T &val) const {
        for(int y = 0; y < yMax; y++){
            for(int x = 0; x < xMax; x++){
                if(mat[y][x] == val){
                    return Point2D(x, y);
                }
            }
        }

        return std::nullopt;
    }

    std::vector<std::vector<T>> mat{};
    int xMax{0}, yMax{0};
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const Grid<T> &g){
    for(auto row : g.mat){
        for(auto val : row){
            os << val;
        }
        os << '\n';
    }
    return os;
}
