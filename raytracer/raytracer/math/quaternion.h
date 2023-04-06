#pragma once

#include "math/angle.h"
#include "math/vector.h"
#include "math/point.h"


namespace math {
	class Quaternion {
	public:
		Quaternion(double a, double b, double c, double d);
		Quaternion(math::Angle, const math::Vector3D&);

		static Quaternion rotation(math::Angle, const math::Vector3D&);

		math::Point3D rotate(const math::Point3D&) const;

		Quaternion conjugate() const;

		Quaternion operator +(const Quaternion&) const;

		Quaternion operator -(const Quaternion&) const;

		Quaternion operator *(double) const;

		Quaternion operator *(const Quaternion&) const;

		Quaternion operator /(double) const;

		Quaternion operator +=(const Quaternion&);

		Quaternion operator -=(const Quaternion&);

		Quaternion operator *=(double);

		Quaternion operator /=(double);

		bool operator ==(const Quaternion&);

		bool operator !=(const Quaternion&);

	private:
		double m_a;
		double m_b;
		double m_c;
		double m_d;
	};

	inline Quaternion operator *(double d, const Quaternion& q)
	{
		return q * d;
	}

}
