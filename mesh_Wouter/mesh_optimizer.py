import sys
sys.setrecursionlimit(1500)

class Coordinaat:
	# """docstring for Coordinaat"""
	def __init__(obj, x, y, z):
		obj.x = x
		obj.y = y
		obj.z = z

	def __str__(self):
		return "{} {} {}".format(self.x, self.y, self.z)

class Triangle:
	# """docstring for Triangle"""
	def __init__(obj, c1, c2, c3, nr1, nr2, nr3):
		obj.c1 = c1
		obj.c2 = c2
		obj.c3 = c3
		obj.nr1 = nr1
		obj.nr2 = nr2
		obj.nr3 = nr3

	def __str__(self):
		return "triangle {} {} {}".format(self.c1, self.c2, self.c3)

	# Min bepalen in iedere richting
	def calc_min_x(self):
		return min(self.c1.x, self.c2.x, self.c3.x)

	def calc_min_y(self):
		return min(self.c1.y, self.c2.y, self.c3.y)

	def calc_min_z(self):
		return min(self.c1.z, self.c2.z, self.c3.z)

def get_totale_x_dist(list):
	minimum_x = list[0].calc_min_x()
	maximum_x = list[0].calc_min_x()
	for tri in list:
		if tri.calc_min_x() < minimum_x:
			minimum_x = tri.calc_min_x()
		if tri.calc_min_x() > maximum_x:
			maximum_x = tri.calc_min_x()
	return maximum_x - minimum_x

def get_totale_y_dist(list):
	minimum_y = list[0].calc_min_y()
	maximum_y = list[0].calc_min_y()
	for tri in list:
		if tri.calc_min_y() < minimum_y:
			minimum_y = tri.calc_min_y()
		if tri.calc_min_y() > maximum_y:
			maximum_y = tri.calc_min_y()
	return maximum_y - minimum_y

def get_totale_z_dist(list):
	minimum_z = list[0].calc_min_z()
	maximum_z = list[0].calc_min_z()
	for tri in list:
		if tri.calc_min_z() < minimum_z:
			minimum_z = tri.calc_min_z()
		if tri.calc_min_z() > maximum_z:
			maximum_z = tri.calc_min_z()
	return maximum_z - minimum_z

def get_minimum_x(list):
	minimum_x = list[0].calc_min_x()
	for tri in list:
		if tri.calc_min_x() < minimum_x:
			minimum_x = tri.calc_min_x()
	return minimum_x

def get_minimum_y(list):
	minimum_y = list[0].calc_min_y()
	for tri in list:
		if tri.calc_min_y() < minimum_y:
			minimum_y = tri.calc_min_y()
	return minimum_y

def get_minimum_z(list):
	minimum_z = list[0].calc_min_z()
	for tri in list:
		if tri.calc_min_z() < minimum_z:
			minimum_z = tri.calc_min_z()
	return minimum_z

# Functie om de mesh in dozen te steken
def make_mesh(file):
	box = []
	if len(file) > 2:
		box1 = []
		box2 = []
		x_dist = get_totale_x_dist(file)
		y_dist = get_totale_y_dist(file)
		z_dist = get_totale_z_dist(file)

		if max(x_dist, y_dist, z_dist) == x_dist:
			middle = get_minimum_x(file) + (x_dist/2)
			for val in file:
				if float(middle) > float(val.calc_min_x()):
					box1.append(val)
				else:
					box2.append(val)

		elif max(x_dist, y_dist, z_dist) == y_dist:
			middle = get_minimum_y(file) + (y_dist/2)
			for val in file:
				if float(middle) > float(val.calc_min_y()):
					box1.append(val)
				else:
					box2.append(val)

		elif max(x_dist, y_dist, z_dist) == z_dist:
			middle = get_minimum_z(file) + (z_dist/2)
			for val in file:
				if float(middle) > float(val.calc_min_z()):
					box1.append(val)
				else:
					box2.append(val)
		if len(box1) == 0:
			for i in range(len(box2) // 2):
				box1.append(box2[0])
				box2.remove(box2[0])

		box.append(make_mesh(box1))
		if len(box1) < 3:
			outputfile.write("b " + str(len(box1)) + "\n")
		else:
			outputfile.write("b 2\n")
		box.append(make_mesh(box2))
		if len(box2) < 3:
			outputfile.write("b " + str(len(box2)) + "\n")
		else:
			outputfile.write("b 2\n")
		return box

	else:
		for x in range(len(file)):
			outputfile.write("t " + str(file[x].nr1) + " " + str(file[x].nr2) + " " + str(file[x].nr3) + "\n")
		box.append(file)
		return box

# Hier start het gebruik van de files:
inputfile = open("bunny.mesh", "r")
outputfile = open("bunny.bmesh", "w")

# Coordinaten klaar maken
coord = []
amount = inputfile.readline()
outputfile.write(amount)
for x in range(int(amount)):
	xyz = inputfile.readline()
	outputfile.write(xyz)
	string = xyz.split(" ")
	x = float(string[0])
	y = float(string[1])
	z = float(string[2])
	coord.append(Coordinaat(x, y, z))

# Triangles klaar maken
triangles = []
for line in inputfile.readlines():
	if line.startswith('t'):
		string = line.split(" ")
		co1 = int(string[1])
		co2 = int(string[2])
		co3 = int(string[3])
		triangles.append(Triangle(coord[co1], coord[co2], coord[co3], co1, co2, co3))
		print("added {} driehoeken".format(line))

# Nieuwe box maken met alle driehoeken in (telkens verdeeld over 2 dozen)
totale_box = []
totale_box.append(make_mesh(triangles))

# Aflsuiten
print("Process finished, closing files...")
outputfile.write("b 2\nend")
outputfile.close()
inputfile.close()
print("Application finished!")