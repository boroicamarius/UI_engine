#include "UI_engine.h"
#include "UI_engine/Globals/Globals.h"

#include <iostream>

namespace UI_engine {
	void test() {
		printf("Working!\n");
	}

	void processEvents(UI_window* uiWindow) {

		SDL_Event _event;

		while (uiWindow->status()!=stopped) {
			uiWindow->update_framerate();

			if (uiWindow->framerate_limit())
			{
				uiWindow->finish_framerate();

				while (SDL_PollEvent(&_event)) {

					uiWindow->execute_sdlEvents(_event);

				}

				uiWindow->render();

			}

		}
	};
}