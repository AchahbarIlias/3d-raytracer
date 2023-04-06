#ifdef TEST_BUILD
#include "Catch.h"
#include "samplers/samplers.h"
#include "math/rectangle2d.h"
#include "samplers/stratified-sampler.h"

bool check_contains(std::vector<math::Point2D> list, math::Point2D point) {
	for (unsigned i = 0; i < list.size(); i++) {
		if (list[i] == point) {
			return true;
		}
	}
	return false;
};

TEST_CASE("first test") {
	// [0,1]x[0,1]
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(1,0), math::Vector2D(0,1));
	
	// [5,7]x[3,7]
	math::Rectangle2D rechthoek2 (math::Point2D(5, 3), math::Vector2D(2, 0), math::Vector2D(0, 4));

	// [left,right]x[bottom,top]
	//math::Rectangle2D rechthoek(math::Point2D(left, bottom), math::Vector2D(right-left, 0), math::Vector2D(0, top-bottom));

	raytracer::Sampler recht = raytracer::samplers::stratified(1, 1);
	auto list =recht->sample(rechthoek2);
	auto point = math::Point2D(6,5);
	CHECK(check_contains(list,point) == true);
	
}
TEST_CASE("second test") {
	// [0,1]x[0,1]
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(1, 0), math::Vector2D(0, 1));
	raytracer::Sampler recht = raytracer::samplers::stratified(1, 1);
	auto list = recht->sample(rechthoek);
	auto point = math::Point2D(0.5,0.5);
	CHECK(check_contains(list,point) == true);

}
TEST_CASE("third test") {
	// [0,2]×[0,2]
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 2));
	raytracer::Sampler recht = raytracer::samplers::stratified(1, 1);
	auto list = recht->sample(rechthoek);
	auto point = math::Point2D(1, 1);
	CHECK(check_contains(list, point) == true);

}
TEST_CASE("fourth test") {
	// [0,4]×[0,2] 
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(4, 0), math::Vector2D(0, 2));
	raytracer::Sampler recht = raytracer::samplers::stratified(2, 1);
	auto list = recht->sample(rechthoek);
	auto point = math::Point2D(1, 1);
	auto point2 = math::Point2D(3, 1);
	CHECK(check_contains(list, point) == true);
	CHECK(check_contains(list, point2) == true);

}
TEST_CASE("fifth test") {
	// [0,2]×[0,4] 
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(2, 0), math::Vector2D(0, 4));
	raytracer::Sampler recht = raytracer::samplers::stratified(1,2);
	auto list = recht->sample(rechthoek);
	auto point = math::Point2D(1, 1);
	auto point2 = math::Point2D(1,3);
	CHECK(check_contains(list, point) == true);
	CHECK(check_contains(list, point2) == true);

}
TEST_CASE("sixth test") {
	// [0,4]×[0,4] 
	math::Rectangle2D rechthoek(math::Point2D(0, 0), math::Vector2D(4, 0), math::Vector2D(0, 4));
	raytracer::Sampler recht = raytracer::samplers::stratified(4,4);
	auto list = recht->sample(rechthoek);
	
	for (auto i = 0; i < 4;i++) {

		for (auto j = 0; j < 4; j++) {
			
			CHECK(check_contains(list, math::Point2D(0.5 + i, 0.5 + j)) == true);
			
			
		}	

	}

}

TEST_CASE("seventh test") {
	// [4,8]×[0,4] 
	math::Rectangle2D rechthoek(math::Point2D(4, 0), math::Vector2D(4, 0), math::Vector2D(0, 4));
	raytracer::Sampler recht = raytracer::samplers::stratified(1,1);
	auto list = recht->sample(rechthoek);

	auto point = math::Point2D(6, 2);
	CHECK(check_contains(list, point) == true);
	

}
TEST_CASE("eight test") {
	// [4,8]×[0,4] 
	math::Rectangle2D rechthoek(math::Point2D(4, 0), math::Vector2D(4, 0), math::Vector2D(0, 4));
	raytracer::Sampler recht = raytracer::samplers::stratified(2, 1);
	auto list = recht->sample(rechthoek);

	auto point = math::Point2D(5, 2);
	auto point2 = math::Point2D(7, 2);
	CHECK(check_contains(list, point) == true);
	CHECK(check_contains(list, point2) == true);

}
TEST_CASE("ninth test") {
	// [4,8]×[0,4] 
	math::Rectangle2D rechthoek(math::Point2D(4, 0), math::Vector2D(4, 0), math::Vector2D(0, 4));
	raytracer::Sampler recht = raytracer::samplers::stratified(1,2);
	auto list = recht->sample(rechthoek);

	auto point = math::Point2D(6, 3);
	auto point2 = math::Point2D(6, 1);
	CHECK(check_contains(list, point) == true);
	CHECK(check_contains(list, point2) == true);

}
TEST_CASE("tenth test") {
	// [4,9]×[1,3] 
	math::Rectangle2D rechthoek(math::Point2D(4, 1), math::Vector2D(5, 0), math::Vector2D(0, 2));
	raytracer::Sampler recht = raytracer::samplers::stratified(1, 1);
	auto list = recht->sample(rechthoek);

	auto point = math::Point2D(6.5, 2);
	CHECK(check_contains(list, point) == true);
	
}
#endif