#include "raytracers/ray-tracer-v4.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

imaging::Color raytracer::raytracers::_private_::RayTracerv4::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const
{
    Hit rayhit;
    auto light_hit = scene.root->find_first_positive_hit(light_ray.ray, &rayhit);

    if (light_hit && 0 <= rayhit.t && rayhit.t < 0.9999) {
        return colors::black();
    }
    else {
        return RayTracerv3::process_light_ray(scene, properties, hit, ray, light_ray);
    }
}

raytracer::RayTracer raytracer::raytracers::v4()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerv4>());
}
