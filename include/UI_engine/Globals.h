#pragma once
#ifndef _GLOBALS_
#define _GLOBALS_

#include "UI.h"
#include <map>
#include <vector>
#include <string>

typedef std::map<std::string, UI*> UI_mapRenderList;
typedef std::vector<UI*> UI_vectorRenderList;

extern UI_mapRenderList* items;
extern UI_vectorRenderList* itemOrder;
extern SDL_Window* _window;
extern SDL_Renderer* _renderer;

#endif
