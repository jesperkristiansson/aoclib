#pragma once

#include "Direction.hpp"

#include <array>
#include <iostream>

template <unsigned N>
struct PointND{
    PointND() = default;
    PointND(std::array<int, N> values) : values(values) {}

    auto operator<=>(const PointND<N> &other) const = default;

    int operator[](size_t i) const{
        return values[i];
    }
    int& operator[](size_t i){
        return values[i];
    }

    PointND<N> operator+(const DirectionND<N> &d) const{
        PointND<N> newPoint = *this;
        newPoint += d;
        return newPoint;
    }
    PointND<N> &operator+=(const DirectionND<N> &d){
        for(size_t i = 0; i < N; i++){
            values[i] += d[i];
        }
        return *this;
    }
    PointND<N> operator-(const DirectionND<N> &d) const{
        PointND<N> newPoint = *this;
        newPoint -= d;
        return newPoint;
    }
    PointND<N> &operator-=(const DirectionND<N> &d){
        for(size_t i = 0; i < N; i++){
            values[i] -= d[i];
        }
        return *this;
    }
    DirectionND<N> operator-(const PointND<N> &other){
        std::array<int, N> diff;
        for(size_t i = 0; i < N; i++){
            diff[i] = values[i] - other.values[i];
        }
        return Direction(diff);
    }

    std::array<int, N> values{};
};

template<unsigned N>
std::ostream &operator<<(std::ostream &os, const PointND<N> &p){
    os << p[0];
    for(size_t i = 1; i < N; i++){
        os << ',' << p[i];
    }
    return os;
}
template<unsigned N>
std::istream &operator>>(std::istream &is, PointND<N> &p){
    is >> p[0];
    for(size_t i = 1; i < N; i++){
        if(is.peek()){
            is.ignore();
        }
        is >> p[i];
    }
    return is;
}

// Forward declaration to avoid circular dependency between Point and Point2D due to both having implicit conversion from the other
struct Point;

struct Point2D : private PointND<2>{
    using PointND<2>::PointND;
    Point2D(int x, int y) : PointND<2>({x, y}) {}
    // Allow implicit conversion both ways for backwards compatability
    Point2D(Point);

    int x() const{
        return values[0];
    }
    int& x(){
        return values[0];
    }
    int y() const{
        return values[1];
    }
    int& y(){
        return values[1];
    }
};

struct Point3D : private PointND<3>{
    using PointND<3>::PointND;
    Point3D(int x, int y, int z) : PointND<3>({x, y, z}) {}

    int x() const{
        return values[0];
    }
    int& x(){
        return values[0];
    }
    int y() const{
        return values[1];
    }
    int& y(){
        return values[1];
    }
    int z() const{
        return values[2];
    }
    int& z(){
        return values[2];
    }
};

// This should be replaced with Point2D, but that requires refactoring e.g. p.x to p.x()
struct Point{
    Point() = default;
    Point(int x, int y) : x{x}, y{y} {}
    // Allow implicit conversion both ways for backwards compatability
    Point(Point2D);

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

Point2D::Point2D(Point p) : Point2D(p.x, p.y) {}
Point::Point(Point2D p) : x{p.x()}, y{p.y()} {}