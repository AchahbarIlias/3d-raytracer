#include "primitives/cylinder-primitive.h"
#include "math/quadratic_equation.h"
#include "util/misc.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
	class CoordinateCylinderImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	protected:
		CoordinateCylinderImplementation() {}

		virtual void initialize_hit(Hit* hit, const Ray& ray, double t) const = 0;
		virtual std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const = 0;
		virtual bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const = 0;
	};

	class CylinderAlongXImplementation : public CoordinateCylinderImplementation {
	public:
		CylinderAlongXImplementation()
			: CoordinateCylinderImplementation()
		{
			// NOP
		}

		math::Box bounding_box() const override
		{
			return Box(Interval<double>::infinite(), interval(-1.00, 1.00), interval(-1.00, 1.00));
		}

	protected:
		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			const auto radius = 1;
			const auto O = Point2D(ray.origin.y(), ray.origin.z());
			const auto delta = Vector2D(ray.direction.y(), ray.direction.z());
			const auto a = delta.dot(delta);
			const auto b = 2 * (O - Point2D(0, 0)).dot(delta);
			const auto c = (O - Point2D(0, 0)).dot((O - Point2D(0, 0))) - pow(radius, 2);

			QuadraticEquation qeq(a, b, c);
			if (qeq.has_solutions())
			{
				double t1 = qeq.x1();
				double t2 = qeq.x2();
				auto hit1 = std::make_shared<Hit>();
				auto hit2 = std::make_shared<Hit>();
				initialize_hit(hit1.get(), ray, t1);
				initialize_hit(hit2.get(), ray, t2);
				hits.push_back(hit1);
				hits.push_back(hit2);
			}

			return hits;
		}

		bool find_first_positive_hit(const math::Ray& ray, Hit* output_hit) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			const auto radius = 1;
			const auto O = Point2D(ray.origin.y(), ray.origin.z());
			const auto delta = Vector2D(ray.direction.y(), ray.direction.z());
			const auto a = delta.dot(delta);
			const auto b = 2 * (O - Point2D(0, 0)).dot(delta);
			const auto c = (O - Point2D(0, 0)).dot((O - Point2D(0, 0))) - pow(radius, 2);

			QuadraticEquation qeq(a, b, c);
			if (qeq.has_solutions())
			{
				double t1 = qeq.x1();
				double t2 = qeq.x2();
				double t;

				if (smallest_greater_than_zero(t1, t2, &t))
				{
					if (t < output_hit->t)
					{
						initialize_hit(output_hit, ray, t);
						return true;
					}
				}
			}

			return false;
		}

		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			const auto radius = 1;
			hit->t = t;
			hit->position = ray.origin + ray.direction * t;
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.y(), hit->position.z());
			hit->normal = Vector3D(0, hit->position.y() / radius, hit->position.z() / radius);
		}
	};

	class CylinderAlongYImplementation : public CoordinateCylinderImplementation {
	public:
		CylinderAlongYImplementation()
			: CoordinateCylinderImplementation()
		{
			// NOP
		}

		math::Box bounding_box() const override
		{
			return Box(interval(-1.00, 1.00), Interval<double>::infinite(), interval(-1.00, 1.00));
		}

	protected:
		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			const auto radius = 1;
			const auto O = Point2D(ray.origin.x(), ray.origin.z());
			const auto delta = Vector2D(ray.direction.x(), ray.direction.z());
			const auto a = delta.dot(delta);
			const auto b = 2 * (O - Point2D(0, 0)).dot(delta);
			const auto c = (O - Point2D(0, 0)).dot((O - Point2D(0, 0))) - pow(radius, 2);

			QuadraticEquation qeq(a, b, c);
			if (qeq.has_solutions())
			{
				double t1 = qeq.x1();
				double t2 = qeq.x2();
				auto hit1 = std::make_shared<Hit>();
				auto hit2 = std::make_shared<Hit>();
				initialize_hit(hit1.get(), ray, t1);
				initialize_hit(hit2.get(), ray, t2);
				hits.push_back(hit1);
				hits.push_back(hit2);
			}

			return hits;
		}

		bool find_first_positive_hit(const math::Ray& ray, Hit* output_hit) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			const auto radius = 1;
			const auto O = Point2D(ray.origin.x(), ray.origin.z());
			const auto delta = Vector2D(ray.direction.x(), ray.direction.z());
			const auto a = delta.dot(delta);
			const auto b = 2 * (O - Point2D(0, 0)).dot(delta);
			const auto c = (O - Point2D(0, 0)).dot((O - Point2D(0, 0))) - pow(radius, 2);

			QuadraticEquation qeq(a, b, c);
			if (qeq.has_solutions())
			{
				double t1 = qeq.x1();
				double t2 = qeq.x2();
				double t;

				if (smallest_greater_than_zero(t1, t2, &t))
				{
					if (t < output_hit->t)
					{
						initialize_hit(output_hit, ray, t);
						return true;
					}
				}
			}

			return false;
		}

		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			const auto radius = 1;
			hit->t = t;
			hit->position = ray.origin + ray.direction * t;
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.z());
			hit->normal = Vector3D(0, hit->position.x() / radius, hit->position.z() / radius);
		}
	};

	class CylinderAlongZImplementation : public CoordinateCylinderImplementation {
	public:
		CylinderAlongZImplementation()
			: CoordinateCylinderImplementation()
		{
			// NOP
		}

		math::Box bounding_box() const override
		{
			return Box(interval(-1.00, 1.00), interval(-1.00, 1.00), Interval<double>::infinite());
		}

	protected:
		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			const auto radius = 1;
			const auto O = Point2D(ray.origin.x(), ray.origin.y());
			const auto delta = Vector2D(ray.direction.x(), ray.direction.y());
			const auto a = delta.dot(delta);
			const auto b = 2 * (O - Point2D(0, 0)).dot(delta);
			const auto c = (O - Point2D(0, 0)).dot((O - Point2D(0, 0))) - pow(radius, 2);

			QuadraticEquation qeq(a, b, c);
			if (qeq.has_solutions())
			{
				double t1 = qeq.x1();
				double t2 = qeq.x2();
				auto hit1 = std::make_shared<Hit>();
				auto hit2 = std::make_shared<Hit>();
				initialize_hit(hit1.get(), ray, t1);
				initialize_hit(hit2.get(), ray, t2);
				hits.push_back(hit1);
				hits.push_back(hit2);
			}

			return hits;
		}

		bool find_first_positive_hit(const math::Ray& ray, Hit* output_hit) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			const auto radius = 1;
			const auto O = Point2D(ray.origin.x(), ray.origin.y());
			const auto delta = Vector2D(ray.direction.x(), ray.direction.y());
			const auto a = delta.dot(delta);
			const auto b = 2 * (O - Point2D(0, 0)).dot(delta);
			const auto c = (O - Point2D(0, 0)).dot((O - Point2D(0, 0))) - pow(radius, 2);

			QuadraticEquation qeq(a, b, c);
			if (qeq.has_solutions())
			{
				double t1 = qeq.x1();
				double t2 = qeq.x2();
				double t;

				if (smallest_greater_than_zero(t1, t2, &t))
				{
					if (t < output_hit->t)
					{
						initialize_hit(output_hit, ray, t);
						return true;
					}
				}
			}

			return false;
		}

		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			const auto radius = 1;
			hit->t = t;
			hit->position = ray.origin + ray.direction * t;
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
			hit->normal = Vector3D(0, hit->position.x() / radius, hit->position.y() / radius);
		}
	};
}

Primitive raytracer::primitives::cylinder_along_x()
{
	return Primitive(std::make_shared<CylinderAlongXImplementation>());
}

Primitive raytracer::primitives::cylinder_along_y()
{
	return Primitive(std::make_shared<CylinderAlongYImplementation>());
}

Primitive raytracer::primitives::cylinder_along_z()
{
	return Primitive(std::make_shared<CylinderAlongZImplementation>());
}
