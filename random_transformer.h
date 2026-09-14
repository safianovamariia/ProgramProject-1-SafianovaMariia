#pragma once

#include <vector>
#include <random>
#include "point.h"
#include "affine_transform.h"

// randomly applies one of the affine transformations to a given point
class RandomAffineTransformer
{
public:
    RandomAffineTransformer(const std::vector<AffineTransform> &transforms);
    Point operator()(const Point &p);

private:
    std::vector<AffineTransform> transforms1;
    std::mt19937 engine1;
    std::uniform_int_distribution<std::size_t> pick1;
};