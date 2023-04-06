#include "raytracers/ray-tracer-v7.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


Color raytracer::raytracers::_private_::RayTracerv7::determine_color(const Scene& scene, const MaterialProperties& matprops, const Hit& hit, const math::Ray& ray, const double weight) const
{
	Color result = colors::black();
	result += RayTracerv2::determine_color(scene, matprops, hit, ray);
	result += compute_translucency(scene, matprops, hit, ray, weight);
	return result;
}

Color raytracer::raytracers::_private_::RayTracerv7::compute_translucency(const Scene& scene, const MaterialProperties& matprops, const Hit& hit, const math::Ray& ray, const double weight) const
{
	auto translucency = matprops.translucency;
	auto result = colors::black();
	if (translucency > 0)
	{
		const auto t = hit.normal.normalized();
		const auto translucency_direction = ray.direction;
		const auto translucency_origin = ray.at(hit.t) + 0.00000001 * translucency_direction;
		const auto translucency_ray = Ray(translucency_origin, translucency_direction);
		const auto new_weight = weight * translucency;
		result += trace(scene, translucency_ray, new_weight).color;
	}
	return result;
}

raytracer::RayTracer raytracer::raytracers::v7()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerv7>());
}


