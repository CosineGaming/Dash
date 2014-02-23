#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#define DEGREES_PER_RADIAN (180 / M_PI)

class Vertex;


class Direction
{
public:
	// Construct a new direction based off of distance and 2 angles
	Direction(const float in_distance = 1.0, const float in_angle_x = 0.0, const float in_angle_y = 0.0);
	// Construct a new direction based off of x, y, and z
	static Direction Coordinates(const float x, const float y, const float z);
	// Destroy a direction
	~Direction(void);
	// Make the distance 1
	void Normalize(const float unit = 1.0);
	// Dot product. Useful for lighting
	float Dot(const Direction& direction) const;
	// Cross product. Finds perpendicular direction to plane defined by 2. Also useful for lighting and angles
	Direction Cross(const Direction& direction) const;
	// Angle between two vectors, useful for rotation
	float Angle_Distance(const Direction& direction) const;
	// Get the relative coordinates of the direction
	float Get_X(void) const;
	float Get_Y(void) const;
	float Get_Z(void) const;
	// Get the distance and angles of the direction
	float Get_Distance(void) const;
	float Get_X_Angle(void) const;
	float Get_Y_Angle(void) const;
	// Set the relative coordinates of the direction
	void Set_X(const float x);
	void Set_Y(const float y);
	void Set_Z(const float z);
	// Set the distance and angles of the direction
	void Set_Distance(const float in_distance);
	void Set_X_Angle(const float in_angle_x);
	void Set_Y_Angle(const float in_angle_y);
	// Set the coordinates of the direction
	void Set_Coordinates(const float x, const float y, const float z);
	// Add values to the coordinates of the direction
	void Add_Coordinates(const float x, const float y = 0.0, const float z = 0.0);
	// Set the distance and angles
	void Set_Direction(const float in_distance, const float in_angle_x, const float in_angle_y);
	// Add values to the distance and angles
	void Add_Direction(const float in_distance, const float in_angle_x = 0.0, const float in_angle_y = 0.0);
	// Find the distance between this direction and another
	Direction Distance(const Direction& to) const;
	// Makes a vertex with the X, Y, and Z values
	Vertex To_Vertex(void) const;
private:
	// The distance stretched when getting coords(1 for a normalized direction)
	float distance;
	// The angle moving left and right, or rotating on the y axis
	float angle_x;
	// The angle moving up and down, or rotating on the x axis
	float angle_y;
};
