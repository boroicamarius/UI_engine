#include "UI_engine/UI_text.h"

UI_text::UI_text(
	float x,
	float y,
	float t,
	std::string text
)
{
	init();

	textColor = new SDL_Color({ 0,0,0,255 });
	textSize = 55;

	textFont = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", textSize);

	if (textFont == NULL)
		printf(SDL_GetError());
	
	SDL_Surface* textSurface = TTF_RenderText_Blended(textFont, text.c_str(), *textColor);
	textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);

	if (textSurface == NULL)
		printf(SDL_GetError());

	if (textTexture == NULL)
		printf(SDL_GetError());	

	interface->x = x;
	interface->y = y;
	interface->w = textSurface->w;
	interface->h = textSurface->h;

	transparencyVal = t;
	renderSection = NULL;
	transparency(transparencyVal);

	SDL_FreeSurface(textSurface);
	_text = text;
};

UI_text::~UI_text() {};

void UI_text::text(std::string text) {
	_text = text;
	SDL_Surface* textSurface = TTF_RenderText_Blended(textFont, text.c_str(), *textColor);
	SDL_DestroyTexture(textTexture);
	textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);

	interface->w = textSurface->w;
	interface->h = textSurface->h;
	transparency(transparencyVal);
	SDL_FreeSurface(textSurface);
};

std::string UI_text::text() {
	return _text;
};

void UI_text::setRenderSection(int x, int y, int w, int h) {
	if (renderSection == NULL)
		renderSection = new SDL_Rect({ x,y,w,h });
	else {
		renderSection->x = x;
		renderSection->y = y;
		renderSection->w = w;
		renderSection->h = h;
	}
};

void UI_text::setRenderSectionFull() {
	renderSection = NULL;
};

SDL_Rect* UI_text::getRenderSection() {
	return new SDL_Rect({0,0,(int)interface->w,(int)interface->h});
};

void UI_text::color(SDL_Color _color) {
	*textColor = _color;
	SDL_Surface* textSurface = TTF_RenderText_Blended(textFont, _text.c_str(), *textColor);
	textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);

	transparency(transparencyVal);
	SDL_FreeSurface(textSurface);
};

SDL_Color* UI_text::color() {
	return textColor;
};

void UI_text::font(const char* _path,int _size) {
	TTF_CloseFont(textFont);

	textFont = TTF_OpenFont(_path, _size);
	SDL_Surface* textSurface = TTF_RenderText_Blended(textFont, _text.c_str(), *textColor);
	textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);

	transparency(transparencyVal);
	SDL_FreeSurface(textSurface);
};

TTF_Font* UI_text::font() {
	return textFont;
};

SDL_Texture* UI_text::source() {
	return textTexture;
};

void UI_text::transparency(float t) {
	SDL_SetTextureAlphaMod(textTexture, 255.0f * t);
	transparencyVal = t;
}

void UI_text::render() {
	SDL_RenderCopyF(_renderer, textTexture, renderSection, interface);
};

void UI_text::destroy() {
	finit();
	TTF_CloseFont(textFont), textFont = NULL;
	SDL_DestroyTexture(textTexture);
	renderSection = NULL;
	_text = "";
	textSize = 0;
};