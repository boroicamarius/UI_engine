#include "UI_engine/UI_collection.h"

UI_collection::UI_collection(float x, float y, float t) 
{
	init();

	Collection_itemOrder = new UI_vectorRenderList();
	Collection_items = new UI_mapRenderList();

	interface->x = x;
	interface->y = y;
	transparency(t);
};
UI_collection::~UI_collection() {};

void UI_collection::increaseWidth(float percent) {
	for (auto& ui : *Collection_itemOrder) {
		ui->width((ui->width()/100.0f)*percent), ui->x((ui->x() / 100.0f) * percent);
	}
};

void UI_collection::increaseHeight(float percent) {
	for (auto& ui : *Collection_itemOrder) {
		ui->height((ui->height() / 100.0f) * percent), ui->y((ui->y() / 100.0f) * percent);
	}
};

UI* UI_collection::object(std::string name) {
	return (*Collection_items)[name];
}

UI* UI_collection::object(int number) {
	return (*Collection_itemOrder)[number];
};

int UI_collection::objects() {
	return (*Collection_itemOrder).size();
};

void UI_collection::transparency(float t){
	for (auto& ui : *Collection_itemOrder) {
		ui->transparency(t);
	}
	transparencyVal = t;
}

void UI_collection::render(){
	for (auto& ui : *Collection_itemOrder) {
		if (ui->isVisible)
			renderRelative(ui);
	}
}

void UI_collection::addWithCustomName(std::string name, UI* ui) {
	if (!ui->used) {
		ui->parent = this;
		if (!std::isalpha(name[0])) {
			(*Collection_items)[name.substr(1, name.size() - 1)] = ui;
			(*Collection_itemOrder).push_back(ui);
		}
		else {
			(*Collection_items)[name] = ui;
			(*Collection_itemOrder).push_back(ui);
		}
		ui->transparency(transparencyVal);
		ui->used = true;
	}
};

float UI_collection::width() {
	float minX = 9999999.0f;
	float maxWidth = 0.0f;

	for (auto& ui : *Collection_itemOrder) {
		maxWidth = std::max(maxWidth, ui->width() + ui->x());
		minX = std::min(minX, ui->x());
	}

	switch ((int)minX) {
	case 9999999:
		return 0.0f;
		break;
	default:
		return abs(minX) + maxWidth;
	}
};

float UI_collection::height() {
	float minY = 9999999.0f;
	float maxHeight = 0.0f;

	for (auto& ui : *Collection_itemOrder) {
		maxHeight = std::max(maxHeight, ui->height() + ui->y());
		minY = std::min(minY, ui->y());
	}

	switch ((int)minY) {
	case 9999999:
		return 0.0f;
		break;
	default:
		return abs(minY) + maxHeight;
	}
};

void UI_collection::destroy() {
	for (auto& ui : *Collection_itemOrder) {
		ui->destroy();
	}
	finit();
};

void UI_collection::execute_event(UI_window* _window, const SDL_Event& _event) {
	if (this->getsEvents) {
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
			if (onKeyPress)
				onKeyPress({ _window, _event });
			break;
		case SDL_KEYUP:
			if (onKeyRelease)
				onKeyRelease({ _window, _event });
			break;
		default:
			break;
		};

		for (auto& ui : *Collection_itemOrder) {
			ui->execute_event(_window, _event);
		}
	}
};

void UI_collection::renderRelative(UI* ui) {
	SDL_FRect* temp = new SDL_FRect(*ui->interface);

	*ui->interface = SDL_FRect(
		{ temp->x + getParentPosX(),
		 temp->y + getParentPosY(),
		 temp->w, temp->h });

	ui->render();

	*ui->interface = *temp;
};

void UI_collection::height(float h) {
	float percent = (this->height() / 100.0f) * h;

	for (auto& ui : *Collection_itemOrder) {
		ui->height((ui->height() / 100.0f) * percent), ui->y((ui->y() / 100.0f) * percent);
	}
};

void UI_collection::width(float w) {
	float percent = (this->width() / 100.0f) * w;

	for (auto& ui : *Collection_itemOrder) {
		ui->width((ui->width() / 100.0f) * percent), ui->x((ui->x() / 100.0f) * percent);
	}
};