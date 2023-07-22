#pragma once
#ifndef _UI_IMAGE
#define _UI_IMAGE

#include "UI.h"
#include "Globals.h"
#include <stdio.h>

class UI_image : public UI {
public:

	UI_image(float x,float y,float w,float h,float t);

	~UI_image();

	void source(SDL_Surface* _imageSurface);
	void source(SDL_Texture* _imageTexture);
	SDL_Texture* source();

	void setRenderSection(int x,int y, int w, int h);
	void setRenderSectionFull();
	SDL_Rect* getRenderSection();

	virtual void transparency(float t) override;

	virtual void render() override;
	virtual void destroy() override;

private:
	SDL_Texture *image;
	SDL_Rect* renderSection;
	bool textureCreatedByItself = false;
};

#endif