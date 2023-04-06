#ifdef TEST_BUILD

#include "Catch.h"
#include "math/quaternion.h"

using namespace math;

#define Q(a, b, c, d)          (a, b, c, d)                      \

#define TEST_ADDITION(q1, q2, qe)                                \
    TEST_CASE("Addition of "#q1 " and " #q2 " should give " #qe) \
    {                                                            \
       Quaternion quat1 q1;                                      \
       Quaternion quat2 q2;                                      \
       Quaternion expected qe;                                   \
       SECTION("Using operator +")                               \
       {                                                         \
           Quaternion actual = quat1 + quat2;                    \
           CHECK(actual == expected);                            \
       }                                                         \
       SECTION("Using operator +=")                              \
       {                                                         \
           quat1 += quat2;                                       \
           CHECK(quat1 == expected);                             \
       }                                                         \
    }

#define TEST_SUBTRACTION(q1, q2, qe)                                \
    TEST_CASE("Subtraction of "#q1 " and " #q2 " should give " #qe) \
    {                                                            \
       Quaternion quat1 q1;                                      \
       Quaternion quat2 q2;                                      \
       Quaternion expected qe;                                   \
       SECTION("Using operator -")                               \
       {                                                         \
           Quaternion actual = quat1 - quat2;                    \
           CHECK(actual == expected);                            \
       }                                                         \
       SECTION("Using operator -=")                              \
       {                                                         \
           quat1 -= quat2;                                       \
           CHECK(quat1 == expected);                             \
       }                                                         \
    }

#define TEST_MULTIPLICATION(q1, qe, x)                                \
    TEST_CASE("Multiplication of "#q1 " and " #x " should give " #qe) \
    {                                                            \
       Quaternion quat1 q1;                                      \
       Quaternion expected qe;                                   \
       SECTION("Using operator *")                               \
       {                                                         \
           Quaternion actual1 = quat1 * x;                       \
           Quaternion actual2 = x * quat1;                       \
           CHECK(actual1 == expected);                           \
           CHECK(actual2 == expected);                           \
       }                                                         \
       SECTION("Using operator *=")                              \
       {                                                         \
           quat1 *= x;                                           \
           CHECK(quat1 == expected);                             \
       }                                                         \
    }

#define TEST_QQ_MULTIPLICATION(q1, q2, qe)                                \
    TEST_CASE("Multiplication of "#q1 " and " #q2 " should give " #qe) \
    {                                                            \
       Quaternion quat1 q1;                                      \
       Quaternion quat2 q2;                                      \
       Quaternion expected qe;                                   \
       SECTION("Using operator *")                               \
       {                                                         \
           Quaternion actual1 = quat1 * quat2;                   \
           CHECK(actual1 == expected);                           \
       }                                                         \
    }

#define AXIS(x, y, z)     (x, y, z)
#define POINT(x, y, z)    (x, y, z)

#define TEST_ROTATION(axis_, angle_, point_, expected_)                        \
    TEST_CASE("Rotation of " #point_ " by " #angle_ " degrees around " #axis_) \
    {                                                                          \
      Vector3D axis axis_;                                                     \
      Angle angle = Angle::degrees(angle_);                                    \
      Point3D point point_;                                                    \
      Point3D expected expected_;                                              \
      Quaternion quaternion = Quaternion::rotation(angle, axis);               \
      Point3D actual = quaternion.rotate(point);                               \
      CHECK(actual == approx(expected));                                       \
    }

TEST_ADDITION(Q(0,0,0,0), Q(0,0,0,0), Q(0,0,0,0))
TEST_ADDITION(Q(1,0,0,0), Q(0,0,0,0), Q(1,0,0,0))
TEST_ADDITION(Q(0,1,0,0), Q(0,0,0,0), Q(0,1,0,0))
TEST_ADDITION(Q(0,0,1,0), Q(0,0,0,0), Q(0,0,1,0))
TEST_ADDITION(Q(0,0,0,1), Q(0,0,0,0), Q(0,0,0,1))
TEST_ADDITION(Q(3,5,2,1), Q(7,4,2,6), Q(10,9,4,7))

TEST_SUBTRACTION(Q(0, 0, 0, 0), Q(0, 0, 0, 0), Q(0, 0, 0, 0))
TEST_SUBTRACTION(Q(0, 0, 0, 0), Q(1, 0, 0, 0), Q(-1, 0, 0, 0))
TEST_SUBTRACTION(Q(0, 0, 0, 0), Q(0, 1, 0, 0), Q(0, -1, 0, 0))
TEST_SUBTRACTION(Q(0, 0, 0, 0), Q(0, 0, 1, 0), Q(0, 0, -1, 0))
TEST_SUBTRACTION(Q(0, 0, 0, 0), Q(0, 0, 0, 1), Q(0, 0, 0, -1))
TEST_SUBTRACTION(Q(3, 5, 2, 1), Q(7, 4, 2, 6), Q(-4, 1, 0, -5))

TEST_MULTIPLICATION(Q(0, 0, 0, 0), Q(0, 0, 0, 0), 5)
TEST_MULTIPLICATION(Q(1, 0, 0, 0), Q(5, 0, 0, 0), 5)
TEST_MULTIPLICATION(Q(0, 1, 0, 0), Q(0, 3, 0, 0), 3)
TEST_MULTIPLICATION(Q(0, 0, 1, 0), Q(0, 0, 7, 0), 7)
TEST_MULTIPLICATION(Q(0, 0, 0, 1), Q(0, 0, 0, 4), 4)
TEST_MULTIPLICATION(Q(1, 2, 3, 4), Q(2, 4, 6, 8), 2)

TEST_QQ_MULTIPLICATION(Q(1, 0, 0, 0), Q(1, 0, 0, 0), Q(1, 0, 0, 0))
TEST_QQ_MULTIPLICATION(Q(1, 0, 0, 0), Q(0, 1, 0, 0), Q(0, 1, 0, 0))
TEST_QQ_MULTIPLICATION(Q(1, 0, 0, 0), Q(0, 0, 1, 0), Q(0, 0, 1, 0))
TEST_QQ_MULTIPLICATION(Q(1, 0, 0, 0), Q(0, 0, 0, 1), Q(0, 0, 0, 1))
TEST_QQ_MULTIPLICATION(Q(0, 1, 0, 0), Q(0, 1, 0, 0), Q(-1, 0, 0, 0))
TEST_QQ_MULTIPLICATION(Q(0, 1, 0, 0), Q(0, 0, 1, 0), Q(0, 0, 0, 1))
TEST_QQ_MULTIPLICATION(Q(0, 1, 0, 0), Q(0, 0, 0, 1), Q(0, 0, -1, 0))

TEST_ROTATION(AXIS(1, 0, 0), 90, POINT(1, 0, 0), POINT(1, 0, 0))
TEST_ROTATION(AXIS(1, 0, 0), 180, POINT(1, 0, 0), POINT(1, 0, 0))
TEST_ROTATION(AXIS(1, 0, 0), 270, POINT(1, 0, 0), POINT(1, 0, 0))

TEST_ROTATION(AXIS(0, 1, 0), 90, POINT(1, 0, 0), POINT(0, 0, -1))
TEST_ROTATION(AXIS(0, 1, 0), 180, POINT(1, 0, 0), POINT(-1, 0, 0))
TEST_ROTATION(AXIS(0, 1, 0), 270, POINT(1, 0, 0), POINT(0, 0, 1))

TEST_ROTATION(AXIS(0, 0, 1), 90, POINT(1, 0, 0), POINT(0, 1, 0))
TEST_ROTATION(AXIS(0, 0, 1), 180, POINT(1, 0, 0), POINT(-1, 0, 0))
TEST_ROTATION(AXIS(0, 0, 1), 270, POINT(1, 0, 0), POINT(0, -1, 0))

TEST_ROTATION(AXIS(1, 0, 0), 90, POINT(0, 1, 0), POINT(0, 0, 1))
TEST_ROTATION(AXIS(1, 0, 0), 180, POINT(0, 1, 0), POINT(0, -1, 0))
TEST_ROTATION(AXIS(1, 0, 0), 270, POINT(0, 1, 0), POINT(0, 0, -1))

TEST_ROTATION(AXIS(0, 1, 0), 90, POINT(0, 1, 0), POINT(0, 1, 0))
TEST_ROTATION(AXIS(0, 1, 0), 180, POINT(0, 1, 0), POINT(0, 1, 0))
TEST_ROTATION(AXIS(0, 1, 0), 270, POINT(0, 1, 0), POINT(0, 1, 0))

TEST_ROTATION(AXIS(0, 0, 1), 90, POINT(0, 1, 0), POINT(-1, 0, 0))
TEST_ROTATION(AXIS(0, 0, 1), 180, POINT(0, 1, 0), POINT(0, -1, 0))
TEST_ROTATION(AXIS(0, 0, 1), 270, POINT(0, 1, 0), POINT(1, 0, 0))

TEST_ROTATION(AXIS(1, 0, 0), 90, POINT(0, 0, 1), POINT(0, -1, 0))
TEST_ROTATION(AXIS(1, 0, 0), 180, POINT(0, 0, 1), POINT(0, 0, -1))
TEST_ROTATION(AXIS(1, 0, 0), 270, POINT(0, 0, 1), POINT(0, 1, 0))

TEST_ROTATION(AXIS(0, 1, 0), 90, POINT(0, 0, 1), POINT(1, 0, 0))
TEST_ROTATION(AXIS(0, 1, 0), 180, POINT(0, 0, 1), POINT(0, 0, -1))
TEST_ROTATION(AXIS(0, 1, 0), 270, POINT(0, 0, 1), POINT(-1, 0, 0))

TEST_ROTATION(AXIS(0, 0, 1), 90, POINT(0, 0, 1), POINT(0, 0, 1))
TEST_ROTATION(AXIS(0, 0, 1), 180, POINT(0, 0, 1), POINT(0, 0, 1))
TEST_ROTATION(AXIS(0, 0, 1), 270, POINT(0, 0, 1), POINT(0, 0, 1))

#endif
