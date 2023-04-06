#include "circular-animation.h"
#include "data-structures/array.h"
#include "math/quaternion.h"

using namespace animation;
using namespace math;

Animation<Point3D> animation::circular(const Point3D& point, const Point3D& center, const Vector3D& rotation_axis, const Interval<Angle>& angle_interval, const Duration& duration)
{

	auto double_animation = basic(0, 1, duration);

	std::function<Point3D(TimeStamp)> lambda = [point, center, rotation_axis, angle_interval, double_animation](TimeStamp now) -> Point3D {

		const auto angle = angle_interval.from_relative(double_animation(now));
		Quaternion quaternion = Quaternion::rotation(angle, rotation_axis);
		Point3D p = quaternion.rotate(Point3D(point.x() - center.x(), point.y() - center.y(), point.z() - center.z()));
		p = Point3D(p.x() + center.x(), p.y() + center.y(), p.z() + center.z());
		return p;
	};

	return make_animation(from_lambda(lambda), duration);
}