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

#include "../Globals/Globals.h"

class UI_window {

	typedef std::deque<std::function<void(UI_window*)>> UI_EventList;

public:

	UI_window(
		std::string name,
		int x,int y,
		int w,int h,
		Uint32 windowFlags,
		Uint32 rendererFlags,
		double framerateCap
	) 
	{
		if (_window == NULL) {
			SDL_Init(SDL_INIT_EVERYTHING);
			TTF_Init();
			windowInterface = new SDL_Rect({ x,y,w,h });

			items = new UI_mapRenderList();
			itemOrder = new UI_vectorRenderList();
			events = new UI_EventList();

			_window = SDL_CreateWindow(name.c_str(), x, y, w, h, windowFlags);
			if (!_window)
				SDL_Log(SDL_GetError() + '\n');
			_renderer = SDL_CreateRenderer(_window, -1, rendererFlags);
			if (!_renderer)
				SDL_Log(SDL_GetError() + '\n');

			SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
			windowActivity = active;
			fpsCap = framerateCap;
		}
	};

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

	void addWithCustomName(std::string name,UI* ui) {
		if (!ui->used) {
			if (!std::isalpha(name[0])) {
				(*items)[name.substr(1, name.size() - 1)] = ui;
				(*itemOrder).push_back(ui);
			}
			else {
				(*items)[name] = ui;
				(*itemOrder).push_back(ui);
			}
			ui->used = true;
		}
	};

	#define add(x) addWithCustomName(#x,x)
	void render() {

		SDL_SetRenderDrawColor(_renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		SDL_RenderClear(_renderer);

		for (auto& ui : *itemOrder) {
			if (ui->isVisible)
				ui->render();
		}

		if (windowActivity == active) {
			int executions = events->size();

			for (; executions; --executions) {
				events->front()(this);
				events->pop_front();
			}

		}

		SDL_RenderPresent(_renderer);
	};

	void status(_status to_set) {
		windowActivity = to_set;
	};

	_status status() {
		return windowActivity;
	};

	void addEvent(std::function<void(UI_window*)> _event) {
		events->push_back(_event);
	};

	void stop() {

		for (auto& ui : *itemOrder) {
			if (ui->isVisible)
				ui->destroy();
		}

		SDL_Quit();
		TTF_Quit();

		windowActivity = stopped;
		events = NULL;
		items = NULL;
		itemOrder = NULL;
	};

	void execute_sdlEvents(const SDL_Event& e) {
		switch (e.type) {
		case SDL_WINDOWEVENT:
			switch (e.window.event) {
			case SDL_WINDOWEVENT_CLOSE:
				stop();
				break;
			}
			break;
		default:
			for (auto& ui : *itemOrder) {
				if (ui->getsEvents)
					ui->execute_event(this, e);
			}
			break;

		}
	}

	void update_framerate() {
		a = SDL_GetTicks();
		delta = a - b;
	};

	void finish_framerate() {
		b = a;
		_framerate = (1000 / delta);
	};

	double framerate() {
		return _framerate;
	};

	bool framerate_limit() {
		return (delta > (1000 / fpsCap));
	};

	double deltaTime() {
		return delta;
	};

private:
	// \for fps
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
