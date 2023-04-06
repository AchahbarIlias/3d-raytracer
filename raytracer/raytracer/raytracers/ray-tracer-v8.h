#pragma once

#include "raytracers/ray-tracer.h"
#include "ray-tracer-v7.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerv8 : public RayTracerv7
            {
            private:
                math::Vector3D refract(math::Vector3D i, math::Vector3D n, double n1, double n2) const;
            protected:
                virtual imaging::Color determine_color(const Scene& scene, const MaterialProperties& matprops, const Hit& hit, const math::Ray& ray, const double weight) const;
                virtual imaging::Color compute_refraction(const Scene& scene, const MaterialProperties& matprops, const Hit& hit, const math::Ray& ray, const double weight) const;
            };
        }

        RayTracer v8();
    }
}