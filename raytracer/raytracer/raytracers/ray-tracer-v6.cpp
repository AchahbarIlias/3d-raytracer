#include "raytracers/ray-tracer-v6.h"

using namespace imaging;
using namespace math;
using namespace raytracer;



TraceResult raytracer::raytracers::_private_::RayTracerv6::trace(const Scene& scene, const Ray& ray) const
{
	Hit rayhit;
	auto hit = scene.root->find_first_positive_hit(ray, &rayhit);

	if (hit) {
		auto matprops = rayhit.material->at(rayhit.local_position);
		Color color = determine_color(scene, matprops, rayhit, ray, 1.0);
		return TraceResult(color, rayhit.group_id, ray, rayhit.t);
	}
	else
	{
		return TraceResult::no_hit(ray);
	}
}


TraceResult raytracer::raytracers::_private_::RayTracerv6::trace(const Scene& scene, const Ray& ray, const double weight) const
{
	Hit rayhit;
	auto hit = scene.root->find_first_positive_hit(ray, &rayhit);
	if (weight < 0.01) {
		return TraceResult::no_hit(ray);
	}
	else if (hit) {
		auto matprops = rayhit.material->at(rayhit.local_position);
		Color color = determine_color(scene, matprops, rayhit, ray, weight);
		return TraceResult(color, rayhit.group_id, ray, rayhit.t);
	}
	else
	{
		return TraceResult::no_hit(ray);
	}
}

Color raytracer::raytracers::_private_::RayTracerv6::determine_color(const Scene& scene, const MaterialProperties& matprops, const Hit& hit, const math::Ray& ray, const double weight) const
{
	Color result = colors::black();
	result += RayTracerv2::determine_color(scene, matprops, hit, ray);
	result += compute_reflection(scene, matprops, hit, ray, weight);
	return result;
}

Color raytracer::raytracers::_private_::RayTracerv6::compute_reflection(const Scene& scene, const MaterialProperties& matprops, const Hit& hit, const math::Ray& ray, const double weight) const
{
	auto reflectivity = matprops.reflectivity;
	auto result = colors::black();
	if (reflectivity > 0)
	{
		const auto t = hit.normal.normalized();
		const auto reflection_direction = ray.direction.reflect_by(t);
		const auto reflection_origin = ray.at(hit.t) + 0.00000001 * reflection_direction;
		const auto reflection_ray = Ray(reflection_origin, reflection_direction);
		const auto new_weight = weight * reflectivity;
		result += (matprops.reflectivity * trace(scene, reflection_ray, new_weight * matprops.reflectivity).color);
	}
	return result;
}

raytracer::RayTracer raytracer::raytracers::v6()
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerv6>());
}


