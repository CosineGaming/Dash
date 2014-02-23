// Allows the world to be viewed from different points

#pragma once

#include "Object.h"
#include "Direction.h"


class Camera
{
public:
	// Create a new camera by a position and a direction
	Camera(const float x = 0.0, const float y = 0.0, const float z = 0.0,
		Direction direction=Direction(1.0),
		Direction above=Direction(1.0, 0.0, 90.0));
	// Create a camera based off another
	Camera(const Camera& camera);
	// Remove the camera and free memory
	~Camera(void);
	// Place the camera at a point
	void Place(const float x, const float y, const float z);
	// Move relative to the way it's pointing and where it is
	void Move(const float foward, const float side = 0.0, const float up = 0.0);
	// Look in a direction
	void Look_At(const Direction& direction);
	// Look at a point
	void Look_At(const float x, const float y, const float z);
	// Look in a direction relative to the camera
	void Look_Towards(const Direction& direction);
	// Look at a point relative to the camera
	void Look_Towards(const float x, const float y, const float z);
	// Look at an object
	void Watch(const Object& object, const Direction& direction);
	// Look through the camera for this frame
	void Look(void) const;
	// Should be private, but copying.
	Direction up;
	float X;
	float Y;
	float Z;
	Direction eye;
private:
};