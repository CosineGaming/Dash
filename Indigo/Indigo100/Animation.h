// Animates variables steadily

#pragma once

#include <vector>
#include "Mesh.h"
#include "Object.h"


class Animation
{
public:
	// Create a new float animation to be animated each frame given a pointer, a final value, and a number of frames
	Animation(float * original, float finished, int frames);
	// Construct an animation based on tweening a shape
	Animation(Mesh * original, Mesh finished, int frames);
	// Construct an animation for tweening position of an object
	Animation(Object * original, float X, float Y, float Z, int frames);
	// Destroy an animation and remove it from the update list
	~Animation(void);
	// Update this one animation; called by static Update
	void Update_One(void);
	// Remove all animations and start anew for a new world or other purpose
	static void Clear(void);
	// Update each animation; called every frame by Indigo::Update
	static void Update(void);
private:
	// The variable to affect
	float * change;
	// What the variable's value should change by each frame
	float each;
	// Remaining frames until change has reached the final variable
	int remaining_frames;
	// Stores all animations to be updated
	static std::vector<Animation> animations;
};