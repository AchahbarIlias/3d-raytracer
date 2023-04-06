#include "primitives/bbacc.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
	class BbaccImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:
		const Primitive primitive;
		const math::Box bb;

		BbaccImplementation(const Primitive primitive)
			: primitive(primitive), bb(primitive->bounding_box()) {}

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
		{
			if (bb.is_hit_by(ray))
			{
				return primitive->find_all_hits(ray);
			}
			return std::vector<std::shared_ptr<Hit>>();
		}

		bool find_first_positive_hit(const Ray& ray, Hit* output_hit) const override
		{
			if (bb.is_hit_positively_by(ray))
			{
				return primitive->find_first_positive_hit(ray, output_hit);
			}
			return false;
		}

		math::Box bounding_box() const override
		{
			return bb;
		}
	};
}

Primitive raytracer::primitives::bounding_box_accelerator(const Primitive primitve)
{
	return Primitive(std::make_shared<BbaccImplementation>(primitve));
}
