#pragma once

#include "raytracers/ray-tracer.h"
#include "ray-tracer-v1.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerv2 : public RayTracerv1
            {
            public:
                imaging::Color determine_color(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const override;

            protected:
                virtual imaging::Color process_lights(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray) const;
                virtual imaging::Color process_light_source(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightSource light_source) const;
                virtual imaging::Color process_light_ray(const Scene& scene, const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const;
                virtual imaging::Color compute_diffuse(const MaterialProperties& properties, const Hit& hit, const math::Ray& ray, LightRay light_ray) const;
            };
        }

        RayTracer v2();
    }
}