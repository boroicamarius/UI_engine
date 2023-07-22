#pragma once
#ifndef _UI_FRAME
#define _UI_FRAME

#include "UI.h"
#include "Globals.h"

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

	virtual void render() override;

	virtual void destroy() override;

	SDL_Color color();

	void color(SDL_Color c);

	virtual void transparency(float t) override;

	void fill();
	void unfill();

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