#include "random_transformer.h"
#include <stdexcept>

RandomAffineTransformer::RandomAffineTransformer(const std::vector<AffineTransform> &transforms)
    : transforms1(transforms), engine1(std::random_device{}()), pick1(0, transforms.empty() ? 0 : transforms.size()-1)
{
    if (transforms1.empty())
    {
        throw std::invalid_argument("Affine transformation list is empty");
    }
}

Point RandomAffineTransformer::operator()(const Point &p)
{
    std::size_t index = pick1(engine1);
    return transforms1[index](p);
}