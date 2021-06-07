#pragma once
#ifndef _UI_PANEL
#define _UI_PANEL

#include "../Globals/Globals.h"
#include <algorithm>

class UI_collection : public UI {
public:

	UI_collection(
		float x,
		float y,
		float t
	);
	~UI_collection();

	virtual void transparency(float t) override {
		for (auto& ui : *Collection_itemOrder) {
			ui->transparency(t);
		}

		transparencyVal = t;
	};

	virtual void render() override {
		for (auto& ui : *Collection_itemOrder) {
			if (ui->isVisible)
				renderRelative(ui);
		}
	};

	void increaseWidth(float percent);
	void increaseHeight(float percent); 

	UI* object(std::string name);

	UI* object(int number) {
		return (*Collection_itemOrder)[number];
	};

	int objects() {
		return (*Collection_itemOrder).size();
	};

	void addWithCustomName(std::string name, UI* ui) {
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
	#define add(x) addWithCustomName(#x,x)

	virtual float width() override {
		float maxWidth = 0.0f;

		for (auto& ui : *Collection_itemOrder) {
			maxWidth = std::max(maxWidth, ui->width() + ui->x());
		}
		return maxWidth;
	};

	virtual float height() override {
		float maxHeight = 0.0f;

		for (auto& ui : *Collection_itemOrder) {
			maxHeight = std::max(maxHeight, ui->height() + ui->y());
		}
		return maxHeight;
	};

	virtual void destroy() override {
		for (auto& ui : *Collection_itemOrder) {
			ui->destroy();
		}
		finit();
	};

private:

	virtual void execute_event(UI_window* _window, const SDL_Event& _event) {
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

	void renderRelative(UI* ui) {
		SDL_FRect* temp = new SDL_FRect(*ui->interface);

		*ui->interface = SDL_FRect(
			{ temp->x + getParentPosX(),
			 temp->y + getParentPosY(),
			 temp->w, temp->h });

		ui->render();

		*ui->interface = *temp;
	};

	UI_vectorRenderList* Collection_itemOrder;
	UI_mapRenderList* Collection_items;

	virtual void height(float h) override {
		float percent = (this->height()/100.0f) * h;

		for (auto& ui : *Collection_itemOrder) {
			ui->height((ui->height() / 100.0f) * percent), ui->y((ui->y() / 100.0f) * percent);
		}
	};
	virtual void width(float w) override {
		float percent = (this->width()/ 100.0f) * w;

		for (auto& ui : *Collection_itemOrder) {
			ui->width((ui->width() / 100.0f) * percent), ui->x((ui->x() / 100.0f) * percent);
		}
	};

};

#endif 