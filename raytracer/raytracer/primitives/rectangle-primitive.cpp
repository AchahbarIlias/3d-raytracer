#include "primitives/rectangle-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
	/// <summary>
	/// Superclass for rectangles. Contains common logic.
	/// </summary>
	class CoordinateRectangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	protected:
		const Vector3D m_normal;

		/// <summary>
		/// Constructor.
		/// </summary>
		/// <param name="normal">
		/// Normal vector on rectangle. Needs to have unit length.
		/// </param>
		CoordinateRectangleImplementation(const Vector3D& normal)
			: m_normal(normal)
		{
			assert(normal.is_unit());
		}

		virtual void initialize_hit(Hit* hit, const Ray& ray, double t) const = 0;

	public:
		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			// Compute denominator
			double denom = ray.direction.dot(m_normal);

			// If denominator == 0, there is no intersection (ray runs parallel to rectangle)
			if (denom != approx(0.0) && bounding_box().is_hit_by(ray))
			{
				// Compute numerator
				double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));

				// Compute t
				double t = numer / denom;

				// Create hit object
				auto hit = std::make_shared<Hit>();

				// shared_ptr<T>::get() returns the T* inside the shared pointer
				initialize_hit(hit.get(), ray, t);

				// Put hit in list
				hits.push_back(hit);
			}

			return hits;
		}

		bool find_first_positive_hit(const math::Ray& ray, Hit* output_hit) const override
		{
			// Compute denominator
			double denom = ray.direction.dot(m_normal);

			// If denominator == 0, there is no intersection (ray runs parallel to square)
			if (denom != approx(0.0) && bounding_box().is_hit_by(ray))
			{
				// Compute numerator
				double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));

				// Compute t
				double t = numer / denom;
				if (t < 0 || t >= output_hit->t) return false;

				// shared_ptr<T>::get() returns the T* inside the shared pointer
				initialize_hit(output_hit, ray, t);

				return true;
			}
			return false;
		}
	};

	class RectangleXYImplementation : public CoordinateRectangleImplementation
	{
		double xsize;
		double ysize;

	public:
		RectangleXYImplementation(double x_size, double y_size)
			: CoordinateRectangleImplementation(Vector3D(0, 0, 1))
		{
			xsize = x_size;
			ysize = y_size;
		}

		math::Box bounding_box() const override
		{
			return Box(interval(-xsize / 2, xsize / 2), interval(-ysize / 2, ysize / 2), interval(-0.01, 0.01));
		}

	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
			hit->normal = ray.origin.z() > 0 ? m_normal : -m_normal;
		}
	};

	class RectangleXZImplementation : public CoordinateRectangleImplementation
	{
		double xsize;
		double zsize;

	public:
		RectangleXZImplementation(double x_size, double z_size)
			: CoordinateRectangleImplementation(Vector3D(0, 1, 0))
		{
			xsize = x_size;
			zsize = z_size;
		}

		math::Box bounding_box() const override
		{
			return Box(interval(-xsize / 2, xsize / 2), interval(-0.01, 0.01), interval(-zsize / 2, zsize / 2));
		}

	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.z());
			hit->normal = ray.origin.y() > 0 ? m_normal : -m_normal;
		}
	};

	class RectangleYZImplementation : public CoordinateRectangleImplementation
	{
		double ysize;
		double zsize;

	public:
		RectangleYZImplementation(double y_size, double z_size)
			: CoordinateRectangleImplementation(Vector3D(1, 0, 0))
		{
			ysize = y_size;
			zsize = z_size;
		}

		math::Box bounding_box() const override
		{
			return Box(interval(-0.01, 0.01), interval(-ysize / 2, ysize / 2), interval(-zsize / 2, zsize / 2));
		}

	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.y(), hit->position.z());
			hit->normal = ray.origin.x() > 0 ? m_normal : -m_normal;
		}
	};

}

Primitive raytracer::primitives::xy_rectangle(double x_size, double y_size)
{
	return Primitive(std::make_shared<RectangleXYImplementation>(x_size, y_size));
}

Primitive raytracer::primitives::xz_rectangle(double x_size, double z_size)
{
	return Primitive(std::make_shared<RectangleXZImplementation>(x_size, z_size));
}

Primitive raytracer::primitives::yz_rectangle(double y_size, double z_size)
{
	return Primitive(std::make_shared<RectangleYZImplementation>(y_size, z_size));
}

Primitive raytracer::primitives::xy_square(double size)
{
	return Primitive(std::make_shared<RectangleXYImplementation>(size, size));
}

Primitive raytracer::primitives::xz_square(double size)
{
	return Primitive(std::make_shared<RectangleXZImplementation>(size, size));
}

Primitive raytracer::primitives::yz_square(double size)
{
	return Primitive(std::make_shared<RectangleYZImplementation>(size, size));
}
