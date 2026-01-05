#pragma once

#include "Direction.hpp"

#include <array>
#include <iostream>

struct Point{
    Point() = default;
    Point(int x, int y) : x{x}, y{y} {}

    auto operator<=>(const Point &other) const = default;

    Point operator+(const Direction &d) const{
        return Point(x + d.dx, y + d.dy);
    }
    Point &operator+=(const Direction &d){
        x += d.dx;
        y += d.dy;
        return *this;
    }
    Point operator-(const Direction &d) const{
        return Point(x - d.dx, y - d.dy);
    }
    Point &operator-=(const Direction &d){
        x -= d.dx;
        y -= d.dy;
        return *this;
    }
    Direction operator-(const Point &other){
        return Direction(this->x - other.x, this->y - other.y);
    }

    int x{0}, y{0};
};

std::ostream &operator<<(std::ostream &os, const Point &p){
    return os << p.x << ',' << p.y;
}
std::istream &operator>>(std::istream &is, Point &p){
    is >> p.x;
    if(is.peek()){
        is.ignore();
    }
    is >> p.y;
    return is;
}