#pragma once

#include <string>
#include <vector>
#include "point.h"
#include "affine_transform.h"

namespace io
{
    struct InputData
    {
        long n=0;
        Point start;
        std::vector<AffineTransform> transforms;
    };
    //reads and parses the input file
    InputData read_input(const std::string &filename);
}