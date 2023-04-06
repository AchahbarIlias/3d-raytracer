#pragma once

#include "lights/light-source.h"
#include "math/rectangle3d.h"
#include "samplers/samplers.h"

namespace raytracer
{
	namespace lights
	{
		LightSource arealight(const math::Rectangle3D rectangle3D, const Sampler sampler, const imaging::Color& color);
	}
}