#pragma once

#include <vector>
#include "Direction.h"
#include "Vertex.h"
#include "glut.h"


class Mesh
{
public:
	// Create a new, empty mesh
	Mesh(const int group_size=3);
	// Create a new mesh with some vertices and an optional group size
	Mesh(const std::vector <Vertex>& vertices, const int group_size=3);
	// Copy a mesh
	Mesh(const Mesh& mesh);
	// Destroy the mesh
	~Mesh(void);
	// Once added to the object, the mesh is locked into place
	void Initialize(void);
	// Mesh constructors:
	// A function to construct a mesh of the type with it's name.
	// /*Example*/ Mesh myCubeMesh = Mesh::Cube(1.0, 50.0, 24.2, 13.5);
	static Mesh Load(const char * filename);
	static Mesh Sphere(const float radius, const int recusions=3, const bool draw_sphere=true);
	static Mesh Box(const float width, const float height, const float length);
	static Mesh Line(const float width, const float height=0.0, const float length=0.0);
	static Mesh Cube(const float side);
	static Mesh Regular_Shape(const int sides, const float side_length);
	static Mesh Rectangle(const float width, const float height);
	// Used in recursion for the Sphere function
	static Mesh Bulge_Sphere(const float radius, const int recursions,
		const Vertex& left, const Vertex& right, const Vertex& top);
	// Allows [] to get a vertex like an array
	Vertex& operator[](const int index) const;
	// Allows += to add a vertex to the end
	Mesh& operator+=(const Vertex& vertex);
	// Allows += to add a mesh to the end
	Mesh& operator+=(const Mesh& mesh);
	// Allows += to add a vector of vertices to the end
	Mesh& operator+=(const std::vector <Vertex>& vertices);
	// Allows + to add a vertex to the end
	Mesh operator+(const Vertex& vertex) const;
	// Allows + to add a mesh to the end
	Mesh operator+(const Mesh& mesh) const;
	// Allows + to add a vector of vertices to the end
	Mesh operator+(const std::vector <Vertex>& vertices) const;
	// Add a new vertex to the end of the mesh,
	// the last vertex made to be 0,0,0.
	// So if the last was 0,1,5, then 2,-1,3 would add 2,0,8
	void Add_Relative(const Vertex& vertex);
	// Add a new mesh to the end relative to the last point
	void Add_Relative(const Mesh& mesh);
	// Add a new set of vertices to the end relative to the last point
	void Add_Relative(const std::vector <Vertex>& vertices);
	// Gets a vertex by its index
	Vertex& Get_Vertex(const int index) const;
	// Get all the vertices, or a subset of them 
	std::vector <Vertex> Get_Vertices(int beginning = 0, int end = -1) const;
	// Calculate all per-vertex normals for the mesh
	void Mesh::Smooth_Normals(void);
	// Get the normal for a specific vertex
	Vertex Flat_Normal(const int index) const;
	// Get the smoother per-vertex normal for a vertex; calculate if needed
	Vertex Smooth_Normal(const int index);
	// Texture the entire mesh with one file, texture coordinates will be used only once called
	void Texture(char * filename);
	// Get the coordinates of the texture, as a vertex with X and Y (and Z omitted) for a vertex
	Vertex Texture_Coordinate(const int index);
	// Set the coordinates of the texture, as a vertex with X and Y (and Z omitted) for a vertex. For the special cases that the automatic isn't nice.
	void Set_Texture_Coordinate(const int index, const Vertex& coordinate);
	// Get the number of Vertices in the mesh
	int Size(void) const;
	// Number of actual different vertices defined
	int Vertex_Data_Amount(void) const;
	// How many sides to each polygon
	int Group_Size;
	// Hitbox used for collision, normally auto-generated. {Left Bottom Back}, {Right Top Front}
	Vertex Hitbox[2];
	// Add points to the mesh in function notation
	void Add(const Vertex& vertex);
	void Add(const Mesh& mesh);
	void Add(const std::vector <Vertex>& vertices);
	// The per-face normals; less pretty and not used by default
	std::vector<Vertex> flat_normals;
	// The per-vertex normals. Only calculated once added to world
	std::vector<Vertex> smooth_normals;
	// The vertices to choose from
	std::vector<Vertex> vertices;
	// The actual vertices in order; indices of vertices (0 for first, unlike obj files)
	std::vector<int> elements;
	// The texture handle number
	int texture;
	// A set of texture coordinates, one for every element. Manually set with Set_Texture_Coordinate()
	std::vector<Vertex> texture_coordinates;
private:
};