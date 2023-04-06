#include "lights/spot-light.h"

using namespace math;
using namespace raytracer;

namespace
{
	/// <summary>
	/// Implementation for spot lights.
	/// </summary>
	class SpotLight : public raytracer::lights::_private_::PointLightImplementation
	{
	public:
		SpotLight(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::Color& color)
			: PointLightImplementation(position), m_direction(direction), m_angle(angle), m_color(color) { }

	protected:
		LightRay cast_lightray_to(const math::Point3D& p) const override
		{
			// Create ray starting at the light source's position and going through p
			math::Ray ray(m_position, p);

			// P-L / |P-L|
			Vector3D u = (p - m_position).normalized();

			// u . v
			auto leftEquation = u.dot(m_direction);

			// cos angle/2
			auto rightEquation = cos(m_angle / 2);

			if (leftEquation >= rightEquation)
			{
				// Return color
				return LightRay(ray, m_color);
			}
			else {
				// Return Black
				return LightRay(ray, imaging::colors::black());
			}
		}

	private:
		Vector3D m_direction;
		math::Angle m_angle;
		imaging::Color m_color;
	};
}

LightSource raytracer::lights::spot(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::Color& color)
{
	return LightSource(std::make_shared<SpotLight>(position, direction, angle, color));
}

LightSource raytracer::lights::spot(const math::Point3D& position, const math::Point3D& target, math::Angle angle, const imaging::Color& color)
{
	Vector3D direction = (target - position).normalized();
	return LightSource(std::make_shared<SpotLight>(position, direction, angle, color));
}
