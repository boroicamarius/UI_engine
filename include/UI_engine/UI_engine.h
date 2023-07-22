#pragma once
#ifndef UI_ENGINE
#define UI_ENGINE

#include <stdio.h>
#include <string>
#include "UI_window.h"
#include "UI_frame.h"
#include "UI_image.h"
#include "UI_text.h"
#include "UI_collection.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

namespace UI_engine {
	void test();
	void processEvents(UI_window* uiWindow);
}

#endif