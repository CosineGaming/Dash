#pragma once
#include <cstdlib>
#include "glut.h"


class Text
{
public:
	// Create new text based off of the text. -1 is bottom, 1 is top. If frames_to_last is negative, text won't disappear.
	Text(const float x=0, const float y=0, char * display="", float * color = nullptr, void * font = GLUT_BITMAP_HELVETICA_18, const int frames_to_last = -1, void(*finished)(void)=nullptr);
	// Create new Text based off of another Text object
	Text(const Text& copy);
	// Destroy the text
	~Text();
	// Render the text, returns true if text should be deleted
	void Render(void);
	// The ID the world uses
	int ID;
protected:
	// The text itself
	char * text;
	// The typeset to use
	void * typeset;
	// The frames until the text should go away
	int last;
	// The position of the text in actual pixels
	float X;
	float Y;
	// The color of the text
	float * text_color;
	// The function to call when the text goes away
	void(*done)(void);
};
