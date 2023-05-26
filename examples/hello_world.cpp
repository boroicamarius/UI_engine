#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_ttf.h"
#include "UI_engine.h"

using namespace UI_engine;

int main(int argc, char* argv[]) {
    UI_window window("exampleWindow",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        400, 400, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED,
        144.0);

    UI_frame frame_example(0.0f, 0.0f, 35.0f, 35.0f, 1.0f, { 0,0,0,255 });
    frame_example.filled();

    window.add(&frame_example);
    processEvents(&window);
    return 0;
}