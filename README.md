# ![UI_engine](https://github.com/boroicamarius/UI_engine/blob/main/docs/logo_git.png)
## Introducere
UI_engine este o bibliotecă statică C++ care permite dezvoltatorilor să creeze interfețe utilizator din codul C++ folosind SDL (Simple DirectMedia Layer). Această documentație vă va ghida prin configurarea bibliotecii, crearea unui proiect simplu și înțelegerea diferitelor componente ale codului.

## Cuprins

1. [Configurarea UI_engine](#configurarea-ui_engine)
2. [Crearea unui Proiect Simplu](#crearea-unui-proiect-simplu)
3. [Componentele UI_engine](#componentele-ui_engine)
   - [UI](#ui)
   - [UI_collection](#ui_collection)
   - [UI_frame](#ui_frame)
   - [UI_image](#ui_image)
   - [UI_text](#ui_text)
   - [UI_window](#ui_window)
   - [Globals](#globals)
   - [UI_engine](#ui_engine)
4. [Concluzie](#concluzie)

---

## Configurarea UI_engine

Pentru a începe cu UI_engine, urmați acești pași:

1. Creați un director de proiect nou și navigați la acesta folosind terminalul sau linia de comandă.
2. Clonați depozitul UI_engine de pe GitHub folosind următoarea comandă:

```bash
git clone https://github.com/boroicamarius/UI_engine.git
```

3. Creați un fișier CMakeLists.txt în directorul rădăcină al proiectului cu următorul conținut:

```cmake
cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
            
project(app)
            
add_subdirectory(UI_engine)
            
add_executable(runnable main.cpp)
target_link_libraries(runnable PUBLIC UI_engine)
```

4. Creați un fișier main.cpp în directorul proiectului cu elementele UI dorite și codul de gestionare a evenimentelor. Pentru un exemplu de bază, consultați [Crearea unui Proiect Simplu](#crearea-unui-proiect-simplu).

---

## Crearea unui Proiect Simplu

Hai să creăm un proiect simplu care afișează o fereastră cu o ramă neagră folosind UI_engine. Iată fișierul main.cpp:

```cpp
#include <UI_engine/UI_engine.h>
using namespace UI_engine;

int main(int argc, char* argv[]) {
  UI_window window("exampleWindow",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    400, 400, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED,
    144.0);
    
  UI_frame frame_example(0.0f, 0.0f, 35.0f, 35.0f, 1.0f, { 0,0,0,255 });
  frame_example.fill();
  
  window.add(&frame_example);
  processEvents(&window);
  return 0;
}
```

Acest cod creează o fereastră intitulată "exampleWindow" cu o ramă neagră la colțul din stânga sus.

---

## Componentele UI_engine

### UI

Clasa UI este clasa de bază pentru toate elementele UI. Aceasta oferă funcționalități comune precum poziționarea, dimensiunea, transparența și gestionarea evenimentelor.

#### `class UI`

Clasa `UI` reprezintă un element de bază pentru interfața utilizator care poate fi afișat și manipulat într-o fereastră.

##### `UI()`

Constructorul inițializează elementul UI.

##### `~UI()`

Destructorul curăță elementul UI.

##### `float width()`

Returnează lățimea elementului UI.

##### `void width(float w)`

Setează lățimea elementului UI.

##### `float height()`

Returnează înălțimea elementului UI.

##### `void height(float h)`

Setează înălțimea elementului UI.

##### `float transparency()`

Returnează valoarea de transparență a elementului UI.

##### `void transparency(float t)`

Setează valoarea de transparență a elementului UI.

##### `float x()`

Returnează coordonata X a elementului UI.

##### `void x(float x)`

Setează

 coordonata X a elementului UI.

##### `float y()`

Returnează coordonata Y a elementului UI.

##### `void y(float y)`

Setează coordonata Y a elementului UI.

##### `void show()`

Face elementul UI vizibil.

##### `void hide()`

Ascunde elementul UI.

##### `void render()`

Randare elementului UI.

##### `void destroy()`

Distruge elementul UI și curăță resursele alocate.

##### `float getParentPosX()`

Returnează coordonata X absolută a elementului UI în cadrul părintelui său.

##### `float getParentPosY()`

Returnează coordonata Y absolută a elementului UI în cadrul părintelui său.

##### `void toggleEvents()`

Comută primirea evenimentelor de la elementul UI (de ex. clicuri de mouse, apăsări de taste).

##### `void execute_event(UI_window* _window, const SDL_Event& _event)`

Execută gestionarea evenimentelor pentru elementul UI.

##### `void init()`

Inițializează elementul UI.

##### `void finit()`

Curăță resursele utilizate de elementul UI.

```cpp
class UI {
public:
  UI();
  virtual ~UI();
  
  float width();
  void width(float w);
  
  float height();
  void height(float h);
  
  float transparency();
  void transparency(float t);
  
  float x();
  void x(float x);
  
  float y();
  void y(float y);
  
  void show();
  void hide();
  
  void render();
  void destroy();
  
  float getParentPosX();
  float getParentPosY();
  
  void toggleEvents();
  void execute_event(UI_window* _window, const SDL_Event& _event);
  
  void init();
  void finit();
};
```

### UI_collection

Clasa UI_collection vă permite să grupați mai multe elemente UI într-o singură unitate. Ajută la gestionarea poziționării și randării elementelor grupate.

####

 `class UI_collection : public UI`

Clasa `UI_collection` reprezintă un container pentru gruparea mai multor elemente UI.

##### `UI_collection(float x, float y, float t)`

Constructorul creează o nouă colecție UI cu poziția și transparența specificate.

##### `~UI_collection()`

Destructorul curăță colecția UI.

##### `void increaseWidth(float percent)`

Crește lățimea tuturor elementelor UI din colecție cu un procentaj.

##### `void increaseHeight(float percent)`

Crește înălțimea tuturor elementelor UI din colecție cu un procentaj.

##### `UI* object(std::string name)`

Returnează un pointer către un element UI din colecție cu numele personalizat dat.

##### `UI* object(int number)`

Returnează un pointer către un element UI din colecție în funcție de poziția sa.

##### `int objects()`

Returnează numărul de elemente UI din colecție.

##### `void addWithCustomName(std::string name, UI* ui)`

Adaugă un element UI la colecție cu un nume personalizat.

##### `float width()`

Returnează lățimea colecției UI.

##### `float height()`

Returnează înălțimea colecției UI.

##### `void destroy()`

Distruge colecția UI și toate elementele sale UI.

##### `void execute_event(UI_window* _window, const SDL_Event& _event)`

Execută gestionarea evenimentelor pentru colecția UI.

##### `void renderRelative(UI* ui)`

Randare unui element UI relativ la poziția sa în cadrul colecției.

##### `void height(float h)`

Setează înălțimea colecției UI.

##### `void width(float w)`

Setează lățimea colecției UI.

```cpp
class UI_collection : public UI {
public:
  UI_collection(float x, float y, float t);
  ~UI_collection();
  
  void increaseWidth(float percent);
  void increaseHeight(float percent);
  
  UI* object(std::string name);
  UI* object(int number);
  
  int objects();
  
  void addWithCustomName(std::string name, UI* ui);
  
  float width();
  float height();
  
  void destroy();
  
  void execute_event(UI_window* _window, const SDL_Event& _event);
  void renderRelative(UI* ui);
  
  void height(float h);
  void width(float w);
};
```

### UI_frame

Clasa UI_frame reprezintă o ramă simplă cu capacități opționale de umplere. Poate fi utilizată pentru a desena dreptunghiuri cu diferite culori.

#### `class UI_frame : public UI`

Clasa `UI_frame` reprezintă o

 ramă sau chenar pentru un element UI.

##### `UI_frame(float x, float y, float w, float h, float t, SDL_Color color)`

Constructorul creează o nouă ramă UI cu poziția, dimensiunele, transparența și culoarea specificate.

##### `~UI_frame()`

Destructorul curăță rama UI.

##### `SDL_Color color()`

Returnează culoarea ramei UI.

##### `void color(SDL_Color c)`

Setează culoarea ramei UI.

##### `void render()`

Randare ramei UI.

##### `void destroy()`

Distruge rama UI și curăță resursele alocate.

##### `void transparency(float t)`

Setează valoarea de transparență a ramei UI.

##### `void fill()`

Umple rama UI cu culoarea sa.

##### `void unfill()`

Elimină umplutura ramei UI.

```cpp
class UI_frame : public UI {
public:
  UI_frame(float x, float y, float w, float h, float t, SDL_Color color);
  ~UI_frame();
  
  SDL_Color color();
  void color(SDL_Color c);
  
  void render();
  void destroy();
  
  void transparency(float t);
  void fill();
  void unfill();
};
```

### UI_image

Clasa UI_image vă permite să afișați imagini pe UI. Suportă SDL_Texture și SDL_Surface ca surse de imagini.

#### `class UI_image : public UI`

Clasa `UI_image` reprezintă un element de interfață utilizator pentru imagini.

##### `UI_image(float x, float y, float w, float h, float t)`

Constructorul creează o nouă imagine UI cu poziția, dimensiunile și transparența specificate.

##### `~UI_image()`

Destructorul curăță imaginea UI.

##### `void source(SDL_Surface* _imageSurface)`

Setează sursa imaginii pentru imaginea UI dintr-un SDL_Surface.

##### `void source(SDL_Texture* _imageTexture)`

Setează sursa imaginii pentru imaginea UI dintr-un SDL_Texture.

##### `SDL_Texture* source()`

Returnează sursa imaginii pentru imaginea UI.

##### `void setRenderSection(int x, int y, int w, int h)`

Setează secțiunea imaginii de randat.

##### `void render()`

Randare imagine UI.

##### `void destroy()`

Distruge imaginea UI și curăță resursele alocate.

```cpp
class UI_image : public UI {
public:
  UI_image(float x, float y, float w, float h, float t);
  ~UI_image();
  
  void source(SDL_Surface* _imageSurface);
  void source(SDL_Texture* _imageTexture);
  SDL_Texture* source();
  
  void setRenderSection(int x, int y, int w, int h);
  
  void render();
  void destroy();
};
```

### UI_text

Clasa UI_text este utilizată pentru afișarea de texte pe UI. Puteți seta fontul, dimensiunea și culoarea textului.

#### `class UI_text : public UI`

Clasa `UI_text` reprezintă un element de interfață utilizator pentru text.

##### `UI_text(float x, float y, float w, float h, float t)`

Constructorul creează un nou element UI pentru text cu poziția, dimensiunile și transparența specificate.

##### `~UI_text()`

Destructorul curăță elementul UI pentru text.

##### `void font(std::string path)`

Setează fișierul fontului pentru elementul UI pentru text.

##### `void fontSize(int size)`

Setează dimensiunea fontului pentru elementul UI pentru text.

##### `void color(SDL_Color c)`

Setează culo

area elementului UI pentru text.

##### `void text(std::string content)`

Setează conținutul textului pentru elementul UI pentru text.

##### `void render()`

Randare element UI pentru text.

##### `void destroy()`

Distruge elementul UI pentru text și curăță resursele alocate.

```cpp
class UI_text : public UI {
public:
  UI_text(float x, float y, float w, float h, float t);
  ~UI_text();
  
  void font(std::string path);
  void fontSize(int size);
  void color(SDL_Color c);
  void text(std::string content);
  
  void render();
  void destroy();
};
```

### UI_window

Clasa UI_window reprezintă fereastra principală a aplicației. Gestionează randarea tuturor elementelor UI și gestionarea evenimentelor SDL.

####

 `class UI_window`

Clasa `UI_window` reprezintă fereastra principală a aplicației.

##### `UI_window(std::string title, int x, int y, int w, int h, int flags, int rendererFlags, float scale)`

Constructorul creează o nouă fereastră UI cu titlul, poziția, dimensiunea, indicatorii și scara specificate.

##### `~UI_window()`

Destructorul curăță fereastra UI.

##### `float scale()`

Returnează scara ferestrei UI.

##### `void scale(float s)`

Setează scara ferestrei UI.

##### `void add(UI* ui)`

Adaugă un element UI la fereastra UI.

##### `void remove(UI* ui)`

Înlătură un element UI din fereastra UI.

##### `void clear()`

Elimină toate elementele UI din fereastra UI.

##### `void render()`

Randare fereastră UI și toate elementele sale UI.

##### `void execute_event(const SDL_Event& _event)`

Execută gestionarea evenimentelor pentru fereastră UI și toate elementele sale UI.

##### `void fullscreen(bool enable)`

Comută fereastra UI între modul fullscreen și modul fereastră.

```cpp
class UI_window {
public:
  UI_window(std::string title, int x, int y, int w, int h, int flags, int rendererFlags, float scale);
  ~UI_window();
  
  float scale();
  void scale(float s);
  
  void add(UI* ui);
  void remove(UI* ui);
  void clear();
  
  void render();
  void execute_event(const SDL_Event& _event);
  
  void fullscreen(bool enable);
};
```

### Globals

Namespace Globals conține variabile globale utilizate în bibliotecă.

#### `namespace Globals`

Namespace `Globals` conține variabile globale utilizate în bibliotecă.

##### `extern TTF_Font* defaultFont`

Variabilă globală pentru fontul implicit utilizat de elementele UI pentru text.

##### `extern SDL_Renderer* globalRenderer`

Variabilă globală pentru renderizatorul utilizat pentru randarea elementelor UI.

### UI_engine

Namespace UI_engine conține funcții utile pentru configurarea și gestionarea bibliotecii.

#### `namespace UI_engine`

Namespace `UI_engine` conține funcții utile pentru configurarea și gestionarea bibliotecii.

##### `bool init(int flags)`

Inițializează SDL și alte biblioteci necesare pentru funcționarea bibliotecii UI_engine.

##### `void finit()`

Curăță resursele și închide biblioteca UI_engine.

##### `void processEvents(UI_window* _window)`

Procesează toate evenimentele SDL pentru fereastra specificată.

##### `void renderFrame(UI_window* _window)`

Randare cadrul pentru fereastra specificată.

##### `void updateWindowSize(UI_window* _window, int w, int h)`

Actualizează dimensiunea ferestrei specificate.

##### `void updateElementPositions(UI_window* _window)`

Actualizează pozițiile tuturor elementelor UI în fereastra specificată.

```cpp
namespace Globals {
  extern TTF_Font* defaultFont;
  extern SDL_Renderer* globalRenderer;
}

namespace UI_engine {
  bool init(int flags);
  void finit();
  
  void processEvents(UI_window* _window);
  void renderFrame(UI_window* _window);
  void updateWindowSize(UI_window* _window, int w, int h);
  void updateElementPositions(UI_window* _window);
}
```

## Concluzie

Felicitări! Acum sunteți familiarizați cu biblioteca UI_engine și puteți începe să creați interfețe utilizator personalizate folosind această bibliotecă în proiectele dvs. Cu componente precum UI_frame, UI_image și UI_text, puteți crea interfețe flexibile și atractive pentru aplicațiile dvs. Cu cât explorați mai multe funcționalități ale bibliotecii, cu atât veți putea crea interfețe mai complexe și sofisticate. Luați în considerare să consultați documentația oficială a SDL pentru a înțelege mai bine interacțiunea dintre SDL și UI_engine.

Dacă aveți întrebări sau întâmpinați probleme, nu ezitați să verificați depozitul oficial de pe GitHub pentru probleme deschise sau să adăugați propriile probleme. Sperăm că veți avea o experiență plăcută lucrând cu UI_engine și că veți construi interfețe utilizator uimitoare pentru aplicațiile dvs.!
