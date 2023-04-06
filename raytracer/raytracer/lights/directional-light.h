#pragma once

#include "lights/point-light.h"
#include "imaging/color.h"
#include "math/point.h"
#include <memory>

namespace raytracer
{
    namespace lights
    {
        LightSource directional(const math::Vector3D& direction,
            const imaging::Color& color);
    }
}