#include "math/transformation3d.h"
#include "math/transformation-matrices.h"
#include "easylogging++.h"

using namespace math;

Transformation3D math::transformations::translation(const Vector3D& v)
{
    Matrix4x4 tm = transformation_matrices::translation(v);
    Matrix4x4 itm = transformation_matrices::translation(-v);

    return Transformation3D(tm, itm);
}

Transformation3D math::transformations::translate(const Vector3D& displacement)
{
    Matrix4x4 tm = transformation_matrices::translation(displacement);
    Matrix4x4 itm = transformation_matrices::translation(-displacement);

    return Transformation3D(tm, itm);
}

Transformation3D math::transformations::rotate_x(const Angle angle)
{
    Matrix4x4 tm = transformation_matrices::rotation_around_x(angle);
    Matrix4x4 itm = transformation_matrices::rotation_around_x(-angle);

    return Transformation3D(tm, itm);
}

Transformation3D math::transformations::rotate_y(const Angle angle)
{
    Matrix4x4 tm = transformation_matrices::rotation_around_y(angle);
    Matrix4x4 itm = transformation_matrices::rotation_around_y(-angle);

    return Transformation3D(tm, itm);
}

Transformation3D math::transformations::rotate_z(const Angle angle)
{
    Matrix4x4 tm = transformation_matrices::rotation_around_z(angle);
    Matrix4x4 itm = transformation_matrices::rotation_around_z(-angle);

    return Transformation3D(tm, itm);
}

Transformation3D math::transformations::scale(const double sx, const double sy, const double sz)
{
    Matrix4x4 tm = transformation_matrices::scaling(sx, sy, sz);
    Matrix4x4 itm = transformation_matrices::scaling(-sx, -sy, -sz);

    return Transformation3D(tm, itm);
}
