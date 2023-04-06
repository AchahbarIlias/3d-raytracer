#include "raytracers/ray-tracer-v5.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

imaging::Color raytracer::raytracers::_private_::RayTracerv5::process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const
{
    std::vector<std::shared_ptr<Hit>> hits = scene.root->find_all_hits(light_ray.ray);
    Color color_filter = colors::white();

    for each (auto h in hits) {
        auto this_hit = *h;
        if (0 < this_hit.t && round(this_hit.t) < 1) {
            auto matprops = this_hit.material->at(this_hit.local_position);
            color_filter = matprops.light_filtering * color_filter;
        }
    }

    auto surviving_light_ray = LightRay(light_ray.ray, light_ray.color * color_filter);

    return RayTracerv3::process_light_ray(scene, properties, hit, ray, surviving_light_ray);
}

raytracer::RayTracer raytracer::raytracers::v5()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerv5>());
}
