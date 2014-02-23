// Defines a mesh of points for render

#include "Mesh.h"
#include "Direction.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


// Create a new, empty mesh
Mesh::Mesh(const int group_size)
{
	Hitbox[0] = Vertex(0, 0, 0);
	Hitbox[1] = Vertex(0, 0, 0);
	Group_Size = group_size;
	vertices = std::vector<Vertex>();
	elements = std::vector<int>();
	texture = -1;
	return;
}


// Create a new mesh with some vertices
Mesh::Mesh(const std::vector <Vertex>& add_vertices, const int group_size)
{
	vertices = std::vector<Vertex>();
	elements = std::vector<int>();
	Add(add_vertices);
	Group_Size = group_size;
	texture = -1;
	return;
}


// Copy a mesh
Mesh::Mesh(const Mesh& mesh)
{
	vertices = mesh.vertices;
	elements = mesh.elements;
	flat_normals = mesh.flat_normals;
	smooth_normals = mesh.smooth_normals;
	Group_Size = mesh.Group_Size;
	Hitbox[0] = mesh.Hitbox[0];
	Hitbox[1] = mesh.Hitbox[1];
	texture = mesh.texture;
	return;
}


// Destroy the mesh
Mesh::~Mesh(void)
{
	return;
}


// Once added to the object, the mesh is locked into place
void Mesh::Initialize(void)
{
	Smooth_Normals();
	return;
}


// The following functions are Mesh Constructors:
// A function to construct a mesh of the type with it's name.
// /*Example:*/ Mesh myCubeMesh = Mesh::Cube(1.0, 50.0, 24.2, 13.5);
Mesh Mesh::Load(const char * filename)
{
	Mesh mesh(3);
	std::ifstream file(filename, std::ios::in);
	if (!file)
	{
		std::cout << "Unable to open file " << filename << ". Replacing mesh with empty mesh.\n";
	}
	else
	{
		std::vector<Vertex> options;
		std::string line;
		while (std::getline(file, line))
		{
			if (line[0] == 'v' && line[1] == ' ')
			{
				std::istringstream stream(line.substr(2));
				Vertex option;
				stream >> option.X;
				stream >> option.Y;
				stream >> option.Z;
				options.push_back(option);
			}
			else if (line[0] == 'f' && line[1] == ' ')
			{
				std::string values(line.substr(2));
				int face[3];
				face[0] = atoi(values.c_str());
				values = values.substr(values.find(' ') + 1);
				face[1] = atoi(values.c_str());
				values = values.substr(values.find(' ') + 1);
				face[2] = atoi(values.c_str());
				face[0] -= 1;
				face[1] -= 1;
				face[2] -= 1;
				mesh += options[face[0]];
				mesh += options[face[1]];
				mesh += options[face[2]];
			}
		}
		file.close();
	}
	return mesh;
}


Mesh Mesh::Sphere(const float radius, const int recursions, const bool draw_sphere)
{
	Mesh mesh(3);
	Vertex top = Vertex(0.0, radius, 0.0);
	Direction cursor(radius, 0.0, 0.0);
	for (int triangle = 0; triangle<8; ++triangle)
	{
		if (triangle == 4)
		{
			top = Vertex(0.0, -1 * radius, 0.0);
		}
		Vertex left = cursor.To_Vertex();
		cursor.Add_Direction(0.0, 90.0, 0.0);
		Vertex right = cursor.To_Vertex();
		mesh += Bulge_Sphere(radius, recursions, left, right, top);
	}
	return mesh;
}


Mesh Mesh::Box(const float width, const float height, const float length)
{
	Mesh mesh = Mesh();
	float Half_Lengths[3] =
	{
		width / 2.0f,
		height / 2.0f,
		length / 2.0f
	};
	int Pair[2] = { 0, 1 };
	mesh.Group_Size = 4;
	for (int Side = 0; Side<3; Side++)
	{
		for (int Twice = 0; Twice<2; Twice++)
		{
			for (int Point = 0; Point<4; Point++)
			{
				Half_Lengths[Pair[Point % 2]] *= -1;
				mesh += Vertex(Half_Lengths[0],
					Half_Lengths[1], Half_Lengths[2]);
			}
			if (0 == Twice)
			{
				Half_Lengths[0] *= -1;
				Half_Lengths[1] *= -1;
				Half_Lengths[2] *= -1;
				Half_Lengths[Pair[0]] *= -1;
			}
		}
		Pair[2 != Pair[1]] += 1; // 0, 1; 0, 2; 1, 2
	}
	return mesh;
}


Mesh Mesh::Line(const float width, const float height, const float length)
{
	Mesh mesh;
	mesh += Vertex(0.0, 0.0, 0.0);
	mesh += Vertex(width, height, length);
	return mesh;
}


Mesh Mesh::Cube(const float side)
{
	return Box(side, side, side);
}


Mesh Mesh::Regular_Shape(const int sides, const float side_length)
{
	Mesh mesh(1);
	mesh += Vertex(0.0, 0.0, 0.0);
	Direction cursor(side_length);
	for (; cursor.Get_X_Angle() <= 360.0; cursor.Add_Direction(0.0, 360.0 / sides))
	{
		mesh += cursor.To_Vertex();
	}
	return mesh;
}


Mesh Mesh::Rectangle(const float width, const float height)
{
	Mesh mesh(4);
	mesh += Vertex(width / -2, height / -2, 0.0);
	mesh += Vertex(width / 2, height / -2, 0.0);
	mesh += Vertex(width / 2, height / 2, 0.0);
	mesh += Vertex(width / -2, height / 2, 0.0);
	return mesh;
}


// Used in recursion for the Sphere function
Mesh Mesh::Bulge_Sphere(const float radius, const int recursions,
	const Vertex& left, const Vertex& right, const Vertex& top)
{
	Mesh mesh(0);
	if (recursions > 0)
	{
		Vertex mid_left = left.Midpoint(top);
		Vertex mid_right = top.Midpoint(right);
		Vertex mid_top = left.Midpoint(right);
		mesh += Bulge_Sphere(radius, recursions - 1, mid_left, mid_right, mid_top);
		mesh += Bulge_Sphere(radius, recursions - 1, mid_left, mid_right, top);
		mesh += Bulge_Sphere(radius, recursions - 1, left, mid_top, mid_left);
		mesh += Bulge_Sphere(radius, recursions - 1, mid_top, right, mid_right);
	}
	else
	{
		Vertex options[3] = { left, right, top };
		for (int vertex = 0; vertex<3; ++vertex)
		{
			Direction distance = options[vertex].To_Direction();
			distance.Set_Distance(radius);
			mesh += Vertex(distance.Get_X(), distance.Get_Y(), distance.Get_Z());
		}
	}
	return mesh;
}


// Allows [] to get a vertex like an array
Vertex& Mesh::operator[](const int index) const
{
	return Get_Vertex(index);
}


// Allows += to add a vertex to the end
Mesh& Mesh::operator+=(const Vertex& vertex)
{
	Add(vertex);
	return *this;
}


// Allows += to add a mesh to the end
Mesh& Mesh::operator+=(const Mesh& mesh)
{
	Add(mesh.Get_Vertices());
	return *this;
}


// Allows += to add a vector of vertices to the end
Mesh& Mesh::operator+=(const std::vector <Vertex>& add_vertices)
{
	Add(add_vertices);
	return *this;
}


// Allows + to add a vertex to the end
Mesh Mesh::operator+(const Vertex& vertex) const
{
	Mesh copy = *this;
	copy.Add(vertex);
	return copy;
}


// Allows + to add a mesh to the end
Mesh Mesh::operator+(const Mesh& mesh) const
{
	Mesh copy = *this;
	copy.Add(mesh.Get_Vertices());
	return copy;
}


Mesh Mesh::operator+(const std::vector <Vertex>& add_vertices) const
{
	// Allows + to add vertices to the end
	Mesh copy = *this;
	copy.Add(add_vertices);
	return copy;
}


// Add a new vertex to the end of the mesh,
// the last vertex made to be 0,0,0.
// So if the last was 0,1,5, then 2,-1,3 would add 2,0,8
void Mesh::Add_Relative(const Vertex& vertex)
{
	Vertex add = vertex;
	Vertex last;
	if (vertices.size() != 0)
	{
		Vertex last = vertices.back();
	}
	add += last;
	Add(add);
	return;
}


// Add a new mesh to the end relative to the last point
void Mesh::Add_Relative(const Mesh& mesh)
{
	Add_Relative(mesh.Get_Vertices());
	return;
}


// Add a new set of vertices to the end relative to the last point
void Mesh::Add_Relative(const std::vector <Vertex>& add_vertices)
{
	Vertex last;
	if (add_vertices.size() != 0)
	{
		Vertex last = add_vertices.back();
	}
	for (int Point = 0; Point<add_vertices.size(); ++Point)
	{
		Vertex add = add_vertices[Point];
		add += last;
		Add(add);
	}
	return;
}


// Gets a vertex by its index
Vertex& Mesh::Get_Vertex(const int index) const
{
	return const_cast<Vertex&>(vertices[elements[index]]);
}


// Get all the vertices, or a subset of them 
std::vector<Vertex> Mesh::Get_Vertices(int beginning, int end) const
{
	if (beginning < 0)
	{
		beginning += elements.size();
	}
	if (end < 0)
	{
		end += elements.size();
	}
	if (end < beginning)
	{
		end = beginning;
	}
	end += 1;
	std::vector<int> options = std::vector<int>(elements.begin() + beginning, elements.begin() + end);
	std::vector<Vertex> all;
	for (int i = 0; i < options.size(); ++i)
	{
		all.push_back(vertices[options[i]]);
	}
	return all;
}


// Calculate all per-vertex normals for the mesh
void Mesh::Smooth_Normals(void)
{
	smooth_normals = std::vector<Vertex>();
	Vertex * normals = new Vertex[Vertex_Data_Amount()];
	int * amounts = new int[Vertex_Data_Amount()];
	for (int point = 0; point < Vertex_Data_Amount(); ++point)
	{
		normals[point] = Vertex(0, 0, 0);
		amounts[point] = 0;
	}
	for (int point = 0; point < Size(); ++point)
	{
		normals[elements[point]] += Flat_Normal(point);
		amounts[elements[point]]++;
	}
	for (int point = 0; point < Vertex_Data_Amount(); ++point)
	{
		if (amounts[point] != 0)
		{
			normals[point].X /= amounts[point];
			normals[point].Y /= amounts[point];
			normals[point].Z /= amounts[point];
			smooth_normals.push_back(normals[point]);
		}
		else
		{
			// Incorrectly ==ed, pick a fairly random but hopefully related normal
			smooth_normals.push_back(Flat_Normal(point * Group_Size));
		}
	}
	delete [] normals;
	delete [] amounts;
}


// Get the normal for a specific vertex by face
Vertex Mesh::Flat_Normal(const int index) const
{
	if (index < 3 && Group_Size == 0)
	{
		if (Size() >= 3)
			return flat_normals[2];
		else
			return Vertex(0, 0, 0);
	}
	else
		return flat_normals[Group_Size != 0 ? index / Group_Size : index - 3];
}


// Get the smoother per-vertex normal for a vertex; calculate if needed
Vertex Mesh::Smooth_Normal(const int index)
{
	return smooth_normals[elements[index]];
}


// Texture the entire mesh with one file, texture coordinates will be used only once called
void Mesh::Texture(char * filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file)
	{
		std::cout << "Cannot find file " << filename << " aborting texture loading." << std::endl;
		return;
	}
	char header[54];
	file.read(header, 54);
	if (header[0] != 'B' || header[1] != 'M')
	{
		std::cout << "Incorrectly configured or corrupted datafile " << filename << ". Aborting." << std::endl;
	}
	int start = *(int*) &(header[0x0A]);
	int size = *(int*) &(header[0x22]);
	int width = *(int*) &(header[0x12]);
	int height = *(int*) &(header[0x16]);
	if (size == 0)
	{
		size = width*height * 3;
	}
	if (start == 0)
	{
		start = 54;
	}
	char * data = new char[size];
	file.read(data, size);
	file.close();

	unsigned int handle;
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	texture = handle;
	delete [] data;
}


// Get the coordinates of the texture, as a vertex with X and Y (and Z omitted) for a vertex
Vertex Mesh::Texture_Coordinate(const int index)
{
	if (texture_coordinates.size() < index + 1)
	{
		return Vertex((index % Group_Size) % 3 != 0, index % Group_Size < 2, 0);
	}
	else if (texture_coordinates[index] == Vertex(-1, -1, -1))
	{
		return Vertex((index % Group_Size) % 3 != 0, index % Group_Size < 2, 0);
	}
	else
	{
		return texture_coordinates[index];
	}
}


// Set the coordinates of the texture, as a vertex with X and Y (and Z omitted) for a vertex. For the special cases that the automatic isn't nice.
void Mesh::Set_Texture_Coordinate(const int index, const Vertex& coordinate)
{
	if (texture_coordinates.size() < index + 1)
	{
		for (int i = 0; i < texture_coordinates.size() - index - 1; ++i)
		{
			texture_coordinates.push_back(Vertex(-1, -1, -1));
		}
	}
	texture_coordinates[index] = coordinate;
}


// Get the number of elements in the mesh
int Mesh::Size(void) const
{
	return elements.size();
}


// Number of actual different vertices defined
int Mesh::Vertex_Data_Amount(void) const
{
	return vertices.size();
}


void Mesh::Add(const Vertex& vertex)
{
	// Checks if this vertex has been mentioned before
	bool duplicate = false;
	for (int Check = 0; Check<Vertex_Data_Amount(); ++Check)
	{
		if (vertex == vertices[Check])
		{
			elements.push_back(Check);
			duplicate = true;
		}
	}
	// Add a new vertex to the end of the mesh if not a duplicate
	if (!duplicate)
	{
		vertices.push_back(vertex);
		elements.push_back(Vertex_Data_Amount() - 1);
		// Update the hitbox with the new vertex
		if (vertex.X < Hitbox[0].X)
		{
			Hitbox[0].X = vertex.X;
		}
		if (vertex.Y < Hitbox[0].Y)
		{
			Hitbox[0].Y = vertex.Y;
		}
		if (vertex.Z < Hitbox[0].Z)
		{
			Hitbox[0].Z = vertex.Z;
		}
		if (vertex.X > Hitbox[1].X)
		{
			Hitbox[1].X = vertex.X;
		}
		if (vertex.Y > Hitbox[1].Y)
		{
			Hitbox[1].Y = vertex.Y;
		}
		if (vertex.Z > Hitbox[1].Z)
		{
			Hitbox[1].Z = vertex.Z;
		}
	}
	// Calculate the light normal if this ends a face
	int point = Size() - 1;
	if (point % (Group_Size > 2 ? Group_Size : 1) == Group_Size - 1 || (Group_Size < 3 && point >= 3))
	{
		Direction normal = Get_Vertex(point - 1).To_Direction().Distance(Get_Vertex(point - 2).To_Direction());
		Direction with = Get_Vertex(point).To_Direction().Distance(Get_Vertex(point - 2).To_Direction());
		normal = normal.Cross(with);
		normal.Normalize();
		with = Get_Vertex(point - 2).To_Direction();
		if (normal.Dot(with) > 0)
		{
			Vertex value = normal.To_Vertex();
			flat_normals.push_back(Vertex(value.X * -1, value.Y * -1, value.Z * -1));
		}
		else
		{
			flat_normals.push_back(normal.To_Vertex());
		}
	}
	return;
}


// Add new vertices to the end of the mesh
void Mesh::Add(const Mesh& mesh)
{
	for (int Point = 0; Point < mesh.Size(); ++Point)
	{
		Add(mesh[Point]);
	}
	return;
}


// Add new vertices to the end of the mesh
void Mesh::Add(const std::vector <Vertex>& add_vertices)
{
	for (int Point = 0; Point < add_vertices.size(); ++Point)
	{
		Add(add_vertices[Point]);
	}
	return;
}