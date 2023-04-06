#pragma once

#include "lights/point-light.h"
#include "imaging/color.h"
#include "math/point.h"
#include <memory>

namespace raytracer
{
	namespace lights
	{
		/// <summary>
		/// Creates a spot light. This is a light source and
		/// produces photons of the given <paramref name="color" /> as if blocked by a cone.
		/// </summary>
		LightSource spot(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::Color& color);
		LightSource spot(const math::Point3D& position, const math::Point3D& target, math::Angle angle, const imaging::Color& color);
	}
}
