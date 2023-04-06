#include "primitives/disk-primitive.h"
#include "math/interval.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
    /// <summary>
    /// Superclass for disks. Contains common logic.
    /// </summary>
    class CoordinateDiskImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
    {
    protected:
        const Vector3D m_normal;
        const double m_radius;

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="normal">
        /// Normal vector on disk. Needs to have unit length.
        /// </param>
        /// <param name="radius">
        /// Radius of the disk.
        /// </param>
        CoordinateDiskImplementation(const Vector3D& normal, double radius)
            : m_normal(normal), m_radius(radius)
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

            // If denominator == 0, there is no intersection (ray runs parallel to plane)
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

                // Check if hit lies inside disk
                if ((hit.get()->position - Point3D(0, 0, 0)).dot(hit.get()->position - Point3D(0, 0, 0)) <= pow(m_radius, 2))
                {
                    // Put hit in list
                    hits.push_back(hit);
                }
            }

            return hits;
        }

        bool find_first_positive_hit(const math::Ray& ray, Hit* output_hit) const override
        {
            // Compute denominator
            double denom = ray.direction.dot(m_normal);

            // If denominator == 0, there is no intersection (ray runs parallel to plane)
            if (denom != approx(0.0) && bounding_box().is_hit_by(ray))
            {
                // Compute numerator
                double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));

                // Compute t
                double t = numer / denom;
                if (t < 0 || t >= output_hit->t) return false;

                // Create hit object
                auto hit = std::make_shared<Hit>();

                // shared_ptr<T>::get() returns the T* inside the shared pointer
                initialize_hit(hit.get(), ray, t);

                if ((hit.get()->position - Point3D(0, 0, 0)).dot(hit.get()->position - Point3D(0, 0, 0)) <= pow(m_radius, 2))
                {
                    initialize_hit(output_hit, ray, t);
                    return true;
                }
            }
            return false;
        }
    };

    class DiskXYImplementation : public CoordinateDiskImplementation
    {
    public:
        DiskXYImplementation(double radius)
            : CoordinateDiskImplementation(Vector3D(0, 0, 1), radius)
        {
            // NOP
        }

        math::Box bounding_box() const override
        {
			return Box(interval(-m_radius, m_radius), interval(-m_radius, m_radius), interval(-0.01, 0.01));
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

    class DiskXZImplementation : public CoordinateDiskImplementation
    {
    public:
        DiskXZImplementation(double radius)
            : CoordinateDiskImplementation(Vector3D(0, 1, 0), radius)
        {
            // NOP
        }

        math::Box bounding_box() const override
        {
            return Box(interval(-m_radius, m_radius), interval(-0.01, 0.01), interval(-m_radius, m_radius));
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

    class DiskYZImplementation : public CoordinateDiskImplementation
    {
    public:
        DiskYZImplementation(double radius)
            : CoordinateDiskImplementation(Vector3D(1, 0, 0), radius)
        {
            // NOP
        }

        math::Box bounding_box() const override
        {
            return Box(interval(-0.01, 0.01), interval(-m_radius, m_radius), interval(-m_radius, m_radius));
        }

    protected:
        void initialize_hit(Hit* hit, const Ray& ray, double t) const override
        {
            hit->t = t;
            hit->position = ray.at(hit->t);
            hit->local_position.xyz = hit->position;
            hit->local_position.uv = Point2D(hit->position.z(), hit->position.y());
            hit->normal = ray.origin.x() > 0 ? m_normal : -m_normal;
        }
    };
}

Primitive raytracer::primitives::xy_disk(double radius)
{
    return Primitive(std::make_shared<DiskXYImplementation>(radius));
}

Primitive raytracer::primitives::xz_disk(double radius)
{
    return Primitive(std::make_shared<DiskXZImplementation>(radius));
}

Primitive raytracer::primitives::yz_disk(double radius)
{
    return Primitive(std::make_shared<DiskYZImplementation>(radius));
}
