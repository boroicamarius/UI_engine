#include "UI_window.h"

int UI_window::width() {
	return windowInterface->w;
};
void UI_window::width(int w) {
	windowInterface->w = w;
	SDL_SetWindowSize(_window,w, windowInterface->h);
};

int UI_window::height() {
	return windowInterface->h;
};
void UI_window::height(int h) {
	windowInterface->h = h;
	SDL_SetWindowSize(_window, windowInterface->w, h);
};

int UI_window::x() {
	SDL_GetWindowPosition(_window, &windowInterface->x, &windowInterface->y);
	return windowInterface->x;
};
void UI_window::x(int x) {
	windowInterface->x = x;
	SDL_SetWindowPosition(_window, x, windowInterface->y);
};

int UI_window::y() {
	SDL_GetWindowPosition(_window, &windowInterface->x, &windowInterface->y);
	return windowInterface->y;
};
void UI_window::y(int y) {
	windowInterface->y = y;
	SDL_SetWindowPosition(_window, windowInterface->x, y);
};

float UI_window::transparency() {
	return transparencyVal;
};
void UI_window::transparency(float t) {
	SDL_SetWindowOpacity(_window, t);
	transparencyVal = t;
};

SDL_Color UI_window::background() {
	return backgroundColor;
};
void UI_window::background(SDL_Color c) {
	backgroundColor = c;
};

UI* UI_window::object(std::string name) {
	return (*items)[name];
};

int UI_window::objects() {
	return (*itemOrder).size();
};