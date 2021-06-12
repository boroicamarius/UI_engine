#pragma once
#ifndef _UI_IMAGE
#define _UI_IMAGE

#include "../UI/UI.h"
#include "../Globals/Globals.h"
#include <stdio.h>

class UI_image : public UI {
public:

	UI_image(
		float x,
		float y,
		float w,
		float h,
		float t
	);

	~UI_image();

	void source(SDL_Surface* _imageSurface);
	SDL_Texture* source();

	void setRenderSection(int x,int y, int w, int h);
	void setRenderSectionFull();
	SDL_Rect* getRenderSection();

	virtual void transparency(float t) override {
		SDL_SetTextureAlphaMod(image, 255.0f * t);
		transparencyVal = t;
	};

	virtual void render() override {
		SDL_RenderCopyF(_renderer, image, renderSection, interface);
	};

	virtual void destroy() override {
		finit();
		if(textureCreatedByItself)
			SDL_DestroyTexture(image);
		renderSection = NULL;
	};

private:
	SDL_Texture *image;
	SDL_Rect* renderSection;
	bool textureCreatedByItself = false;
};

#endif