#include "UI_engine/UI_image.h"
#include "UI_engine/Globals.h"

#include <stdio.h>

UI_image::UI_image(
	float x,
	float y,
	float w,
	float h,
	float t
) {
	init();

	interface->x = x;
	interface->y = y;
	interface->w = w;
	interface->h = h;

	renderSection = new SDL_Rect({ (int)interface->x,(int)interface->y,(int)interface->w ,(int)interface->h });

	transparencyVal = t;
};

UI_image::~UI_image() {};

void UI_image::source(SDL_Surface* _imageSurface) {
	if (this->textureCreatedByItself) {
		SDL_DestroyTexture(image);
		textureCreatedByItself = true;
	}

	image = SDL_CreateTextureFromSurface(_renderer, _imageSurface);
	if (image == NULL)
		printf(SDL_GetError());

	transparency(transparencyVal);
};

void UI_image::source(SDL_Texture* _imageTexture) {
	if (this->textureCreatedByItself) {
		SDL_DestroyTexture(image);
		textureCreatedByItself = true;
	}

	image = _imageTexture;
	if (image == NULL)
		printf(SDL_GetError());

	transparency(transparencyVal);
}

SDL_Texture* UI_image::source() {
	return image;
};

void UI_image::setRenderSection(int x, int y, int w, int h) {
	if (renderSection == NULL)
		renderSection = new SDL_Rect({ x,y,w,h });
	else {
		renderSection->x = x;
		renderSection->y = y;
		renderSection->w = w;
		renderSection->h = h;
	}
};

void UI_image::setRenderSectionFull() {
	renderSection = NULL;
};

SDL_Rect* UI_image::getRenderSection() {
	return new SDL_Rect({ 0,0,(int)interface->w,(int)interface->h });
};

void UI_image::transparency(float t) {
	SDL_SetTextureAlphaMod(image, 255.0f * t);
	transparencyVal = t;
};

void UI_image::render() {
	if (image == NULL) return;
	SDL_RenderCopyF(_renderer, image, renderSection, interface);
};

void UI_image::destroy() {
	finit();
	if (textureCreatedByItself)
		SDL_DestroyTexture(image);
	renderSection = NULL;
};