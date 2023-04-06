from datetime import datetime
import sys
sys.setrecursionlimit(1500)

startTime = datetime.now()

class Vertex:
	def __init__(obj, x, y, z):
		obj.x = x
		obj.y = y
		obj.z = z

class Triangle:
	def __init__(obj, v1, v2, v3, nr1, nr2, nr3):
		obj.v1 = v1
		obj.v2 = v2
		obj.v3 = v3
		obj.nr1 = nr1
		obj.nr2 = nr2
		obj.nr3 = nr3

	def min_x(self):
		return min(self.v1.x, self.v2.x, self.v3.x)

	def min_y(self):
		return min(self.v1.y, self.v2.y, self.v3.y)

	def min_z(self):
		return min(self.v1.z, self.v2.z, self.v3.z)

def get_total_x_distance(triangles):
	maximum_x = max(triangles, key = lambda t: t.min_x()).min_x()
	minimum_x = min(triangles, key = lambda t: t.min_x()).min_x()
	return maximum_x - minimum_x

def get_total_y_distance(triangles):
	maximum_y = max(triangles, key = lambda t: t.min_y()).min_y()
	minimum_y = min(triangles, key = lambda t: t.min_y()).min_y()
	return maximum_y - minimum_y

def get_total_z_distance(triangles):
	maximum_z = max(triangles, key = lambda t: t.min_z()).min_z()
	minimum_z = min(triangles, key = lambda t: t.min_z()).min_z()
	return maximum_z - minimum_z

def get_minimum_x(triangles):
	return min(triangles, key = lambda t: t.min_x()).min_x()

def get_minimum_y(triangles):
	return min(triangles, key = lambda t: t.min_y()).min_y()

def get_minimum_z(triangles):
	return min(triangles, key = lambda t: t.min_z()).min_z()

def make_mesh(triangles):
	box = []
	if len(triangles) > 2:
		box1 = []
		box2 = []
		x_distance = get_total_x_distance(triangles)
		y_distance = get_total_y_distance(triangles)
		z_distance = get_total_z_distance(triangles)

		if max(x_distance, y_distance, z_distance) == x_distance:
			middle = get_minimum_x(triangles) + (x_distance/2)
			for val in triangles:
				if float(middle) > float(val.min_x()):
					box1.append(val)
				else:
					box2.append(val)

		elif max(x_distance, y_distance, z_distance) == y_distance:
			middle = get_minimum_y(triangles) + (y_distance/2)
			for val in triangles:
				if float(middle) > float(val.min_y()):
					box1.append(val)
				else:
					box2.append(val)

		elif max(x_distance, y_distance, z_distance) == z_distance:
			middle = get_minimum_z(triangles) + (z_distance/2)
			for val in triangles:
				if float(middle) > float(val.min_z()):
					box1.append(val)
				else:
					box2.append(val)

		if len(box1) == 0:
			for i in range(len(box2) // 2):
				box1.append(box2[0])
				box2.remove(box2[0])

		box.append(make_mesh(box1))
		if len(box1) < 3:
			output.write(f"b {str(len(box1))}\n")
		else:
			output.write("b 2\n")
		box.append(make_mesh(box2))
		if len(box2) < 3:
			output.write(f"b {str(len(box2))}\n")
		else:
			output.write("b 2\n")
		return box

	else:
		for i in range(len(triangles)):
			output.write(f"t {str(triangles[i].nr1)} {str(triangles[i].nr2)} {str(triangles[i].nr3)}\n")
		box.append(triangles)
		return box

print("Opening the input and output file")
inputFileName = "buddha.mesh"
outputFileName = "optimized.mesh"
input = open(inputFileName, "r")
output = open(outputFileName, "w")

vertices = []
first_line = input.readline()
vertex_count = int(first_line.split(' ')[0])
print(f"Reading in {vertex_count} vertices")
output.write(first_line)
for vertex in range(vertex_count):
	xyz = input.readline()
	output.write(xyz)
	vertex_list = xyz.split(' ')
	x = float(vertex_list[0])
	y = float(vertex_list[1])
	z = float(vertex_list[2])
	vertices.append(Vertex(x, y, z))

print("Creating all triangles")
triangles = []
for line in input.readlines():
	if line.startswith('t'):
		vertex_numbers = list(map(int, line.split(' ')[1:]))
		vertex1 = vertex_numbers[0]
		vertex2 = vertex_numbers[1]
		vertex3 = vertex_numbers[2]
		triangles.append(Triangle(vertices[vertex1], vertices[vertex2], vertices[vertex3], vertex1, vertex2, vertex3))

print("Creating new box with all triangles (each divided into 2 boxes)")
box = []
box.append(make_mesh(triangles))

print("Writing end to output file")
output.write("b 2\nend")

print("Closing files")
output.close()
input.close()
runtime = str(datetime.now() - startTime).split('.')[0]
print(f"\nFinished in {runtime}")
