#pragma once

#ifndef _UI_WINDOW
#define _UI_WINDOW

#define _to_string(x) #x

#include <SDL.h>
#include <SDL_ttf.h>
#include <functional>
#include <deque>

enum _status {
	active = 4,
	paused = 2,
	stopped = 0,
	undefined = -1
};

#include "Globals.h"

class UI_window {

	typedef std::deque<std::function<void(UI_window*)>> UI_EventList;

public:

	UI_window(
		std::string name,
		int x, int y,
		int w, int h,
		Uint32 windowFlags,
		Uint32 rendererFlags,
		double framerateCap
	);

	~UI_window() {};

	int width();
	void width(int w);

	int height();
	void height(int h);

	int x();
	void x(int x);

	int y();
	void y(int y);

	float transparency();
	void transparency(float t);

	SDL_Color background();
	void background(SDL_Color c);

	UI* object(std::string name);
	UI* object(int number);
	int objects();

	void addWithCustomName(std::string name, UI* ui);
	#define add(x) addWithCustomName(#x,x)

	void render();

	void status(_status to_set);
	_status status();

	void addEvent(std::function<void(UI_window*)> _event);
	void execute_sdlEvents(const SDL_Event& e);

	void stop();

	void update_framerate();
	void finish_framerate();
	double framerate();
	bool framerate_limit();
	double deltaTime();

private:
	unsigned int a = SDL_GetTicks();
	unsigned int b = SDL_GetTicks();
	double delta = 0.0;

	double _framerate = 0.0;
	double fpsCap;

	_status windowActivity = undefined;
	SDL_Rect* windowInterface;
	float transparencyVal = 0.0f;
	SDL_Color backgroundColor = { 255,255,255,255 };
	UI_EventList* events = NULL;
};

#endif
