#pragma once

#ifndef _UI
#define _UI

#include "SDL.h"
#include <functional>

class UI {
public:

	UI() { init(); };

	~UI() { finit(); };

	virtual float width() {
		return interface->w;
	};

	virtual void width(float w) {
		interface->w = w;
	};

	virtual float height() {
		return interface->h;
	};

	virtual void height(float h) {
		interface->h = h;
	};

	virtual float transparency() {
		return transparencyVal;
	};

	virtual void transparency(float t) {
		transparencyVal = t;
	};

	virtual float x() {
		return interface->x;
	};

	virtual void x(float x) {
		interface->x = x;
	};

	virtual float y() {
		return interface->y;
	};

	virtual void y(float y) {
		interface->y = y;
	};

	virtual void show() {
		isVisible = true;
	};

	virtual void hide() {
		isVisible = false;
	};

	virtual void render() {};

	virtual void destroy() {
		finit();
	};

	float getParentPosX() {
		float x = this->interface->x;
		if (parent != NULL)
			x += parent->getParentPosX();
		return x;
	};

	float getParentPosY() {
		float y = this->interface->y;
		if (parent != NULL)
			y += parent->getParentPosY();
		return y;
	};

	void toggleEvents() {
		getsEvents = !getsEvents;
	}

protected:

	friend class UI_window;
	friend class UI_collection;

	virtual void execute_event(UI_window* _window,const SDL_Event& _event) {
		if (this->getsEvents)
			switch (_event.type) {
			case SDL_MOUSEBUTTONDOWN:
				if (onMousePress)
					onMousePress({ _window, _event });
				break;
			case SDL_MOUSEBUTTONUP:
				if (onMouseRelease)
					onMouseRelease({ _window, _event });
				break;
			case SDL_MOUSEMOTION:
				if (onMouseMove)
					onMouseMove({ _window, _event });
				break;
			case SDL_MOUSEWHEEL:
				if (onScroll)
					onScroll({ _window, _event });
				break;
			case SDL_KEYDOWN:
				if(onKeyPress)
					onKeyPress({ _window, _event });
				break;
			case SDL_KEYUP:
				if (onKeyRelease)
					onKeyRelease({ _window, _event });
				break;
			default:
				break;
			};
	};

	void init() {
		interface = new SDL_FRect;
	}

	void finit() {
		interface = NULL;
	}

	bool used = false;
	bool isVisible = true;
	bool getsEvents = false;
	SDL_FRect* interface;
	float transparencyVal = 0.0f;
	UI* parent = NULL;

public:

	struct UI_eventData {
		UI_window* w;
		const SDL_Event& e;
	};

	typedef std::function<void(UI_eventData)> UI_event;

	UI_event onMousePress;
	UI_event onMouseRelease;
	UI_event onMouseMove;
	UI_event onKeyPress;
	UI_event onKeyRelease;
	UI_event onScroll;

};

#endif