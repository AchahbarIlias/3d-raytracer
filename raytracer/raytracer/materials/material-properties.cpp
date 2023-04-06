#include "materials/material-properties.h"
#include "imaging/color.h"


using namespace imaging;

raytracer::MaterialProperties::MaterialProperties(
    const Color& ambient,
    const Color& diffuse,
    const Color& specular,
    const double specular_exponent,
    const Color& light_filtering,
    const double reflectivity,
    const double translucency,
    const double transparency,
    const double refractive_index)
    : ambient(ambient)
    , diffuse(diffuse)
    , specular(specular)
    , specular_exponent(specular_exponent)
    , light_filtering(light_filtering)
    , reflectivity(reflectivity)
    , translucency(translucency)
    , transparency(transparency)
    , refractive_index(refractive_index)
{
    // NOP
}

raytracer::MaterialPropertiesBuilder::MaterialPropertiesBuilder()
    : m_ambient(colors::black())
    , m_diffuse(colors::black())
    , m_specular(colors::black())
    , m_specular_exponent(0.0)
    , m_light_filtering(colors::black())
    , m_reflectivity(0.0)
    , m_translucency(0.0)
    , m_transparency(0.0)
    , m_refractive_index(1.0)
{
    // NOP
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::ambient(const imaging::Color& color)
{
    m_ambient = color;

    return *this;
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::diffuse(const imaging::Color& color)
{
    m_diffuse = color;

    return *this;
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::specular(const imaging::Color& color, double exponent)
{
    m_specular = color;
    m_specular_exponent = exponent;

    return *this;
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::light_filtering(const imaging::Color& color)
{
    m_light_filtering = color;

    return *this;
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::reflectivity(const double reflectivity)
{
    m_reflectivity = reflectivity;

    return *this;
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::translucency(const double translucency)
{
    m_translucency = translucency;

    return *this;
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::transparency(const double transparency, const double refractive_index)
{
    m_transparency = transparency;
    m_refractive_index = refractive_index;

    return *this;
}

raytracer::MaterialPropertiesBuilder::operator raytracer::MaterialProperties() const
{
    return MaterialProperties(
        m_ambient,
        m_diffuse,
        m_specular,
        m_specular_exponent,
        m_light_filtering,
        m_reflectivity,
        m_translucency,
        m_transparency,
        m_refractive_index
    );
}
