#pragma once

#include "raytracers/ray-tracer.h"
#include "ray-tracer-v6.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerv7 : public RayTracerv6
            {
            protected:
                virtual imaging::Color determine_color(const Scene& scene, const MaterialProperties& matprops, const Hit& hit, const math::Ray& ray, const double weight) const;
                virtual imaging::Color compute_translucency(const Scene& scene, const MaterialProperties& matprops, const Hit& hit, const math::Ray& ray, const double weight) const;
            };
        }

        RayTracer v7();
    }
}