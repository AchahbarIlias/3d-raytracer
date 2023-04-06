#include "raytracers/ray-tracer-v8.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


Vector3D raytracer::raytracers::_private_::RayTracerv8::refract(Vector3D i, Vector3D n, double n1, double n2) const
{
	Vector3D null;
	auto ox = (n1 / n2) * (i - i.dot(n) * n);

	if ((1 - ox.dot(ox)) < 0) {
		return null;
	}

	const auto oy = (-1 * sqrt(1 - ox.dot(ox))) * n;
	Vector3D o = ox + oy;
	return o;
}

Color raytracer::raytracers::_private_::RayTracerv8::determine_color(const Scene& scene, const MaterialProperties& matprops, const Hit& hit, const math::Ray& ray, const double weight) const
{
	Color result = colors::black();
	result += RayTracerv2::determine_color(scene, matprops, hit, ray);
	result += compute_refraction(scene, matprops, hit, ray, weight);
	return result;
}

Color raytracer::raytracers::_private_::RayTracerv8::compute_refraction(const Scene& scene, const MaterialProperties& matprops, const Hit& hit, const math::Ray& ray, const double weight) const
{
	auto transparency = matprops.transparency;
	auto result = colors::black();
	if (transparency > 0)
	{
		double n1 = 1.0;
		auto n2 = matprops.refractive_index;

		auto p1 = hit.position;
		auto normal_p1 = hit.normal.normalized();
		auto refracted_direction = refract(ray.direction.normalized(), normal_p1, n1, n2);

		Vector3D null;
		if (refracted_direction == null) {
			return result;
		}
		auto vector_moved = p1 + refracted_direction * 0.0000001;
		auto refracted_ray = Ray(vector_moved, refracted_direction);

		Hit exit_hit;

		if (!scene.root->find_first_positive_hit(refracted_ray, &exit_hit)) {
			return result;
		}

		auto p2 = exit_hit.position;
		auto normal_p2 = exit_hit.normal.normalized();
		if (exit_hit.normal.opposite_to(refracted_ray.direction)) {
			refracted_direction = refract(refracted_ray.direction.normalized(), normal_p2, n1, n2);
		}

		if (refracted_direction == null) {
			return result;
		}
		vector_moved = p2 + refracted_direction * 0.0000001;
		auto exit_ray = Ray(vector_moved, refracted_direction);
		return trace(scene, exit_ray, weight * transparency).color * transparency;
	}
	return result;
}

raytracer::RayTracer raytracer::raytracers::v8()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerv8>());
}


