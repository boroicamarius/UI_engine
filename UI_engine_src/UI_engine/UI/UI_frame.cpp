#include "UI_frame.h"

UI_frame::UI_frame(float x, float y, float w, float h, float t,SDL_Color c) {

	init();

	interface->x = x;
	interface->y = y;
	interface->w = w;
	interface->h = h;

	transparencyVal = t;

	frameColor = new SDL_Color(c);
	transparency(t);

};

UI_frame::~UI_frame() {

};

SDL_Color UI_frame::color() {
	return *frameColor;
}

void UI_frame::color(SDL_Color c) {
	*frameColor = c;
}
