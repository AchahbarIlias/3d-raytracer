#include "cameras/fisheye-camera.h"
#include <assert.h>
#include "math/interval-mapper.h"

using namespace raytracer;
using namespace raytracer::cameras;
using namespace math;


raytracer::cameras::_private_::FisheyeCamera::FisheyeCamera(const math::Matrix4x4 transformation, math::Angle horizontal_angle, math::Angle vertical_angle)
	: DisplaceableCamera(transformation), m_horizontal_angle(horizontal_angle), m_vertical_angle(vertical_angle)
{
	// NOP
}

void raytracer::cameras::_private_::FisheyeCamera::enumerate_untransformed_rays(const Point2D& point, std::function<void(const math::Ray&)> callback) const
{
	const auto horizontal_interval = interval(-m_horizontal_angle.degrees() / 2 - 90, m_horizontal_angle.degrees() / 2 - 90);
	const auto vertical_interval = interval(-m_vertical_angle.degrees() / 2, m_vertical_angle.degrees() / 2);

	const auto horizontal_mapper = IntervalMapper<double, double>(interval(0.0, 1.0), horizontal_interval);
	const auto vertical_mapper = IntervalMapper<double, double>(interval(0.0, 1.0), vertical_interval);

	Point3D p = Point3D::spherical(1, Angle::degrees(horizontal_mapper[point.x()]), Angle::degrees(vertical_mapper[point.y()]));

	callback(Ray(math::Point3D(0, 0, 0), p));
}

Camera raytracer::cameras::fisheye(
	const math::Point3D& eye,
	const math::Point3D& look_at,
	const math::Vector3D& up,
	math::Angle horizontal_angle,
	math::Angle vertical_angle)
{
	assert(up.is_unit());

	Matrix4x4 transformation = _private_::create_transformation(eye, look_at, up);

	return Camera(std::make_shared<_private_::FisheyeCamera>(transformation, horizontal_angle, vertical_angle));
}
