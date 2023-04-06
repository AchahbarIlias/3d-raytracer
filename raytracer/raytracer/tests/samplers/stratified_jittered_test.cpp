#ifdef TEST_BUILD
#include "Catch.h"
#include "math/rectangle2d.h"
#include "samplers/jittered-sampler.h"


bool check_inside(std::vector<math::Point2D> list, int xmin, int xmax, int ymin, int ymax) {
	for (unsigned i = 0; i < list.size(); i++) {
		if ((xmin < list[i].x())   &&   (list[i].x() < xmax)    && (ymin < list[i].y())   &&   (list[i].y() < ymax)) {
			return true;
		}
	}
	return false;
};

TEST_CASE("jittered first test") {
	// [0,1]x[0,1]
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 1));
	raytracer::Sampler recht = raytracer::samplers::jittered(1, 1);
	auto list = recht->sample(rechthoek);
	CHECK(check_inside(list, 0, 1, 0, 1) == true);

};

TEST_CASE("jittered second test") {
	// [0,2]×[0,1]
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 1));
	raytracer::Sampler recht = raytracer::samplers::jittered(1, 1);
	auto list = recht->sample(rechthoek);
	CHECK(check_inside(list, 0, 2, 0, 1) == true);

};

TEST_CASE("jittered third test") {
	// [0,1]×[0,2]
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 2));
	raytracer::Sampler recht = raytracer::samplers::jittered(1, 1);
	auto list = recht->sample(rechthoek);
	CHECK(check_inside(list, 0, 1, 0, 2) == true);

};

TEST_CASE("jittered fourth test") {
	// [5,7]×[3,8]
	math::Rectangle2D rechthoek(math::Point2D(5, 3), math::Vector2D(2, 0), math::Vector2D(0, 5));
	raytracer::Sampler recht = raytracer::samplers::jittered(1, 1);
	auto list = recht->sample(rechthoek);
	CHECK(check_inside(list, 5, 7, 3, 8) == true);

};

TEST_CASE("jittered fifth test") {
	// [0,2]×[0,2]
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 2));
	raytracer::Sampler recht = raytracer::samplers::jittered(2,2);
	auto list = recht->sample(rechthoek);
	CHECK(check_inside(list, 0,1,0,1) == true);
	CHECK(check_inside(list, 1,2,0,1) == true);
	CHECK(check_inside(list, 0,1,1,2) == true);
	CHECK(check_inside(list, 1,2,1,2) == true);

};

TEST_CASE("jittered sixth test") {
	// [5,7]×[3,7]
	math::Rectangle2D rechthoek(math::Point2D(5, 3), math::Vector2D(2, 0), math::Vector2D(0, 4));
	raytracer::Sampler recht = raytracer::samplers::jittered(1,1);
	auto list = recht->sample(rechthoek);
	CHECK(check_inside(list, 5,7,3,7) == true);
	

};

TEST_CASE("jittered seventh test") {
	// [0,2]×[0,2]
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 2));
	raytracer::Sampler recht = raytracer::samplers::jittered(1, 1);
	auto list = recht->sample(rechthoek);
	CHECK(check_inside(list, 0,2,0,2) == true);


};

TEST_CASE("jittered eighth test") {
	// [0,4]×[0,2]
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(4, 0), math::Vector2D(0, 2));
	raytracer::Sampler recht = raytracer::samplers::jittered(2, 1);
	auto list = recht->sample(rechthoek);
	CHECK(check_inside(list, 0, 2, 0, 2) == true);
	CHECK(check_inside(list, 2, 4, 0, 2) == true);


};

TEST_CASE("jittered ninth test") {
	// [0,2]×[0,4]
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 4));
	raytracer::Sampler recht = raytracer::samplers::jittered(1,2);
	auto list = recht->sample(rechthoek);
	CHECK(check_inside(list, 0, 2, 0 ,2) == true);
	CHECK(check_inside(list, 0, 2,2,4) == true);


};

TEST_CASE("jittered tenth test") {
	// [0,4]×[0,4]
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(4, 0), math::Vector2D(0, 4));
	raytracer::Sampler recht = raytracer::samplers::jittered(4, 4);
	auto list = recht->sample(rechthoek);
	CHECK(check_inside(list, 0, 1, 0, 1) == true);
	CHECK(check_inside(list, 1,2, 0, 1) == true);
	CHECK(check_inside(list, 2, 3, 0, 1) == true);
	CHECK(check_inside(list, 3,4, 0, 1) == true);

	CHECK(check_inside(list, 0, 1, 1,2) == true);
	CHECK(check_inside(list, 1, 2, 1,2) == true);
	CHECK(check_inside(list, 2, 3, 1,2) == true);
	CHECK(check_inside(list, 3, 4, 1,2) == true);

	CHECK(check_inside(list, 0, 1, 2, 3) == true);
	CHECK(check_inside(list, 1, 2, 2, 3) == true);
	CHECK(check_inside(list, 2, 3, 2, 3) == true);
	CHECK(check_inside(list, 3, 4, 2, 3) == true);

	CHECK(check_inside(list, 0, 1, 3, 4) == true);
	CHECK(check_inside(list, 1, 2, 3, 4) == true);
	CHECK(check_inside(list, 2, 3, 3, 4) == true);
	CHECK(check_inside(list, 3, 4, 3, 4) == true);
	
};

#endif