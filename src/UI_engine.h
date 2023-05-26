#pragma once
#ifndef UI_ENGINE
#define UI_ENGINE

#include <stdio.h>
#include <string>
#include "UI_engine/UI_window/UI_window.h"
#include "UI_engine/UI/UI_frame.h"
#include "UI_engine/UI_image/UI_image.h"
#include "UI_engine/UI_text/UI_text.h"
#include "UI_engine/UI_collection/UI_collection.h"

namespace UI_engine {
	void test();
	void processEvents(UI_window* uiWindow);
}

#endif