#pragma once
#ifndef _UI_COLLECTION
#define _UI_COLLECTION

#include "UI_window.h"
#include "Globals.h"
#include <algorithm>

class UI_collection : public UI {
public:

	UI_collection(float x,float y,float t);
	~UI_collection();

	virtual void transparency(float t) override;
	virtual void render() override;

	void increaseWidth(float percent);
	void increaseHeight(float percent); 

	UI* object(std::string name);
	UI* object(int number);
	int objects();

	void addWithCustomName(std::string name, UI* ui);
	#define add(x) addWithCustomName(#x,x)

	virtual float width() override;
	virtual float height() override;
	virtual void destroy() override;

private:

	virtual void execute_event(UI_window* _window, const SDL_Event& _event);

	void renderRelative(UI* ui);

	UI_vectorRenderList* Collection_itemOrder;
	UI_mapRenderList* Collection_items;

	virtual void height(float h) override;
	virtual void width(float w) override;

};

#endif 