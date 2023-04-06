#include "primitives/triangle-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
	class TriangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:
		TriangleImplementation(const math::Point3D& vertex1, const math::Point3D& vertex2, const math::Point3D& vertex3)
			: v1(vertex1), v2(vertex2), v3(vertex3)
		{
			//Compute the normal vector on the plane
			this->normal = (v2 - v1).cross(v3 - v1).normalized();
		}

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			//Compute the hit t
			double t = (v1 - ray.origin).dot(normal) / ray.direction.dot(normal);

			//Compute the hit position H
			Point3D H = ray.origin + (ray.direction * t);

			//Check if H lies to the right of P1 P2
			if (((v2 - v1).cross(H - v1).dot(normal)) < 0) return hits;
			//Check if H lies to the right of P2 P3
			if (((v3 - v2).cross(H - v2).dot(normal)) < 0) return hits;
			//Check if H lies to the right of P3 P1
			if (((v1 - v3).cross(H - v3).dot(normal)) < 0) return hits;

			auto hit = std::make_shared<Hit>();
			initialize_hit(hit.get(), ray, t);
			hits.push_back(hit);

			return hits;
		}

		bool find_first_positive_hit(const Ray& ray, Hit* output_hit) const override
		{
			//Compute the hit t
			double t = (v1 - ray.origin).dot(normal) / ray.direction.dot(normal);

			if (t < 0 || t >= output_hit->t) return false;

			//Compute the hit position H
			Point3D H = ray.origin + (ray.direction * t);

			//Check if H lies to the right of P1 P2
			if (((v2 - v1).cross(H - v1).dot(normal)) < 0) return false;
			//Check if H lies to the right of P2 P3
			if (((v3 - v2).cross(H - v2).dot(normal)) < 0) return false;
			//Check if H lies to the right of P3 P1
			if (((v1 - v3).cross(H - v3).dot(normal)) < 0) return false;

			initialize_hit(output_hit, ray, t);
			return true;
		}

		math::Box bounding_box() const override
		{
			auto xmin = std::min({ v1.x(), v2.x(), v3.x() });
			auto ymin = std::min({ v1.y(), v2.y(), v3.y() });
			auto zmin = std::min({ v1.z(), v2.z(), v3.z() });

			auto xmax = std::max({ v1.x(), v2.x(), v3.x() });
			auto ymax = std::max({ v1.y(), v2.y(), v3.y() });
			auto zmax = std::max({ v1.z(), v2.z(), v3.z() });

			return Box(interval(xmin, xmax), interval(ymin, ymax), interval(zmin, zmax));
		}

	private:
		Point3D v1;
		Point3D v2;
		Point3D v3;
		Vector3D normal;

		void initialize_hit(Hit* hit, const Ray& ray, double t) const
		{
			hit->t = t;
			hit->position = ray.at(t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
			hit->normal = normal;
		}
	};
}

Primitive raytracer::primitives::triangle(const math::Point3D& vertex1, const math::Point3D& vertex2, const math::Point3D& vertex3)
{
	return Primitive(std::make_shared<TriangleImplementation>(vertex1, vertex2, vertex3));
}
