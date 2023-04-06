#include "samplers/half-jittered-sampler.h"
#include "math/rasterizer.h"
#include <random>

using namespace math;
using namespace raytracer;

namespace
{
    class HalfJitteredSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
    public:
        HalfJitteredSampler(const int n, const int m) : m_n(n), m_m(m), rd(), gen(rd()), dis(0.25, 0.75) {}

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
        {
            math::Rasterizer rasterizer = math::Rasterizer(rectangle, m_m, m_n);

            for (int m = 0; m < m_m; ++m) {
                for (int n = 0; n < m_n; ++n) {
                    function(rasterizer[Position2D(m, n)].from_relative(Point2D(dis(gen), dis(gen))));
                }
            }
        }
    private:
        int m_n;
        int m_m;

        mutable std::random_device rd;
        mutable std::mt19937 gen;
        mutable std::uniform_real_distribution<double> dis;
    };
}

Sampler raytracer::samplers::half_jittered(unsigned const int n, unsigned const int m)
{
    return Sampler(std::make_shared<HalfJitteredSampler>(n, m));
}
