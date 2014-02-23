// Allows the world to be viewed from different points

#include "Camera.h"
#include <stdlib.h>
#include <iostream>
#include "glut.h"


Camera::Camera(float x, float y, float z, Direction direction, Direction above)
{
	// Create a new camera by a position and a direction
	Place(x, y, z);
	eye = direction;
	up = above;
	return;
}


Camera::Camera(const Camera& camera)
{
	// Create a camera based off another
	Place(camera.X, camera.Y, camera.Z);
	Look_At(camera.eye);
	up = camera.up;
}


Camera::~Camera(void)
{
	// Remove the camera and free memory
	return;
}


void Camera::Place(const float x, const float y, const float z)
{
	// Place the camera at a point
	X = x;
	Y = y;
	Z = z;
	return;
}


void Camera::Move(const float forward, const float side, const float up)
{
	// Move relative to the way it's pointing and where it is
	Direction direction = eye;
	direction.Set_Direction(forward, direction.Get_X_Angle(), 0.0);
	X += direction.Get_X();
	Y += direction.Get_Y();
	Z += direction.Get_Z();
	direction.Set_Direction(side, direction.Get_X_Angle() + 90.0, 0.0);
	X += direction.Get_X();
	Y += direction.Get_Y();
	Z += direction.Get_Z();
	direction.Set_Direction(up, direction.Get_X_Angle(), 90.0);
	X += direction.Get_X();
	Y += direction.Get_Y();
	Z += direction.Get_Z();
}


// Look in a direction
void Camera::Look_At(const Direction& direction)
{
	eye = direction.Distance(Direction::Coordinates(X, Y, Z));
	return;
}


// Look at a point
void Camera::Look_At(const float x, const float y, const float z)
{
	eye.Set_Coordinates(x - X, y - Y, z - Z);
	return;
}


// Look in a direction
void Camera::Look_Towards(const Direction& direction)
{
	eye = direction;
	return;
}


// Look at a point
void Camera::Look_Towards(const float x, const float y, const float z)
{
	eye.Set_Coordinates(x, y, z);
	return;
}


// Look at an object
void Camera::Watch(const Object& object, const Direction& relative_camera_position)
{
	Direction position = object.facing;
	position.Add_Direction(0.0, relative_camera_position.Get_X_Angle(), relative_camera_position.Get_Y_Angle());
	Place(position.Get_X() + object.X,
		position.Get_Y() + object.Y,
		position.Get_Z() + object.Z);
	eye.Set_Coordinates(object.X - X, object.Y - Y, object.Z - Z);
	return;
}


void Camera::Look(void) const
{
	// Look through the camera for this frame
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(X, Y, Z, X + eye.Get_X(), Y + eye.Get_Y(), Z + eye.Get_Z(),
		up.Get_X(), up.Get_Y(), up.Get_Z());
	return;
}