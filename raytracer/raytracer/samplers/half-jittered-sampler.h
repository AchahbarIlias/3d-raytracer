#pragma once

#include "samplers/sampler.h"


namespace raytracer
{
	namespace samplers
	{
		Sampler half_jittered(unsigned const int rows, unsigned const int cols);
	}
}