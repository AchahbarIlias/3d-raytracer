#ifndef EXCLUDE_SCRIPTING

#include "scripting/animation-module.h"
#include "scripting/scripting-util.h"
#include "raytracers/scene.h"
#include "animation/animations.h"
#include "math/angle.h"
#include "math/functions.h"


using namespace chaiscript;
using namespace raytracer;
using namespace math;
using namespace imaging;
using namespace animation;


namespace
{
    struct AnimationLibrary
    {
        Animation<Point3D> point_animation(const Point3D& from, const Point3D& to, Duration duration) const
        {
            return animation::animate(from, to, duration);
        }

        Animation<double> double_animation(double from, double to, Duration duration) const
        {
            return animation::animate(from, to, duration);
        }

        Animation<Angle> angle_animation(Angle from, Angle to, Duration duration) const
        {
            return animation::animate(from, to, duration);
        }

        template<typename T>
        Animation<T> ease_animation(Animation<T> animation, math::functions::EasingFunction easing_function) const
        {
            return animation::ease(animation, easing_function);
        }

		Animation<Point3D> lissajous_animation(animation::Duration duration, const double& x_amp, const double& y_amp, const double& z_amp,
			const double& x_freq, const double& y_freq, const double& z_freq, math::Angle& x_phase, math::Angle& y_phase, math::Angle& z_phase) const
		{
			return animation::lissajous(duration, x_amp, y_amp, z_amp, x_freq, y_freq, z_freq, x_phase, y_phase, z_phase);
		}

		Animation<Point3D> lissajous_animation_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
		{
            Duration duration = Duration::zero();

			START_ARGUMENTS(argument_map);
            BIND_ARGUMENT(duration);
			OPTIONAL_ARGUMENT(int, x_amplitude, 1);
			OPTIONAL_ARGUMENT(int, y_amplitude, 1);
			OPTIONAL_ARGUMENT(int, z_amplitude, 1);
			OPTIONAL_ARGUMENT(int, x_frequency, 1);
			OPTIONAL_ARGUMENT(int, y_frequency, 1);
			OPTIONAL_ARGUMENT(int, z_frequency, 1);
			OPTIONAL_ARGUMENT(Angle, x_phase, 0_degrees);
			OPTIONAL_ARGUMENT(Angle, y_phase, 0_degrees);
			OPTIONAL_ARGUMENT(Angle, z_phase, 0_degrees);
			END_ARGUMENTS();

			return animation::lissajous(duration, x_amplitude, y_amplitude, z_amplitude, x_frequency, y_frequency, z_frequency, x_phase, y_phase, z_phase);
		}

        Animation<Point3D> circular_animation(Point3D& point, Point3D& center, Vector3D& rotation_axis, Interval<math::Angle>& angle_interval, Duration duration) const
        {
            return animation::circular(point, center, rotation_axis, angle_interval, duration);
        }

        Animation<Point3D> circular_animation_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            START_ARGUMENTS(argument_map);
            OPTIONAL_ARGUMENT(Point3D, position, Point3D(0, 0, 1));
            OPTIONAL_ARGUMENT(Point3D, around, Point3D(0, 0, 0));
            OPTIONAL_ARGUMENT(Vector3D, axis, Vector3D(0, 1, 0));
            OPTIONAL_ARGUMENT(Interval<Angle>, angle_interval, math::interval(Angle::degrees(0), Angle::degrees(360)));
            OPTIONAL_ARGUMENT(Duration, duration, Duration::from_seconds(1));
            END_ARGUMENTS();

            return circular_animation(position, around, axis, angle_interval, duration);
        }
    };

    Duration seconds(double s)
    {
        return Duration::from_seconds(s);
    }

    TimeStamp epoch()
    {
        return TimeStamp::zero();
    }

    Animation<std::shared_ptr<Scene>> make_scene_animation(std::function<std::shared_ptr<Scene>(TimeStamp)> function, Duration duration)
    {
        return Animation<std::shared_ptr<Scene>>(from_lambda(function), duration);
    }
}

ModulePtr raytracer::scripting::_private_::create_animation_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_to_string<Duration>(*module);
    util::register_to_string<TimeStamp>(*module);

    auto animation_library = std::make_shared<AnimationLibrary>();
    module->add_global_const(chaiscript::const_var(animation_library), "Animations");

#define BIND_AS(INTERNAL, EXTERNAL)                 module->add(fun(&AnimationLibrary::INTERNAL), #EXTERNAL)
#define BIND(NAME)                                  BIND_AS(NAME, NAME)
    BIND_AS(double_animation, animate);
    BIND_AS(point_animation, animate);
    BIND_AS(angle_animation, animate);
    BIND_AS(ease_animation<double>, ease);
    BIND_AS(ease_animation<Angle>, ease);
    BIND_AS(ease_animation<Point3D>, ease);
    BIND_AS(lissajous_animation, lissajous);
    BIND_AS(lissajous_animation_by_map, lissajous);
    BIND_AS(circular_animation, circular);
    BIND_AS(circular_animation_by_map, circular);

#undef BIND
#undef BIND_AS

    module->add(fun(&seconds), "seconds");
    module->add(fun(&epoch), "epoch");
    module->add(fun([](TimeStamp t, Duration d) { return t + d; }), "+");
    module->add(fun([](Duration d, TimeStamp t) { return t + d; }), "+");
    module->add(fun(&Animation<Point3D>::operator()), "[]");
    module->add(fun(&Animation<Angle>::operator()), "[]");
    module->add(fun(&Animation<double>::operator()), "[]");
    module->add(fun(&make_scene_animation), "scene_animation");

    return module;
}

#endif
