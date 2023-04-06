#ifdef TEST_BUILD
#include "samplers/half-jittered-sampler.h"
#include "Catch.h"
#include <iostream>
using namespace math;

using namespace std;

static unsigned int inside_half(double min, double max, double point)
{
    unsigned int result;
    if (min < point && point < max)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    return result;

}

TEST_CASE("half-jittered: 1")
{
    //Given a rectangle [0,1]×[0,1] and 1×1 samples, the returned sample should inside [0.25,0.75]×[0.25,0.75].
    auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(0, 1), math::Vector2D(1, 0));
    auto half_jittered_sampler = raytracer::samplers::half_jittered(1, 1);


    auto list = half_jittered_sampler->sample(rectangle);


    bool checker = false;

    for (Point2D point : list) {

        if (inside_half(0.25, 0.75, point.x()) == 1 && inside_half(0.25, 0.75, point.y()) == 1) checker = true;
    }
    CHECK(checker == true);
};



TEST_CASE("half-jittered 2:")
{
    //Given a rectangle [0,2]×[0,1] and 1×1 samples, the returned sample should inside [0.5,1.5]×[0.25,0.75].
    auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(0, 2), math::Vector2D(1, 0));
    auto half_jittered_sampler = raytracer::samplers::half_jittered(1, 1);
    auto list = half_jittered_sampler->sample(rectangle);

    bool checker = false;

    for (Point2D point : list) {

        if (inside_half(0.5, 1.5, point.y()) == 1 && inside_half(0.25, 0.75, point.x()) == 1) checker = true;
    }
    CHECK(checker == true);
};


TEST_CASE("half-jittered 3:")
{
    //Given a rectangle [0,1]×[0,2] and 1×1 samples, the returned sample should inside [0.25,0.75]×[0.5,1.5].
    auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(0, 1), math::Vector2D(2, 0));
    auto half_jittered_sampler = raytracer::samplers::half_jittered(1, 1);
    auto list = half_jittered_sampler->sample(rectangle);

    bool checker = false;

    for (Point2D point : list) {
        if (inside_half(0.25, 0.75, point.y()) == 1 && inside_half(0.5, 1.5, point.x()) == 1) checker = true;
    }
    CHECK(checker == true);
};

TEST_CASE("half-jittered 4:")
{
    //Given a rectangle [5,9]×[2,6] and 1×1 samples, the returned sample should inside [6,8]×[3,5].
    auto rectangle = math::Rectangle2D(math::Point2D(5, 2), math::Vector2D(4, 0), math::Vector2D(0, 4));
    auto half_jittered_sampler = raytracer::samplers::half_jittered(1, 1);
    auto list = half_jittered_sampler->sample(rectangle);

    bool checker = false;

    for (Point2D point : list) {
        if (inside_half(6, 8, point.x()) == 1 && inside_half(3, 5, point.y()) == 1) checker = true;
    }
    CHECK(checker == true);
};


TEST_CASE("half-jittered 5:")
{
    auto rectangle = math::Rectangle2D(math::Point2D(0, 0), math::Vector2D(0, 8), math::Vector2D(8, 0));
    auto half_jittered_sampler = raytracer::samplers::half_jittered(2, 2);
    auto list = half_jittered_sampler->sample(rectangle);

    int counter = 0;

    for (Point2D point : list) {
        if (inside_half(1, 3, point.x()) == 1 && inside_half(1, 3, point.y()) == 1) counter += 1;
        if (inside_half(1, 3, point.x()) == 1 && inside_half(5, 7, point.y()) == 1) counter += 1;
        if (inside_half(5, 7, point.x()) == 1 && inside_half(1, 3, point.y()) == 1) counter += 1;
        if (inside_half(5, 7, point.x()) == 1 && inside_half(5, 7, point.y()) == 1) counter += 1;
    }
    CHECK(counter == 4);
};


TEST_CASE("half-jittered 6:")
{
    // [5,7]×[3,7]
    math::Rectangle2D rechthoek(math::Point2D(5, 3), math::Vector2D(2, 0), math::Vector2D(0, 4));
    raytracer::Sampler recht = raytracer::samplers::half_jittered(1, 1);
    auto list = recht->sample(rechthoek);
    bool checker = false;

    for (Point2D point : list) {
        if (inside_half(5, 7, point.x()) == 1 && inside_half(3, 7, point.y()) == 1) checker = true;
    }
    CHECK(checker == true);
};

TEST_CASE("half-jittered 7:") {
    // [0,2]×[0,2]
    math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 2));
    raytracer::Sampler recht = raytracer::samplers::half_jittered(1, 1);
    auto list = recht->sample(rechthoek);

    bool checker = false;
    for (Point2D point : list) {
        if (inside_half(0, 2, point.x()) == 1 && inside_half(0, 2, point.y()) == 1) checker = true;
    }
    CHECK(checker == true);
};

TEST_CASE("half-jittered 8:") {
    // [0,4]×[0,2]
    math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(4, 0), math::Vector2D(0, 2));
    raytracer::Sampler recht = raytracer::samplers::half_jittered(2, 1);
    auto list = recht->sample(rechthoek);

    int counter = 0;
    for (Point2D point : list) {
        if (inside_half(0, 2, point.x()) == 1 && inside_half(0, 2, point.y()) == 1) counter  += 1;
        if (inside_half(2, 4, point.x()) == 1 && inside_half(0, 2, point.y()) == 1) counter += 1;
    }
    CHECK(counter == 2);

};

TEST_CASE("half-jittered 9:") {
    // [0,2]×[0,4]
    math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 4));
    raytracer::Sampler recht = raytracer::samplers::half_jittered(1, 2);
    auto list = recht->sample(rechthoek);

    int counter = 0;
    for (Point2D point : list) {
        if (inside_half(0, 2, point.x()) == 1 && inside_half(0, 2, point.y()) == 1) counter += 1;
        if (inside_half(0, 2, point.x()) == 1 && inside_half(2, 4, point.y()) == 1) counter += 1;
    }
    CHECK(counter == 2);

};

TEST_CASE("half-jittered 10:") {
    // [0,4]×[0,4]
    math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(4, 0), math::Vector2D(0, 4));
    raytracer::Sampler recht = raytracer::samplers::half_jittered(4, 4);
    auto list = recht->sample(rechthoek);

    int counter = 0;
    for (Point2D point : list) {
        if (inside_half(0, 1, point.x()) == 1 && inside_half(0, 1, point.y()) == 1) counter += 1;
        if (inside_half(1, 2, point.x()) == 1 && inside_half(0, 1, point.y()) == 1) counter += 1;
        if (inside_half(2, 3, point.x()) == 1 && inside_half(0, 1, point.y()) == 1) counter += 1;
        if (inside_half(3, 4, point.x()) == 1 && inside_half(0, 1, point.y()) == 1) counter += 1;

        if (inside_half(0, 1, point.x()) == 1 && inside_half(1, 2, point.y()) == 1) counter += 1;
        if (inside_half(1, 2, point.x()) == 1 && inside_half(1, 2, point.y()) == 1) counter += 1;
        if (inside_half(2, 3, point.x()) == 1 && inside_half(1, 2, point.y()) == 1) counter += 1;
        if (inside_half(3, 4, point.x()) == 1 && inside_half(1, 2, point.y()) == 1) counter += 1;

        if (inside_half(0, 1, point.x()) == 1 && inside_half(2, 3, point.y()) == 1) counter += 1;
        if (inside_half(1, 2, point.x()) == 1 && inside_half(2, 3, point.y()) == 1) counter += 1;
        if (inside_half(2, 3, point.x()) == 1 && inside_half(2, 3, point.y()) == 1) counter += 1;
        if (inside_half(3, 4, point.x()) == 1 && inside_half(2, 3, point.y()) == 1) counter += 1;

        if (inside_half(0, 1, point.x()) == 1 && inside_half(3, 4, point.y()) == 1) counter += 1;
        if (inside_half(1, 2, point.x()) == 1 && inside_half(3, 4, point.y()) == 1) counter += 1;
        if (inside_half(2, 3, point.x()) == 1 && inside_half(3, 4, point.y()) == 1) counter += 1;
        if (inside_half(3, 4, point.x()) == 1 && inside_half(3, 4, point.y()) == 1) counter += 1;
    }
    CHECK(counter == 16);

};

#endif