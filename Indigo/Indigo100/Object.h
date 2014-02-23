// Graphical objects to be displayed on the screen,
// along with useful functions for drawing and warping them

#pragma once

#include "Mesh.h"
#include "Vertex.h"
#include "Direction.h"


class Object
{
public:
	// Create an object given optional position, a mesh,
	// and whether the object should render in wireframe
	Object(const float x = 0.0, const float y = 0.0, const float z = 0.0, const Mesh& mesh = Mesh(), float *color = nullptr,
		void(*update_function)(const int frame, Object& self) = nullptr, const bool smooth = true, const Direction& towards = Direction(1, 0, 0),
		const bool world_collide = true, const float shine = 60.0, const bool line = false);
	// Copy an object
	Object(const Object& object);
	// Destroys the object
	~Object(void);

	// Renders the object
	void Render();

	// Places the object at the X, Y, and Z coordinates
	void Place(const float x, const float y=0.0, const float z=0.0);
	// Moves the forward, side, and up based on the facing direction
	void Move(const float forward, const float side=0.0, const float up=0.0);

	// Checks whether this object collides with another object
	bool Collide(const Object& object, const float add_x=0, const float add_y=0, const float add_z=0) const;
	// Checks whether this object will ever be intersected by a direction
	bool Collide(const Direction& position, const Direction& direction) const;
	// Checks whether this vertex is withing this object
	bool Collide(const Vertex& vertex, const float add_x = 0, const float add_y = 0, const float add_z = 0) const;
	// Changes the relative hitbox for collision, set to 0 0 0 0 to make it uncollidable
	void Set_Hitbox(const float right=0.0, const float top=0.0, const float front=0.0, const float left=0.0, const float bottom=0.0, const float back=0.0);

	// Checked for whether to draw filled or lines
	bool Line;
	// Check if it's been fully initialized
	int Is_Blank;
	// An ID used for accessing and deleting the object
	int ID;
	// Called every time the World updates, set this as you please
	void(*Update)(const int time, Object& self);
	// X, Y, and Z position of center. Z is a constant if 2D.
	float X;
	float Y;
	float Z;
	// Relative position of points
	Mesh Data;
	// The Direction the object is Facing
	Direction facing;
	// Whether or not to use smooth, vertex normals
	bool vertex_normals;
	// The color of the object
	float * object_color;
	// The shininess of the object, from 0 to 128, lower numbers distribute light over greater area
	float object_shine;
	// The OpenGL draw mode for each render type.
	static const int Render_Types[5];
	// Whether or not to collide when searching through World::Collide
	bool World_Collide;
private:
};