#pragma once
#include <compare>

// 2D point
struct Point
{
    double x = 0.0;
    double y = 0.0;
    auto operator<=>(const Point &other) const = default;
};