#pragma once
#include "animation/animation.h"

namespace animation
{
	Animation<math::Point3D> lissajous(animation::Duration duration, const double& x_amp, const double& y_amp, const double& z_amp,
		const double& x_freq, const double& y_freq, const double& z_freq, math::Angle& x_phase, math::Angle& y_phase, math::Angle& z_phase);
}