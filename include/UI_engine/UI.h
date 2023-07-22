#pragma once

#ifndef _UI
#define _UI

#include <SDL.h>
#include <functional>

class UI {
public:

	UI();
	~UI();

	virtual float width();
	virtual void width(float w);

	virtual float height();
	virtual void height(float h);

	virtual float transparency();
	virtual void transparency(float t);

	virtual float x();
	virtual void x(float x);

	virtual float y();
	virtual void y(float y);

	virtual void show();
	virtual void hide();

	virtual void render();
	virtual void destroy();

	float getParentPosX();
	float getParentPosY();

	void toggleEvents();

protected:

	friend class UI_window;
	friend class UI_collection;

	virtual void execute_event(UI_window* _window,const SDL_Event& _event);

	void init();
	void finit();

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
		UI* obj;
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