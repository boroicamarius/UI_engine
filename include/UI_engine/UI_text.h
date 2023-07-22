#ifndef _UI_TEXT
#define _UI_TEXT

#include <SDL_ttf.h>
#include "Globals.h"

class UI_text : public UI {
public:
	UI_text(
		float x,
		float y,
		float t,
		std::string text
	);

	~UI_text();

	void text(std::string text);
	std::string text();

	void setRenderSection(int x, int y, int w, int h);
	void setRenderSectionFull();

	SDL_Rect* getRenderSection();

	void color(SDL_Color _color);
	SDL_Color* color();

	void font(const char* _path, int _size);
	TTF_Font* font();

	SDL_Texture* source();

	virtual void transparency(float t);

	virtual void render() override;
	virtual void destroy() override;

private:
	SDL_Texture* textTexture;
	TTF_Font* textFont;
	SDL_Rect* renderSection;
	std::string _text;
	int textSize;
	SDL_Color* textColor;
};

#endif 