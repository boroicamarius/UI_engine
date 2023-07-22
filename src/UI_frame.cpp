#include "UI_engine/UI_frame.h"

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

UI_frame::~UI_frame() {};

SDL_Color UI_frame::color() {
	return *frameColor;
}

void UI_frame::color(SDL_Color c) {
	*frameColor = c;
}

void UI_frame::render() {
	SDL_SetRenderDrawColor(_renderer, frameColor->r, frameColor->g, frameColor->b, frameColor->a);
	renderMode[frameFilled](*_renderer, *this->interface);
};

void UI_frame::destroy() {
	finit();
	frameColor = NULL;
};

void UI_frame::transparency(float t) {
	frameColor->a = 255.0f * t;
	transparencyVal = t;
};

void UI_frame::fill() {
	frameFilled = true;
}

void UI_frame::unfill() {
	frameFilled = false;
}