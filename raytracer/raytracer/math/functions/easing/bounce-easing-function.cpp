#include "math/functions/easing/bounce-easing-function.h"
#include "math/interval.h"
#include <assert.h>
# define PI         3.14159265358979323846  

using namespace math;
using namespace math::functions;

EasingFunction math::functions::easing::bounce(int y, int x) {

	std::function<double(double)> lambda = [x, y](double t) {
		assert(interval(0.0, 1.0).contains(t));
		return -exp(-(x)*t) * abs(cos(y * t * PI)) + 1;


	};

	return from_lambda(lambda);
}