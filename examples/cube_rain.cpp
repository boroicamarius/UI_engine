#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_ttf.h"
#include "UI_engine.h"

#include<thread>
#include<cstdlib>
#include<vector>

using namespace UI_engine;

bool END = false;

void move_cube(std::vector<UI_frame> v) {
	while (END == false) {
		for(auto& cube: v){
			cube.x(rand() % 1000);
			cube.y(rand() % 1000);
		}
	}
}

int main(int argc, char* argv[]) {

	UI_window window("exampleWindow",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		400, 400, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED,
		144.0);

	std::vector<UI_frame> cubes;
	for (int i = 0; i < 100; ++i) {
		UI_frame* frame =  new UI_frame(0.0f, 0.0f, 35.0f, 35.0f, 1.0f, { 0,0,0,255 });
		frame->filled();
		cubes.push_back(*frame);
		window.add(frame);
	}
	

	std::thread random(move_cube,cubes);
	processEvents(&window);
	END = true,random.join();
	return 0;
}