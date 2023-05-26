#pragma once
#ifndef _UI_FRAME
#define _UI_FRAME

#include "UI.h"
#include "../Globals/Globals.h"

class UI_frame : public UI {
public:

	UI_frame(
		float x,
		float y,
		float w,
		float h,
		float t,
		SDL_Color color
	);

	~UI_frame();

	virtual void render() override {
		SDL_SetRenderDrawColor(_renderer, frameColor->r, frameColor->g, frameColor->b, frameColor->a);
		renderMode[frameFilled](*_renderer, *this->interface);
	};

	virtual void destroy() override {
		finit();
		frameColor = NULL;
	};

	SDL_Color color();

	void color(SDL_Color c);

	virtual void transparency(float t) override {
		frameColor->a = 255.0f * t;
		transparencyVal = t;
	};

	void filled() {
		frameFilled = true;
	}

	void unfilled() {
		frameFilled = false;
	}

private:

	SDL_Color* frameColor;
	
	bool frameFilled = true;

	void(*renderMode[2])(SDL_Renderer&, const SDL_FRect&) = {
		[](SDL_Renderer& u_renderer,const SDL_FRect& u_rect) {
			SDL_RenderDrawRectF(&u_renderer, &u_rect);
		},
		[](SDL_Renderer& u_renderer,const SDL_FRect& u_rect) {
			SDL_RenderFillRectF(&u_renderer, &u_rect);
		}
	};
};

#endif