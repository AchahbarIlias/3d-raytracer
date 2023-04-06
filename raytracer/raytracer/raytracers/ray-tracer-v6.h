#pragma once

#include "raytracers/ray-tracer.h"
#include "ray-tracer-v5.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerv6 : public RayTracerv5
            {
            public:
                virtual TraceResult trace(const Scene& scene, const math::Ray& ray) const override;
            protected:
                virtual TraceResult trace(const Scene& scene, const math::Ray& ray, const double weight) const;
                virtual imaging::Color determine_color(const Scene& scene, const MaterialProperties& matprops, const Hit& hit, const math::Ray& ray, const double weight) const;
                virtual imaging::Color compute_reflection(const Scene& scene, const MaterialProperties& matprops, const Hit& hit, const math::Ray& ray, const double weight) const;
            };
        }

        RayTracer v6();
    }
}