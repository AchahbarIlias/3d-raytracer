#ifdef TEST_BUILD
#include "samplers/n-rooks-sampler.h"
#include "Catch.h"
#include <iostream>
using namespace math;
using namespace std;


static int inside_nrooks(double min, double max, double point)
{
    unsigned int result;
    if (min <= point && point <= max)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    return result;

}

TEST_CASE("n-rooks: 1")
{
    auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(0, 1), math::Vector2D(1, 0));
    auto sampler = raytracer::samplers::nrooks(1);
    auto sampled = sampler->sample(rectangle);

    bool checker = false;


    for (Point2D point : sampled) {

        if (inside_nrooks(0, 1, point.x()) == 1 && inside_nrooks(0, 1, point.y()) == 1) checker = true;
    }


    REQUIRE(checker == true);

}


TEST_CASE("n-rooks: 2")
{
    auto rectangle = math::Rectangle2D(math::Point2D(4, 6), math::Vector2D(4, 0), math::Vector2D(0, 1));
    auto sampler = raytracer::samplers::nrooks(1);
    auto list = sampler->sample(rectangle);

    bool checker = false;
    for (Point2D point : list) {
        if (inside_nrooks(4, 8, point.x()) == 1 && inside_nrooks(6, 8, point.y()) == 1) checker = true;
    }

    CHECK(checker == true);
}

TEST_CASE("n-rooks: 3")
{
    auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(0, 4), math::Vector2D(4, 0));
    auto sampler = raytracer::samplers::nrooks(4);
    auto list = sampler->sample(rectangle);

    int counter = 0;

    for (Point2D point : list) {
        //x
        if (inside_nrooks(0, 1, point.x()) == 1) counter += 1;
        if (inside_nrooks(1, 2, point.x()) == 1) counter += 1;
        if (inside_nrooks(2, 3, point.x()) == 1) counter += 1;
        if (inside_nrooks(3, 4, point.x()) == 1) counter += 1;
        //y
        if (inside_nrooks(0, 1, point.y()) == 1) counter += 1;
        if (inside_nrooks(1, 2, point.y()) == 1) counter += 1;
        if (inside_nrooks(2, 3, point.y()) == 1) counter += 1;
        if (inside_nrooks(3, 4, point.y()) == 1) counter += 1;


    }

    CHECK(counter == 8);

}

TEST_CASE("n-rooks: 4")
{
    auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(8, 0), math::Vector2D(0, 8));
    auto sampler = raytracer::samplers::nrooks(1);
    auto list = sampler->sample(rectangle);

    bool checker = false;


    for (Point2D point : list) {
        if (inside_nrooks(0, 8, point.x()) == 1 && inside_nrooks(0, 8, point.y()) == 1) checker = true;

    }

    CHECK(checker == true);
}


TEST_CASE("n-rooks: 5")
{
    auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(0, 7), math::Vector2D(7, 0));
    auto sampler = raytracer::samplers::nrooks(7);
    auto list = sampler->sample(rectangle);

    int counter = 0;

    for (Point2D point : list) {
        //x
        if (inside_nrooks(0, 1, point.x()) == 1) counter += 1;
        if (inside_nrooks(1, 2, point.x()) == 1) counter += 1;
        if (inside_nrooks(2, 3, point.x()) == 1) counter += 1;
        if (inside_nrooks(3, 4, point.x()) == 1) counter += 1;
        if (inside_nrooks(4, 5, point.x()) == 1) counter += 1;
        if (inside_nrooks(5, 6, point.x()) == 1) counter += 1;
        if (inside_nrooks(6, 7, point.x()) == 1) counter += 1;
        //y
        if (inside_nrooks(0, 1, point.y()) == 1) counter += 1;
        if (inside_nrooks(1, 2, point.y()) == 1) counter += 1;
        if (inside_nrooks(2, 3, point.y()) == 1) counter += 1;
        if (inside_nrooks(3, 4, point.y()) == 1) counter += 1;
        if (inside_nrooks(4, 5, point.y()) == 1) counter += 1;
        if (inside_nrooks(5, 6, point.y()) == 1) counter += 1;
        if (inside_nrooks(6, 7, point.y()) == 1) counter += 1;


    }

    CHECK(counter == 14);
}

#endif