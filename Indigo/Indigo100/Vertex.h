#pragma once

class Mesh;

class Direction;


class Vertex
{
public:
	// Create a new, blank vertex
	Vertex(void);
	// Copies a vertex
	Vertex(const Vertex& vertex);
	// Create a vertex with these values
	Vertex(const float x, const float y, const float z=0);
	// Destroy a vertex
	~Vertex(void);
	// Enables += to add the X, Y, and Z values to a vertex
	Vertex& operator+=(const Vertex& vertex);
	// Enables + to put values together into a mesh
	Mesh operator+(const Vertex& vertex) const;
	// Checks whether this Vertex is (0, 0, 0)
	bool operator==(const Vertex& check) const;
	// Finds the midpoint between 2 vertices, useful for triangular recursion
	Vertex Midpoint(const Vertex& vertex) const;
	// Returns a direction with the coordinates of the vertex
	Direction To_Direction(void) const;
	// Position of the vertex
	float X;
	float Y;
	float Z;
private:
};