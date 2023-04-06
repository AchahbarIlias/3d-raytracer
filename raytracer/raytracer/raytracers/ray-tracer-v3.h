#pragma once

#include "raytracers/ray-tracer.h"
#include "ray-tracer-v2.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerv3 : public RayTracerv2
            {
            protected:
                virtual imaging::Color process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const;
                virtual imaging::Color compute_specular(const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const;
            };
        }

        RayTracer v3();
    }
}