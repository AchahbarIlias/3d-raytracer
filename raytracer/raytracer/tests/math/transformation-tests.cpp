#ifdef TEST_BUILD

#include "Catch.h"
#include "math/angle.h"
#include "math/transformation2d.h"
#include "math/transformation3d.h"
#include "math/transformation-matrices.h"

using namespace math;
#define V(...)     (__VA_ARGS__)
#define P(...)     (__VA_ARGS__)


#define TEST_TRANSLATION2D(v, p, q)                                      \
    TEST_CASE("Translation by " #v " of " #p " should yield " #q)        \
    {                                                                    \
        auto transformation = transformations::translation(Vector2D v);  \
        auto original = Point2D p;                                       \
        auto transformed = Point2D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

#define TEST_ROTATION2D(v, p, q)                                      \
    TEST_CASE("Translation by " #v " of " #p " should yield " #q)        \
    {                                                                    \
        auto transformation = transformations::rotate(v);                \
        auto original = Point2D p;                                       \
        auto transformed = Point2D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

#define TEST_SCALE2D(v, d, p, q)                                      \
    TEST_CASE("Translation by " #v " of " #p " should yield " #q)        \
    {                                                                    \
        auto transformation = transformations::scale(v, d);              \
        auto original = Point2D p;                                       \
        auto transformed = Point2D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

#define TEST_TRANSLATION3D(v, p, q)                                      \
    TEST_CASE("Translation by " #v " of " #p " should yield " #q)        \
    {                                                                    \
        auto transformation = transformations::translation(Vector3D v);  \
        auto original = Point3D p;                                       \
        auto transformed = Point3D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

#define TEST_ROTATION3D_X(v, p, q)                                      \
    TEST_CASE("Translation by " #v " of " #p " should yield " #q)        \
    {                                                                    \
        auto transformation = transformations::rotate_x(v);                \
        auto original = Point3D p;                                       \
        auto transformed = Point3D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

#define TEST_ROTATION3D_Y(v, p, q)                                      \
    TEST_CASE("Translation by " #v " of " #p " should yield " #q)        \
    {                                                                    \
        auto transformation = transformations::rotate_y(v);              \
        auto original = Point3D p;                                       \
        auto transformed = Point3D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

#define TEST_ROTATION3D_Z(v, p, q)                                      \
    TEST_CASE("Translation by " #v " of " #p " should yield " #q)        \
    {                                                                    \
        auto transformation = transformations::rotate_z(v);              \
        auto original = Point3D p;                                       \
        auto transformed = Point3D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

#define TEST_SCALE3D(v, d, g, p, q)                                      \
    TEST_CASE("Translation by " #v " of " #p " should yield " #q)        \
    {                                                                    \
        auto transformation = transformations::scale(v, d, g);              \
        auto original = Point3D p;                                       \
        auto transformed = Point3D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

TEST_TRANSLATION2D(V(1, 0), P(2, 3), P(3, 3))
TEST_TRANSLATION2D(V(4, 1), P(2, 3), P(6, 4))

auto angle1 = Angle::degrees(90);
auto angle2 = Angle::degrees(180);
TEST_ROTATION2D(V(angle1), P(2, 3), P(-3, 2))
TEST_ROTATION2D(V(angle2), P(2, 3), P(-2, -3))

TEST_SCALE2D(V(1.0), V(1.0), P(2, 3), P(2, 3))

TEST_TRANSLATION3D(V(1, 0, 0), P(2, 3, 0), P(3, 3, 0))
TEST_TRANSLATION3D(V(4, 1, 1), P(2, 3, 3), P(6, 4, 4))

TEST_ROTATION3D_X(V(angle1), P(2, 3, 3), P(2, -3, 3))

TEST_ROTATION3D_Y(V(angle1), P(2, 3, 3), P(3, 3, -2))

TEST_ROTATION3D_Z(V(angle1), P(2, 3, 3), P(-3, 2, 3))

#endif