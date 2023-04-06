#include "animation/lissajous-animation.h"

using namespace animation;
using namespace math;


Animation<math::Point3D> animation::lissajous(animation::Duration duration, const double& x_amp, const double& y_amp, const double& z_amp,
	const double& x_freq, const double& y_freq, const double& z_freq, math::Angle& x_phase, math::Angle& y_phase, math::Angle& z_phase)
{
	// Create an animation from 0 to 2*pi
	auto double_animation = basic(0, 2 * atan(1) * 4, duration);

	std::function<math::Point3D(TimeStamp)> lambda = [x_amp, y_amp, z_amp, x_freq, y_freq, z_freq, x_phase, y_phase, z_phase, double_animation](TimeStamp now)
		-> math::Point3D
	{
		// Get the current value for t.
		// t == 0 at the beginning of the animation and grows linearly to 2*pi.
		double t = double_animation(now);

		auto x = x_amp * math::sin(Angle::radians(x_freq * t) - x_phase);
		auto y = y_amp * math::sin(Angle::radians(y_freq * t) - y_phase);
		auto z = z_amp * math::sin(Angle::radians(z_freq * t) - z_phase);

		return math::Point3D(x, y, z);
	};

	// Turns the function into an Animation object
	return make_animation(math::from_lambda(lambda), duration);
}
