// Defines a three-dimensional position

#include "Direction.h"
#include "Vertex.h"
#include "Mesh.h"


// Create a new, blank vertex
Vertex::Vertex(void)
{
	X = 0.0;
	Y = 0.0;
	Z = 0.0;
	return;
}


// Copies a vertex
Vertex::Vertex(const Vertex& vertex)
{
	X = vertex.X;
	Y = vertex.Y;
	Z = vertex.Z;
	return;
}


// Create a vertex with these values
Vertex::Vertex(const float x, const float y, const float z)
{
	X = x;
	Y = y;
	Z = z;
	return;
}


// Destroy a vertex
Vertex::~Vertex(void)
{
	return;
}


// Enables += to add the X, Y, and Z values to a vertex
Vertex& Vertex::operator+=(const Vertex& vertex)
{
	X += vertex.X;
	Y += vertex.Y;
	Z += vertex.Z;
	return *this;
}


// Enables + to put values together into a mesh
Mesh Vertex::operator+(const Vertex& vertex) const
{
	Mesh mesh;
	mesh += *this;
	mesh += vertex;
	return mesh;
}


// Checks whether this Vertex is exactly the same as another
bool Vertex::operator==(const Vertex& check) const
{
	return check.X == this->X && check.Y == this->Y && check.Z == this->Z;
}


// Finds the midpoint between 2 vertices, useful for triangular recursion
Vertex Vertex::Midpoint(const Vertex& vertex) const
{
	Vertex copy = *this;
	copy.X = (X + vertex.X) / 2;
	copy.Y = (Y + vertex.Y) / 2;
	copy.Z = (Z + vertex.Z) / 2;
	return copy;
}


// Returns a direction with the coordinates of the vertex
Direction Vertex::To_Direction(void) const
{
	return Direction::Coordinates(X, Y, Z);
}
