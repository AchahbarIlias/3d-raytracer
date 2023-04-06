#ifndef EXCLUDE_SCRIPTING

#include "scripting/samplers-module.h"
#include "samplers/samplers.h"
#include "scripting/scripting-util.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    struct SamplerLibrary
    {
        Sampler single() const
        {
            return samplers::single();
        }
        Sampler stratified(const int& rows, const int& cols) const
        {
            return samplers::stratified(rows, cols);
        }
        Sampler halfjittered(const int& rows, const int& cols) const
        {
            return samplers::half_jittered(rows, cols);
        }
        Sampler random(int count) const
        {
            return samplers::random(count);
        }
        Sampler jittered(const int& rows, const int& cols) const
        {
            return samplers::jittered(rows, cols);
        }

        Sampler nrooks(const int n) const
        {
            return samplers::nrooks(n);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_samplers_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Sampler>(*module, "Sampler");

    auto sampler_library = std::make_shared<SamplerLibrary>();
    module->add_global_const(chaiscript::const_var(sampler_library), "Samplers");

#   define BIND(NAME)  module->add(fun(&SamplerLibrary::NAME), #NAME)
    BIND(single);
    BIND(stratified);
    BIND(halfjittered);
    BIND(random);
    BIND(jittered);
    BIND(nrooks);
#   undef BIND

    return module;
}

#endif
