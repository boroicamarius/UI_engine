# UI_engine
A simple to use engine for 2D user interface elements

# Documentation
[UI_engine Documentation](https://github.com/boroicamarius/UI_engine/tree/main#ui_engine-hello-world-example)

[Example](https://github.com/boroicamarius/UI_engine/tree/main#ui_engine-hello-world-example)
# How-to-setup a UI_engine project
[configuration](https://github.com/boroicamarius/UI_engine/tree/main#ui_engine-static-lib-configurationall-configurations)

# UI_engine hello world example
```cpp
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
```

## UI_engine Static Lib configuration(All configurations)
### configuration type: static library;

### Librarian>Additional Library Directories:
	path\to\SDL2_ttf\include
	path\to\SDL2_image\include
	path\to\SDL2\include

### Librarian>Additional Dependencies:
	SDL2.lib
	SDL2main.lib
	SDL2_image.lib
	SDL2_ttf.lib
		
		
## Main project configuration(All configurations)
same as the UI_engine configuration except

### C/C++>Additional Include Directories:
	path\to\UI_engine\(file that has every header/cpp file)

### C/C++>Precompiled Headers:Not Using Precompiled headers

### Linker>Additional Library Directories:
	path\to\SDL2_image\lib\x64
	path\to\SDL2_ttf\lib\x64
	path\to\SDL2\lib\x64
		
## final step
right click on the main solution project, add>reference and select UI_engine

And You're done!

have fun messing with it =)
