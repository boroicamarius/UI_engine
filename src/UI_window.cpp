#include "UI_engine/UI_window.h"

UI_window::UI_window(
	std::string name,
	int x, int y,
	int w, int h,
	Uint32 windowFlags,
	Uint32 rendererFlags,
	double framerateCap
) {
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

UI* UI_window::object(int number) {
	return (*itemOrder)[number];
};

int UI_window::objects() {
	return (*itemOrder).size();
};

void UI_window::addWithCustomName(std::string name, UI* ui) {
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

void UI_window::render() {

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

void UI_window::status(_status to_set) {
	windowActivity = to_set;
};

_status UI_window::status() {
	return windowActivity;
};

void UI_window::addEvent(std::function<void(UI_window*)> _event) {
	events->push_back(_event);
};

void UI_window::stop() {
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

void UI_window::execute_sdlEvents(const SDL_Event& e) {
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

void UI_window::update_framerate() {
	a = SDL_GetTicks();
	delta = a - b;
};

void UI_window::finish_framerate() {
	b = a;
	_framerate = (1000 / delta);
};

double UI_window::framerate() {
	return _framerate;
};

bool UI_window::framerate_limit() {
	return (delta > (1000 / fpsCap));
};

double UI_window::deltaTime() {
	return delta;
};