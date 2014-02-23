// Allows for customization of lighting

#include "Lighting.h"
#include <stdlib.h>
#include "glut.h"
#include <iostream>


Lighting::Lighting(void)
{
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	Set_Ambient(0.15);
	Number_Of_Lights = 0;
	return;
}


Lighting::Lighting(const Lighting& arrangement)
{
	Number_Of_Lights = arrangement.Get_Number_Of_Lights();
	for (int light = 0; light < Number_Of_Lights; ++light)
	{
		for (int i = 0; i < 4; ++i)
		{
			Light_Positions[light][i] = arrangement.Light_Positions[light][i];
		}
	}
	return;
}


Lighting::~Lighting(void)
{
	return;
}


void Lighting::Set_Ambient(float intensity)
{
	float ambient[] = {intensity, intensity, intensity, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	return;
}


void Lighting::Add_Light(float X, float Y, float Z, bool infinity,
	float diffuse, float specular, float * color_offset)
{
	int Light = Light_Values[Number_Of_Lights];
	float position_array[] = {X, Y, Z, 1.0 - (float) infinity};
	float diffuse_array [] = {diffuse, diffuse, diffuse, 1.0};
	float specular_array[] = {specular, specular, specular, 1.0};
	if (color_offset)
	{
		for (int Color = 0; Color<3; ++Color)
		{
			specular_array[Color] += color_offset[Color];
		}
	}
	Light_Positions[Number_Of_Lights][0] = position_array[0];
	Light_Positions[Number_Of_Lights][1] = position_array[1];
	Light_Positions[Number_Of_Lights][2] = position_array[2];
	Light_Positions[Number_Of_Lights][3] = position_array[3];
	glEnable(Light);
	for (int i=Number_Of_Lights+1; i<8; ++i)
	{
		glDisable(Light_Values[i]);
	}
	glLightfv(Light, GL_POSITION, position_array);
	glLightfv(Light, GL_DIFFUSE, diffuse_array);
	glLightfv(Light, GL_SPECULAR, specular_array);
	++Number_Of_Lights;
	return;
}


// Update the positions of all lights, and ensure they're enabled
void Lighting::Update_Lights(void) const
{
	for (int Light = 0; Light<Number_Of_Lights; ++Light)
	{
		glLightfv(Light_Values[Light], GL_POSITION, Light_Positions[Light]);
	}
}


int Lighting::Get_Number_Of_Lights(void) const
{
	return Number_Of_Lights;
}


const int Lighting::Light_Values[8] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3,
	GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};
