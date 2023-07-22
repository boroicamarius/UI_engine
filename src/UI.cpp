#include<UI_engine/UI.h>
#include<UI_engine/UI_window.h>

UI::UI() { init(); }

UI::~UI() { finit(); }

float UI::width() { return interface->w; }
void UI::width(float w) { interface->w = w; }

float UI::height() { return interface->h; }
void UI::height(float h) { interface->h = h; }

float UI::transparency() { return transparencyVal; }
void UI::transparency(float t) { transparencyVal = t; }

float UI::x() { return interface->x; }
void UI::x(float x) { interface->x = x; }

float UI::y() { return interface->y; }
void UI::y(float y) { interface->y = y; }

void UI::show() { isVisible = true; }
void UI::hide() { isVisible = false; }

void UI::render() {}
void UI::destroy() { finit(); }

float UI::getParentPosX() {
	float x = this->interface->x;
	if (parent != NULL)
		x += parent->getParentPosX();
	return x;
}

float UI::getParentPosY() {
	float y = this->interface->y;
	if (parent != NULL)
		y += parent->getParentPosY();
	return y;
}

void UI::toggleEvents() {
	getsEvents = !getsEvents;
}

void UI::execute_event(UI_window* _window, const SDL_Event& _event) {
	if (this->getsEvents)
		switch (_event.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (onMousePress)
				onMousePress({ _window, _event, this });
			break;
		case SDL_MOUSEBUTTONUP:
			if (onMouseRelease)
				onMouseRelease({ _window, _event, this });
			break;
		case SDL_MOUSEMOTION:
			if (onMouseMove)
				onMouseMove({ _window, _event, this });
			break;
		case SDL_MOUSEWHEEL:
			if (onScroll)
				onScroll({ _window, _event, this });
			break;
		case SDL_KEYDOWN:
			if (onKeyPress)
				onKeyPress({ _window, _event, this });
			break;
		case SDL_KEYUP:
			if (onKeyRelease)
				onKeyRelease({ _window, _event, this });
			break;
		default:
			break;
		};
}

void UI::init() {
	interface = new SDL_FRect;
}

void UI::finit() {
	interface = NULL;
}