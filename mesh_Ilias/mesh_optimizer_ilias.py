import sys
sys.setrecursionlimit(1500)


inFile = "buddha.mesh"
outFile = "buddha.bmesh"

print(f"Starting Optimization")

# Point Object
class Point:
	def __init__(point, x, y, z):
		point.x = x
		point.y = y
		point.z = z

# Triangle Object
class Triangle:
	def __init__(triangle, v1, v2, v3, nr1, nr2, nr3):
		triangle.v1 = v1
		triangle.v2 = v2
		triangle.v3 = v3
		triangle.nr1 = nr1
		triangle.nr2 = nr2
		triangle.nr3 = nr3

	def min_x(self):
		return min(self.v1.x, self.v2.x, self.v3.x)

	def min_y(self):
		return min(self.v1.y, self.v2.y, self.v3.y)

	def min_z(self):
		return min(self.v1.z, self.v2.z, self.v3.z)


# Helper Functions
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

# Mesh Creater
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


input = open(inFile, "r")
output = open(outFile, "w")

points = []
first_line = input.readline()
# read how many points there are
point_amount = int(first_line.split(' ')[0])
output.write(first_line)
for point in range(point_amount):
	xyz = input.readline()
	output.write(xyz)
	point_data = xyz.split(' ')
	points.append(Point(float(point_data[0]), float(point_data[1]), float(point_data[2])))

triangles = []
for line in input.readlines():
	if line.startswith('t'):
		numbs = list(map(int, line.split(' ')[1:]))
		triangles.append(Triangle(points[numbs[0]], points[numbs[1]], points[numbs[2]], numbs[0], numbs[1], numbs[2]))


box = []
box.append(make_mesh(triangles))


output.write("b 2\nend")

output.close()
input.close()
print(f"Done Optimizing")
