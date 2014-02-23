#include "Direction.h"
#include "Vertex.h"
#include <iostream>


// Construct a new direction based off of distance and 2 angles
Direction::Direction(const float in_distance, const float in_angle_x, const float in_angle_y)
{
	Set_Direction(in_distance, in_angle_x, in_angle_y);
	return;
}


// Construct a new direction based off of x, y, and z
Direction Direction::Coordinates(const float x, const float y, const float z)
{
	Direction construct;
	construct.Set_Coordinates(x, y, z);
	return construct;
}


// Destroy a direction
Direction::~Direction(void)
{
	return;
}


// Make the distance 1
void Direction::Normalize(const float unit)
{
	Set_Direction(unit, Get_X_Angle(), Get_Y_Angle());
}


// Dot product. Useful for lighting
float Direction::Dot(const Direction& direction) const
{
	float answer = (Get_X() * direction.Get_X()) + (Get_Y() * direction.Get_Y()) + (Get_Z() * direction.Get_Z());
	return answer;
}


// Cross product. Finds perpendicular direction to plane defined by 2. Also useful for lighting and angles
Direction Direction::Cross(const Direction& direction) const
{
	return Direction::Coordinates(
		Get_Y() * direction.Get_Z() - Get_Z() * direction.Get_Y(),
		Get_Z() * direction.Get_X() - Get_X() * direction.Get_Z(),
		Get_X() * direction.Get_Y() - Get_Y() * direction.Get_X());
}


// Angle between two vectors, useful for rotation
float Direction::Angle_Distance(const Direction& direction) const
{
	if (!(Get_X_Angle() == direction.Get_X_Angle() && Get_Y_Angle() == direction.Get_Y_Angle() && Get_Distance() == direction.Get_Distance()))
	{
		return acos(Dot(direction) / (Get_Distance() * direction.Get_Distance())) * DEGREES_PER_RADIAN;
	}
	return 0;
}


// Get the relative coordinates of the direction
float Direction::Get_X(void) const
{
	return sin(angle_x) * cos(angle_y) * distance;
}

float Direction::Get_Y(void) const
{
	return sin(angle_y) * distance;
}

float Direction::Get_Z(void) const
{
	return cos(angle_x) * cos(angle_y) * distance;
}


// Get the distance and angles of the direction
float Direction::Get_Distance(void) const
{
	return distance;
}

float Direction::Get_X_Angle(void) const
{
	return angle_x * DEGREES_PER_RADIAN;
}

float Direction::Get_Y_Angle(void) const
{
	return angle_y * DEGREES_PER_RADIAN;
}


// Set the relative coordinates of the direction
void Direction::Set_X(const float x)
{
	Set_Coordinates(x, Get_Y(), Get_Z());
}

void Direction::Set_Y(const float y)
{
	Set_Coordinates(Get_X(), y, Get_Z());
}

void Direction::Set_Z(const float z)
{
	Set_Coordinates(Get_X(), Get_Y(), z);
}


// Set the distance and angles of the direction
void Direction::Set_Distance(const float in_distance)
{
	distance = in_distance;
}

void Direction::Set_X_Angle(const float in_angle_x)
{
	angle_x = fmod(in_angle_x / DEGREES_PER_RADIAN, 360.0 / DEGREES_PER_RADIAN);
	if (angle_x < 0)
	{
		angle_x += 360.0 / DEGREES_PER_RADIAN;
	}
}

void Direction::Set_Y_Angle(const float in_angle_y)
{
	angle_y = fmod(in_angle_y / DEGREES_PER_RADIAN, 360.0 / DEGREES_PER_RADIAN);
	if (angle_y < 0)
	{
		angle_y += 360.0 / DEGREES_PER_RADIAN;
	}
}


// Set the coordinates of the direction
void Direction::Set_Coordinates(const float x, const float y, const float z)
{
	Set_Direction(
		sqrt(x*x + y*y + z*z),
		atan2(x, z) * DEGREES_PER_RADIAN,
		atan2(y, sqrt(x*x + z*z)) * DEGREES_PER_RADIAN);
	return;
}


// Add values to the coordinates of the direction
void Direction::Add_Coordinates(const float x, const float y, const float z)
{
	Set_Coordinates(Get_X() + x, Get_Y() + y, Get_Z() + z);
	return;
}


// Set the distance and angles
void Direction::Set_Direction(const float in_distance, const float in_angle_x, const float in_angle_y)
{
	distance = in_distance;
	if (distance != 0)
	{
		angle_x = fmod(in_angle_x / DEGREES_PER_RADIAN, 360.0 / DEGREES_PER_RADIAN);
		if (angle_x < 0)
		{
			angle_x += 360.0 / DEGREES_PER_RADIAN;
		}
		angle_y = fmod(in_angle_y / DEGREES_PER_RADIAN, 360.0 / DEGREES_PER_RADIAN);
		if (angle_y < 0)
		{
			angle_y += 360.0 / DEGREES_PER_RADIAN;
		}
	}
	else
	{
	}
	return;
}


// Add values to the distance and angles
void Direction::Add_Direction(const float in_distance, const float in_angle_x, const float in_angle_y)
{
	Set_Direction(distance + in_distance,
		Get_X_Angle() + in_angle_x,
		Get_Y_Angle() + in_angle_y);
	return;
}


// Find the distance between this direction and another
Direction Direction::Distance(const Direction& to) const
{
	Direction copy = to;
	copy.Add_Coordinates(-1 * Get_X(), -1 * Get_Y(), -1 * Get_Z());
	return copy;
}


// Makes a vertex with the X, Y, and Z values
Vertex Direction::To_Vertex(void) const
{
	return Vertex(Get_X(), Get_Y(), Get_Z());
}
