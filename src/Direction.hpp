#pragma once

#include <iostream>
#include <array>

template<unsigned N>
struct DirectionND{
    DirectionND() = default;
    DirectionND(std::array<int, N> values) : values(values) {}

    auto operator<=>(const DirectionND<N> &other) const = default;

    static unsigned dimensions(){
        return N;
    }

    int operator[](size_t i) const{
        return values[i];
    }
    int& operator[](size_t i){
        return values[i];
    }

    DirectionND<N> operator*(int mult) const{
        std::array<int, N> newValues;
        for(size_t i = 0; i < N; i++){
            newValues[i] = values[i] * mult;
        }
        return DirectionND<N>(newValues);
    }
    DirectionND<N> operator+(DirectionND<N> other) const{
        std::array<int, N> newValues;
        for(size_t i = 0; i < N; i++){
            newValues[i] = values[i] + other.values[i];
        }
        return DirectionND<N>(newValues);
    }

    std::array<int, N> values{};
};

template<unsigned N>
std::ostream &operator<<(std::ostream &os, const DirectionND<N> &d){
    os << d[0];
    for(size_t i = 1; i < N; i++){
       os << ',' << d[i];
    }
    return os;
}

// Forward declaration to avoid circular dependency between Direction and Direction2D due to both having implicit conversion from the other
struct Direction;

struct Direction2D : private DirectionND<2>{
    using DirectionND<2>::DirectionND;
    Direction2D(int dx, int dy) : DirectionND<2>({dx, dy}) {}
    // Allow implicit conversion both ways for backwards compatability
    Direction2D(Direction);

    int dx() const{
        return values[0];
    }
    int& dx(){
        return values[0];
    }
    int dy() const{
        return values[1];
    }
    int& dy(){
        return values[1];
    }

    Direction2D rotateRight() const{
        return Direction2D(-dy(), dx());
    }
    Direction2D rotateLeft() const{
        return Direction2D(dy(), -dx());
    }
};


struct Direction3D : private DirectionND<3>{
    using DirectionND<3>::DirectionND;
    Direction3D(int dx, int dy, int dz) : DirectionND<3>({dx, dy, dz}) {}

    int dx() const{
        return values[0];
    }
    int& dx(){
        return values[0];
    }
    int dy() const{
        return values[1];
    }
    int& dy(){
        return values[1];
    }
    int dz() const{
        return values[2];
    }
    int& dz(){
        return values[2];
    }
};

// This should be replaced with Direction2D, but that requires refactoring e.g. dir.dx to dir.dx()
struct Direction{
    Direction() = default;
    Direction(int dx, int dy) : dx{dx}, dy{dy} {}
    // Allow implicit conversion both ways for backwards compatability
    Direction(Direction2D);

    auto operator<=>(const Direction &other) const = default;

    Direction operator*(int mult) const{
        return Direction(dx*mult, dy*mult);
    }
    Direction operator+(Direction other) const{
        return Direction(dx+other.dx, dy+other.dy);
    }

    Direction rotateRight() const{
        return Direction(-dy, dx);
    }
    Direction rotateLeft() const{
        return Direction(dy, -dx);
    }

    int dx{0}, dy{0};
};

std::ostream &operator<<(std::ostream &os, const Direction &d){
    return os << d.dx << ',' << d.dy;
}

const inline Direction NORTH(0, -1);
const inline Direction SOUTH(0, 1);
const inline Direction EAST(1, 0);
const inline Direction WEST(-1, 0);

Direction2D::Direction2D(Direction d) : Direction2D(d.dx, d.dy) {}
Direction::Direction(Direction2D d) : dx{d.dx()}, dy{d.dy()} {}
