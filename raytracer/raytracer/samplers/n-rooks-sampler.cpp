#include "samplers/n-rooks-sampler.h"
#include "math/rasterizer.h"
#include <random>

using namespace math;
using namespace raytracer;

namespace
{
    class NRooksSampler : public raytracer::samplers::_private_::SamplerImplementation
    {
        unsigned int rooks;

    public:
        NRooksSampler(unsigned int rooks) : rooks(rooks) {};
        std::vector<math::Point2D> sample(const::math::Rectangle2D& rectangle) const override
        {
            std::random_device dev;
            std::mt19937_64 rando(dev());
            std::vector<math::Point2D> points2d;


            std::vector<int> columns;
            auto raster = math::Rasterizer(rectangle, this->rooks, this->rooks);
            for (unsigned int row = 0; row < raster.vertical_subdivisions(); row++)
            {
                std::uniform_int_distribution<int> dist(0, raster.horizontal_subdivisions() - 1);
                auto value = dist(rando);
                for (int col : columns) {
                    if (value != col)
                    {
                        value = dist(rando);
                    }
                }
                columns.push_back(value);
                double randX = ((double)rand() / RAND_MAX);
                double randY = ((double)rand() / RAND_MAX);
                Point2D random(randX, randY);
                points2d.push_back(raster[Position2D(row, value)].from_relative(random));
            }
            return points2d;

        }

    };
}



raytracer::Sampler raytracer::samplers::nrooks(unsigned int rooks)
{
    return Sampler(std::make_shared<NRooksSampler>(rooks));
}