#include "raytracers/ray-tracer-v3.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

imaging::Color raytracer::raytracers::_private_::RayTracerv3::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const
{
    Color result = colors::black();

    result += compute_diffuse(properties, hit, ray, light_ray);
    result += compute_specular(properties, hit, ray, light_ray);

    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerv3::compute_specular(const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const
{
    Color result = colors::black();
    if (properties.specular != colors::black()) {
        math::Point3D l = light_ray.ray.origin;
        math::Point3D p = hit.position;
        math::Point3D e = ray.origin;
        Color cl = light_ray.color;
        Color cp = properties.specular;
        auto i = (p - l).normalized();
        auto r = i.reflect_by(hit.normal);
        auto v = (e - p).normalized();
        auto cos_alpha = v.dot(r);

        if (cos_alpha > 0) {
            return cl * cp * pow(cos_alpha, properties.specular_exponent);
        }
    }
    return result;
}

raytracer::RayTracer raytracer::raytracers::v3()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerv3>());
}
