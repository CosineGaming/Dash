// Animates variables steadily

#include "Animation.h"
#include <iostream>


// Create a new, blank animation to be assigned to
Animation::Animation(float * original, float finished, int frames)
{
	change = original;
	each = (finished - *original) / frames;
	remaining_frames = frames;
	animations.push_back(*this);
}


// Construct an animation based on tweening a shape
Animation::Animation(Mesh * original, Mesh finished, int frames)
{
	for (int point = 0; point < original->Size(); ++point)
	{
		Animation(&((*original)[point].X), finished[point].X, frames);
		Animation(&((*original)[point].Y), finished[point].Y, frames);
		Animation(&((*original)[point].Z), finished[point].Z, frames);
	}
}


// Construct an animation for tweening position of an object
Animation::Animation(Object * original, float X, float Y, float Z, int frames)
{
	Animation(&(original->X), X, frames);
	Animation(&(original->Y), Y, frames);
	Animation(&(original->Z), Z, frames);
}


// Destroy an animation and remove it from the update list
Animation::~Animation(void)
{
}


// Update all animations; once per frame called by Indigo::Update
void Animation::Update_One(void)
{
	if (remaining_frames != 0)
	{
		*change += each;
		remaining_frames--;
	}
}


// Remove all animations and start anew for a new world or other purpose
void Animation::Clear(void)
{
	animations.clear();
}


// Update each animation; called every frame by Indigo::Update
void Animation::Update(void)
{
	for (int animation = 0; animation < animations.size(); ++animation)
	{
		animations[animation].Update_One();
	}
}


// Stores all animations to be updated
std::vector<Animation> Animation::animations;