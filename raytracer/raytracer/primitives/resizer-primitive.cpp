#include "primitives/resizer-primitive.h"
using namespace math;
using namespace raytracer;
using namespace raytracer::primitives;

Primitive raytracer::primitives::resize_x(Primitive child, double size)
{
    auto width = child->bounding_box().x().size();
    auto factor = size / width;
    return raytracer::primitives::scale(factor, 1, 1, child);
}

Primitive raytracer::primitives::resize_y(Primitive child, double size)
{
    auto width = child->bounding_box().y().size();
    auto factor = size / width;
    return raytracer::primitives::scale(1, factor, 1, child);
}

Primitive raytracer::primitives::resize_z(Primitive child, double size)
{
    auto width = child->bounding_box().z().size();
    auto factor = size / width;
    return raytracer::primitives::scale(1, 1, factor, child);
}






Primitive raytracer::primitives::resize_x_uniform(Primitive child, double size)
{
    auto width = child->bounding_box().x().size();
    auto factor = size / width;
    return raytracer::primitives::scale(factor, factor, factor, child);
}

Primitive raytracer::primitives::resize_y_uniform(Primitive child, double size)
{
    auto width = child->bounding_box().y().size();
    auto factor = size / width;
    return raytracer::primitives::scale(factor, factor, factor, child);
}

Primitive raytracer::primitives::resize_z_uniform(Primitive child, double size)
{
    auto width = child->bounding_box().z().size();
    auto factor = size / width;
    return raytracer::primitives::scale(factor, factor, factor, child);
}