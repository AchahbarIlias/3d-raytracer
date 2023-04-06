#include "primitives/mesh/mesh-primitive.h"
#include "easylogging++.h"
#include <primitives/mesh/mesh-text-reader.h>
#include <primitives/triangle-primitive.h>
#include <primitives/union-primitive.h>
#include <primitives/bbacc.h>


using namespace raytracer;
using namespace raytracer::primitives;

class MeshReceiverImplementation : public raytracer::primitives::MeshReceiver
{
public:
	std::vector<math::Point3D> vertices;
	std::vector<Primitive> stack;

	virtual void vertex(double x, double y, double z) override
	{
		auto vertex = math::Point3D(x, y, z);
		vertices.push_back(vertex);
	}

	virtual void normal(double x, double y, double z) override
	{
	}

	virtual void triangle(unsigned vertex1, unsigned vertex2, unsigned vertex3) override
	{
		Primitive triangle = raytracer::primitives::triangle(vertices[vertex1], vertices[vertex2], vertices[vertex3]);
		stack.push_back(triangle);
	}

	virtual void box(unsigned n_children) override
	{
		std::vector<Primitive> triangles_for_bbacc;
		while (n_children > 0)
		{
			triangles_for_bbacc.push_back(stack.back());
			stack.pop_back();
			n_children--;
		}
		stack.push_back(raytracer::primitives::bounding_box_accelerator(make_union(triangles_for_bbacc)));
	}
};

Primitive raytracer::primitives::mesh(const std::string& path)
{
	std::ifstream input_stream(path);
	CHECK(input_stream.is_open()) << "Failed to open file at " << path;
	MeshReceiverImplementation meshRec;
	read_text_mesh(input_stream, meshRec);
	return Primitive(make_union(meshRec.stack));
}
