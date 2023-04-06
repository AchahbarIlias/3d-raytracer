#pragma once
#include "primitives/transformer-primitive.h"


namespace raytracer
{
    namespace primitives
    {
        Primitive resize_x(Primitive child, double size);
        Primitive resize_y(Primitive child, double size);
        Primitive resize_z(Primitive child, double size);
        Primitive resize_x_uniform(Primitive child, double size);
        Primitive resize_y_uniform(Primitive child, double size);
        Primitive resize_z_uniform(Primitive child, double size);
    }
}