#pragma once
#include "point.h"

// 2D affine transformation y = A*x + b
struct AffineTransform
{
    double a11 = 1.0, a12 = 0.0;
    double a21 = 0.0, a22 = 1.0;
    double b1 = 0.0, b2 = 0.0;

    Point operator()(const Point &p) const
    {
        Point result;
        result.x = a11 * p.x + a12 * p.y + b1;
        result.y = a21 * p.x + a22 * p.y + b2;
        return result;
    }
};