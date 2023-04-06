#include "math/quaternion.h"
#include <math\angle.h>
#include <math\vector.h>
#include <math\point.h>

using namespace math;

math::Quaternion::Quaternion(double a, double b, double c, double d) : m_a(a), m_b(b), m_c(c), m_d(d) {}

math::Quaternion::Quaternion(Angle theta, const Vector3D& axis) :
	m_a(cos(theta / 2)),
	m_b(sin(theta / 2)* axis.x()),
	m_c(sin(theta / 2)* axis.y()),
	m_d(sin(theta / 2)* axis.z())
{}

math::Quaternion math::Quaternion::rotation(math::Angle theta, const math::Vector3D& axis)
{
	return math::Quaternion(theta, axis);
}

Point3D math::Quaternion::rotate(const Point3D& point) const
{
	auto p2 = *this * Quaternion(0, point.x(), point.y(), point.z()) * conjugate();

	return Point3D(p2.m_b, p2.m_c, p2.m_d);
}

Quaternion math::Quaternion::conjugate() const
{
	return Quaternion(m_a, -m_b, -m_c, -m_d);
}

Quaternion math::Quaternion::operator +(const Quaternion& q) const
{
	return Quaternion(m_a + q.m_a, m_b + q.m_b, m_c + q.m_c, m_d + q.m_d);
}

Quaternion math::Quaternion::operator -(const Quaternion& q) const
{
	return Quaternion(m_a - q.m_a, m_b - q.m_b, m_c - q.m_c, m_d - q.m_d);
}

Quaternion math::Quaternion::operator *(double d) const
{
	return Quaternion(m_a * d, m_b * d, m_c * d, m_d * d);
}

Quaternion math::Quaternion::operator *(const Quaternion& q) const
{
	return Quaternion((m_a * q.m_a - m_b * q.m_b - m_c * q.m_c - m_d * q.m_d),
		(m_a * q.m_b + m_b * q.m_a + m_c * q.m_d - m_d * q.m_c),
		(m_a * q.m_c - m_b * q.m_d + m_c * q.m_a + m_d * q.m_b),
		(m_a * q.m_d + m_b * q.m_c - m_c * q.m_b + m_d * q.m_a));
}

Quaternion math::Quaternion::operator /(double d) const
{
	return Quaternion(m_a / d, m_b / d, m_c / d, m_d / d);
}

Quaternion math::Quaternion::operator +=(const Quaternion& q)
{
	return *this = *this + q;
}

Quaternion math::Quaternion::operator -=(const Quaternion& q)
{
	return *this = *this - q;
}

Quaternion math::Quaternion::operator *=(double d)
{
	return *this = *this * d;
}

Quaternion math::Quaternion::operator /=(double d)
{
	return *this = *this / d;
}

bool math::Quaternion::operator ==(const Quaternion& q)
{
	return this->m_a == q.m_a && this->m_b == q.m_b && this->m_c == q.m_c && this->m_d == q.m_d;
}

bool math::Quaternion::operator !=(const Quaternion& q)
{
	return this->m_a != q.m_a || this->m_b != q.m_b || this->m_c != q.m_c || this->m_d != q.m_d;
}
