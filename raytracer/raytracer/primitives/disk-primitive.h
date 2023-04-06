#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
    namespace primitives
    {
        Primitive xy_disk(double radius);
        Primitive xz_disk(double radius);
        Primitive yz_disk(double radius);
    }
}