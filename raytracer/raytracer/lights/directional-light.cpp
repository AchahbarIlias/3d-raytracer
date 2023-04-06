#include "lights/directional-light.h"

using namespace math;
using namespace raytracer;

namespace
{
    /// <summary>
    /// Implementation for omnidirectional point lights.
    /// </summary>
    class DirectionalLight : public raytracer::lights::_private_::PointLightImplementation
    {
    public:
        DirectionalLight(const math::Vector3D& direction, const imaging::Color& color)
            : PointLightImplementation({ direction.x(), direction.y(), direction.z() }), _direction(direction), _color(color) { }

    protected:
        LightRay cast_lightray_to(const math::Point3D& point) const override
        {
            // Create ray starting at the light source's position and going through p
            const math::Point3D fake_origin = point - _direction * 100;
            const math::Ray ray(fake_origin, point);
            const LightRay lightray = LightRay(ray, _color);

            return LightRay(ray, _color);
        }

    private:
        imaging::Color _color;
        math::Vector3D _direction;
    };
}

LightSource raytracer::lights::directional(const math::Vector3D& direction, const imaging::Color& color)
{
    return LightSource(std::make_shared<DirectionalLight>(direction, color));
}