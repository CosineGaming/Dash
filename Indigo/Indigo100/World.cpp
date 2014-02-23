// Defines a class for holding objects

#include "World.h"
#include "Indigo.h"
#include <stdlib.h>
#include "glut.h"
#include <iostream>


// Create a new, empty world
World::World(void)
{
	objects = std::vector<Object>();
	texts = std::vector<Text>();
	lighting = Lighting();
	camera = Camera();
	return;
}


// Copy a world
World::World(const World& world)
{
	objects = world.objects;
	texts = world.texts;
	lighting = world.lighting;
	camera = world.camera;
	return;
}


// Deletes the world, opens memory
World::~World(void)
{
	return;
}


// Updates every object in the world, prepares to render again
void World::Update(const int& time)
{
	for (int Object_ID = 0; Object_ID<objects.size(); ++Object_ID)
	{
		if (objects[Object_ID].Update)
		{
			objects[Object_ID].Update(time, objects[Object_ID]);
		}
	}
	for (int Object_ID = 0; Object_ID<objects_2d.size(); ++Object_ID)
	{
		if (objects_2d[Object_ID].Update)
		{
			objects_2d[Object_ID].Update(time, objects_2d[Object_ID]);
		}
	}
	return;
}


// Renders every object in the world
void World::Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	Indigo::Reshape();
	camera.Look();
	lighting.Update_Lights();
	for (int Object_ID = 0; Object_ID<objects.size(); ++Object_ID)
	{
		objects[Object_ID].Render();
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-1 * Indigo::Aspect_Ratio, Indigo::Aspect_Ratio, -1, 1, -1, 1);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	for (int Object_ID = 0; Object_ID<objects_2d.size(); ++Object_ID)
	{
		objects_2d[Object_ID].Render();
	}
	for (int text = 0; text < texts.size(); ++text)
	{
		texts[text].Render();
	}
	glutSwapBuffers();
	return;
}


// Adds an object to the world to be rendered and updated, returns an object ID
int World::Add_Object(const Object& object)
{
	objects.push_back(object);
	int Object_ID = objects.size() - 1;
	objects[Object_ID].ID = Object_ID;
	return Object_ID;
}


// Gets an object based on an index. DO NOT attempt to store the reference after a push_back. Ever.
Object& World::Get_Object(const int& ID) const
{
	return const_cast <Object&>(objects[ID]);
}


// Removes an object from the world based on an object ID
void World::Remove_Object(const int& ID)
{
	objects[ID] = Object();
	return;
}


// Removes an object from the world based on object; gets ID automatically
void World::Remove_Object(const Object& object)
{
	objects[object.ID] = Object();
	return;
}


// Adds an object to the world to be rendered and updated, returns an object ID
int World::Add_2D_Object(const Object& object)
{
	objects_2d.push_back(object);
	int Object_ID = objects_2d.size() - 1;
	objects_2d[Object_ID].ID = Object_ID;
	return Object_ID;
}


// Gets an object based on an index. DO NOT attempt to store the reference after a push_back. Ever.
Object& World::Get_2D_Object(const int& ID) const
{
	return const_cast <Object&>(objects_2d[ID]);
}


// Removes an object from the world based on an object ID
void World::Remove_2D_Object(const int& ID)
{
	objects_2d[ID] = Object();
	return;
}


// Removes an object from the world based on object; gets ID automatically
void World::Remove_2D_Object(const Object& object)
{
	objects_2d[object.ID] = Object();
	return;
}


// Add text to the world to be rendered, returns no handle to the text
int World::Add_Text(const Text& text)
{
	texts.push_back(text);
	int Object_ID = texts.size() - 1;
	texts[Object_ID].ID = Object_ID;
	return Object_ID;
}


// Gets text based on an index. DO NOT attempt to store the reference after a push_back. Ever.
Text& World::Get_Text(const int& ID) const
{
	return const_cast <Text&>(texts[ID]);
}


// Removes text from the world based on an object ID
void World::Remove_Text(const int& ID)
{
	texts[ID] = Text();
}


// Removes text from the world based on text; gets ID automatically
void World::Remove_Text(const Text& text)
{
	texts[text.ID] = Text();
}


// Returns the number of objects in the world, simply objects.size()
int World::Number_Of_Objects(void)
{
	return objects.size();
}


// Returns the number of 2d objects in the world, simply objects_2d.size()
int World::Number_Of_2D_Objects(void)
{
	return objects_2d.size();
}


// Returns the number of texts in the world, simply texts.size()
int World::Number_Of_Texts(void)
{
	return texts.size();
}

// Checks whether any object collides with another object, each collision testing returns -1 if no collision or object id for first
int World::Collide(const Object& object, const float add_x, const float add_y, const float add_z)
{
	for (int Object = 0; Object < objects.size(); ++Object)
	{
		if (Object != object.ID && objects[Object].World_Collide)
		{
			if (objects[Object].Collide(object, add_x, add_y, add_z))
			{
				return Object;
				break;
			}
		}
	}
	return -1;
}


// Checks whether any object will ever be intersected by a direction
int World::Collide(const Direction& position, const Direction& direction)
{
	for (int Object = 0; Object < objects.size(); ++Object)
	{
		if (objects[Object].World_Collide && objects[Object].Collide(position, direction))
		{
			return Object;
		}
	}
	return -1;
}


// Checks whether a vertex is within any object
int World::Collide(const Vertex& vertex, const float add_x, const float add_y, const float add_z)
{
	for (int Object = 0; Object < objects.size(); ++Object)
	{
		if (objects[Object].World_Collide && objects[Object].Collide(vertex, add_x, add_y, add_z))
		{
			return Object;
		}
	}
	return -1;
}