#pragma once

#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include "oc_model.h"
#include "oc_view.h"

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

class OCApplicationManager
{
public:
   OCApplicationManager();
   OCApplicationManager(unsigned int width, unsigned int height);
   int execute();

private:
   unsigned int width_;
   unsigned int height_;
   bool m_running;
   SDL_Window *m_window;
   OCModel *model_;
   OCView *view_;

   bool init();
   void update();
   void render();
   void cleanup();

   void onEvent(SDL_Event *event);
   void onInputFocus(); 
   void onInputBlur(); 
   void onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode key); 
   void onKeyUp(SDL_Keycode sym, Uint16 mod, SDL_Scancode key);  
   void onMouseFocus(); 
   void onMouseBlur(); 
   void onMouseMove(int mX, int mY, int relX, int relY, bool left,bool right,bool middle); 
   void onMouseWheel(bool up, bool down);     //Not implemented
   void onLButtonDown(int mX, int mY); 
   void onLButtonUp(int mX, int mY); 
   void onRButtonDown(int mX, int mY); 
   void onRButtonUp(int mX, int mY); 
   void onMButtonDown(int mX, int mY); 
   void onMButtonUp(int mX, int mY); 
   void onJoyAxis(Uint8 which, Uint8 axis, Sint16 value); 
   void onJoyButtonDown(Uint8 which, Uint8 button); 
   void onJoyButtonUp(Uint8 which, Uint8 button); 
   void onJoyHat(Uint8 which, Uint8 hat, Uint8 value); 
   void onJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel); 
   void onMinimize(); 
   void onRestore(); 
   void onResize(int w,int h); 
   void onExpose(); 
   void onExit(); 
   void onUser(Uint8 type, int code, void* data1, void* data2); 
};
