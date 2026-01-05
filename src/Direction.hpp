#pragma once

#include <iostream>
#include <array>

struct Direction{
    Direction() = default;
    Direction(int dx, int dy) : dx{dx}, dy{dy} {}

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