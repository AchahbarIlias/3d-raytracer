#include "primitives/box-primitive.h"
#include <primitives/rectangle-primitive.h>
#include <primitives/transformer-primitive.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
	/// <summary>
	/// Superclass for rectangles. Contains common logic.
	/// </summary>
	class BoxImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
		double xsize;
		double ysize;
		double zsize;

	public:
		BoxImplementation(double x_size, double y_size, double z_size)
		{
			xsize = x_size;
			ysize = y_size;
			zsize = z_size;
		}

		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			if (bounding_box().is_hit_by(ray)) {
				// xy_rectangles
				auto xy_hits = translate(Vector3D(0, 0, zsize / 2), xy_rectangle(xsize, ysize))->find_all_hits(ray);
				hits.insert(hits.end(), xy_hits.begin(), xy_hits.end());
				auto xy2_hits = translate(Vector3D(0, 0, -zsize / 2), xy_rectangle(xsize, ysize))->find_all_hits(ray);
				hits.insert(hits.end(), xy2_hits.begin(), xy2_hits.end());

				// xz_rectangles
				auto xz_hits = translate(Vector3D(0, ysize / 2, 0), xz_rectangle(xsize, zsize))->find_all_hits(ray);
				hits.insert(hits.end(), xz_hits.begin(), xz_hits.end());
				auto xz2_hits = translate(Vector3D(0, -ysize / 2, 0), xz_rectangle(xsize, zsize))->find_all_hits(ray);
				hits.insert(hits.end(), xz2_hits.begin(), xz2_hits.end());

				// yz_rectangles
				auto yz_hits = translate(Vector3D(xsize / 2, 0, 0), yz_rectangle(ysize, zsize))->find_all_hits(ray);
				hits.insert(hits.end(), yz_hits.begin(), yz_hits.end());
				auto yz2_hits = translate(Vector3D(-xsize / 2, 0, 0), yz_rectangle(ysize, zsize))->find_all_hits(ray);
				hits.insert(hits.end(), yz2_hits.begin(), yz2_hits.end());
			}
			return hits;
		}

		bool find_first_positive_hit(const math::Ray& ray, Hit* output_hit) const override
		{
			if (bounding_box().is_hit_by(ray)) {
				if (translate(Vector3D(0, 0, zsize / 2), xy_rectangle(xsize, ysize))->find_first_positive_hit(ray, output_hit) ||
					translate(Vector3D(0, 0, -zsize / 2), xy_rectangle(xsize, ysize))->find_first_positive_hit(ray, output_hit) ||
					translate(Vector3D(0, ysize / 2, 0), xz_rectangle(xsize, zsize))->find_first_positive_hit(ray, output_hit) ||
					translate(Vector3D(0, -ysize / 2, 0), xz_rectangle(xsize, zsize))->find_first_positive_hit(ray, output_hit) ||
					translate(Vector3D(xsize / 2, 0, 0), yz_rectangle(ysize, zsize))->find_first_positive_hit(ray, output_hit) ||
					translate(Vector3D(-xsize / 2, 0, 0), yz_rectangle(ysize, zsize))->find_first_positive_hit(ray, output_hit)) {
					return true;
				}
			}
			return false;
		}

		math::Box bounding_box() const override
		{
			return Box(interval(-xsize / 2, xsize / 2), interval(-ysize / 2, ysize / 2), interval(-zsize / 2, zsize / 2));
		}

	};
}

Primitive raytracer::primitives::box(double x_size, double y_size, double z_size)
{
	return Primitive(std::make_shared<BoxImplementation>(x_size, y_size, z_size));
}

Primitive raytracer::primitives::cube()
{
	return Primitive(std::make_shared<BoxImplementation>(1,1,1));
}
