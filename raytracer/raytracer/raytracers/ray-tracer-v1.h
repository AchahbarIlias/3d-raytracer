#pragma once

#include "raytracers/ray-tracer.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerv1 : public RayTracerImplementation
            {
            public:
               
                TraceResult trace(const Scene& scene, const math::Ray& eye_ray) const override;

            protected:
                imaging::Color compute_ambient(const MaterialProperties&) const;
                virtual imaging::Color determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const;
            };
        }

        RayTracer v1();
    }
}