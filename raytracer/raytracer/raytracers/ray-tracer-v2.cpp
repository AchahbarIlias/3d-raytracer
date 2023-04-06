#include "raytracers/ray-tracer-v2.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

imaging::Color raytracer::raytracers::_private_::RayTracerv2::determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const
{
    Color result = colors::black();

    result += this->RayTracerv1::determine_color(scene, properties, hit, ray);
    result += process_lights(scene, properties, hit, ray);
    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerv2::process_lights(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const
{
    Color result = colors::black();
    for each (LightSource light_source in scene.light_sources)
    {
        result += process_light_source(scene, properties, hit, ray, light_source);
    }
    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerv2::process_light_source(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightSource light_source) const
{
    Color result = colors::black();

    for each (LightRay light_ray in light_source->lightrays_to(hit.position))
    {
        result += process_light_ray(scene, properties, hit, ray, light_ray);
    }

    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerv2::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const
{
    Color result = colors::black();

    result += compute_diffuse(properties, hit, ray, light_ray);

    return result;
}

imaging::Color raytracer::raytracers::_private_::RayTracerv2::compute_diffuse(const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const
{
    Color result = colors::black();
    math::Vector3D n = hit.normal;
    math::Point3D l = light_ray.ray.origin;
    math::Point3D p = hit.position;
    Color cl = light_ray.color;
    Color cs = properties.diffuse;
    double cos;
    cos = (l - p).normalized().dot(n);

    if (cos > 0) {
        return cos * cl * cs;
    }

    return result;
}

raytracer::RayTracer raytracer::raytracers::v2()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerv2>());
}
