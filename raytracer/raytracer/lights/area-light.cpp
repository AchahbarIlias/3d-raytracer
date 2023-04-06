#include "area-light.h"

using namespace raytracer;

namespace
{
    class AreaLight : public raytracer::lights::_private_::LightSourceImplementation
    {
    public:
        AreaLight(const math::Rectangle3D rectangle3D, const Sampler sampler, const imaging::Color& color)
            : m_rectangle3D(rectangle3D), m_sampler(sampler), m_color(color) { }

    protected:
        std::vector<LightRay> lightrays_to(const math::Point3D& point3d) const override
        {
            //make empty vector
            std::vector<LightRay> lightraysvector;

            math::Rectangle2D rectangle2D(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 1));
            std::vector<math::Point2D> samplerpositions = m_sampler->sample(rectangle2D);

            //each position in area
            for each (math::Point2D position in samplerpositions) {
                //get point
                math::Point3D point = m_rectangle3D.project(position);

                // make lightray based on ray
                math::Ray ray(point, point3d);

                //(Remember that we are faking an area light by creating a number of point lights.
                //Say the area light should be 100 Watt. We are replacing it by 10 smaller light sources.
                //Should each of these 10 light sources shine at a full 100W?)
                imaging::Color newcolor(m_color.r / samplerpositions.size(), m_color.g / samplerpositions.size(), m_color.b / samplerpositions.size());

                //push back lightray on the lightrayvector
                lightraysvector.push_back(LightRay(ray, newcolor));
            }
            //return lightrayvector when for each is done
            return lightraysvector;
        }

    private:
        math::Rectangle3D m_rectangle3D;
        Sampler m_sampler;
        imaging::Color m_color;
    };
}

LightSource raytracer::lights::arealight(const math::Rectangle3D rectangle3D, const Sampler sampler, const imaging::Color& color)
{
    return LightSource(std::make_shared<AreaLight>(rectangle3D, sampler, color));
}