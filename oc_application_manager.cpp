#include <OPENGL/gl.h>
#include <OPENGL/glu.h>
#include <OPENGL/glext.h>

#include <iostream>
#include <boost/thread.hpp>

#include "oc_application_manager.h"

OCApplicationManager::OCApplicationManager()
    : width_(DEFAULT_WINDOW_WIDTH), height_(DEFAULT_WINDOW_HEIGHT) 
{
   m_running = true;
   m_window = NULL;
}

OCApplicationManager::OCApplicationManager(unsigned int width, unsigned int height)
    : width_(width), height_(height) 
{
   m_running = true;
   m_window = NULL;
}

int OCApplicationManager::execute()
{
   
   if (!init())
   {
      return -1;
   }
   
   boost::thread model_thread(&OCApplicationManager::update, this);
   render();

   model_thread.join();
   cleanup();

   return 0;
}

bool OCApplicationManager::init()
{
   if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		return false;
	}
	
   model_ = new OCModel();
   model_->init();

   m_window = SDL_CreateWindow("Cloak", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
         width_, height_, 
         SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
   view_ = new OCView(m_window, width_, height_, model_);

   return true;
}

void OCApplicationManager::update() 
{
   SDL_Event event;
   while(m_running)
   {
      while(SDL_PollEvent(&event))
      {
         onEvent(&event);     
      }
      //model_->update();
   }
}

void OCApplicationManager::render()
{
   SDL_Event event;
   while(m_running)
   {
      
      while(SDL_PollEvent(&event))
      {
         onEvent(&event);     
      }
      view_->render();
   }
}

void OCApplicationManager::cleanup()
{
   delete view_;
   SDL_Quit();
}

void OCApplicationManager::onInputFocus() 
{
}
 
void OCApplicationManager::onInputBlur()
{
}

void OCApplicationManager::onEvent(SDL_Event* event)
{
   switch(event->type)
   {
      case SDL_KEYDOWN: 
      {
         onKeyDown(event->key.keysym.sym,event->key.keysym.mod,event->key.keysym.scancode);
         break;
      }
      case SDL_KEYUP: 
      {
         onKeyUp(event->key.keysym.sym,event->key.keysym.mod,event->key.keysym.scancode);
         break;
      }
      case SDL_MOUSEMOTION: 
      {
         onMouseMove(event->motion.x,event->motion.y,event->motion.xrel, event->motion.yrel,
            (event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,
            (event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,
            (event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
         break;
      }
      case SDL_MOUSEBUTTONDOWN: 
      {
         switch(event->button.button) 
         {
            case SDL_BUTTON_LEFT: 
            {
               onLButtonDown(event->button.x,event->button.y);
               break;
            }
            case SDL_BUTTON_RIGHT: 
            {
               onRButtonDown(event->button.x,event->button.y);
               break;
            }
            case SDL_BUTTON_MIDDLE: 
            {
               onMButtonDown(event->button.x,event->button.y);
               break;
            }
         }
         break;
      }
      case SDL_MOUSEBUTTONUP:    
      {
         switch(event->button.button) 
         {
            case SDL_BUTTON_LEFT: 
            {
               onLButtonUp(event->button.x,event->button.y);
               break;
            }
            case SDL_BUTTON_RIGHT: 
            {
               onRButtonUp(event->button.x,event->button.y);
               break;
            }
            case SDL_BUTTON_MIDDLE: 
            {
               onMButtonUp(event->button.x,event->button.y);
               break;
            }
         }
         break;
      }
      case SDL_JOYAXISMOTION: 
      {
            onJoyAxis(event->jaxis.which,event->jaxis.axis,event->jaxis.value);
            break;
      }
      case SDL_JOYBALLMOTION: 
      {
         onJoyBall(event->jball.which,event->jball.ball,event->jball.xrel,event->jball.yrel);
         break;
      }
      case SDL_JOYHATMOTION: 
      {
            onJoyHat(event->jhat.which,event->jhat.hat,event->jhat.value);
            break;
      }
      case SDL_JOYBUTTONDOWN: 
      {
            onJoyButtonDown(event->jbutton.which,event->jbutton.button);
            break;
      }
      case SDL_JOYBUTTONUP: 
      {
            onJoyButtonUp(event->jbutton.which,event->jbutton.button);
            break;
      }
      case SDL_QUIT: 
      {
            onExit();
            break;
      }
      case SDL_SYSWMEVENT: 
      {
            //Ignoe
            break;
      }
      default: 
      {
            onUser(event->user.type,event->user.code,event->user.data1,event->user.data2);
            break;
      }
   }
}
 
void OCApplicationManager::onKeyDown(SDL_Keycode sym, Uint16 mod, SDL_Scancode key) 
{
   std::cout << sym << "," << mod << "," << key << std::endl;
   switch(mod)
   {
      case KMOD_SHIFT: break;
      case KMOD_CTRL: break;
      case KMOD_ALT: break;
      case KMOD_LGUI: case KMOD_RGUI: 
      {
         switch(sym)
         {
            case SDLK_q: 
            {
               onExit(); 
               break;
            }
            default: break;
         }
      }
      break;
      default: break;
   }
}
 
void OCApplicationManager::onKeyUp(SDL_Keycode sym, Uint16 mod, SDL_Scancode key) 
{
}

void OCApplicationManager::onMouseFocus()
{
}
 
void OCApplicationManager::onMouseBlur()
{
}
 
void OCApplicationManager::onMouseMove(int mX, int mY, int relX, int relY, bool left,bool right,bool middle) 
{
}
 
void OCApplicationManager::onMouseWheel(bool up, bool down)     //Not implemented
{
}
 
void OCApplicationManager::onLButtonDown(int mX, int mY) 
{
}
 
void OCApplicationManager::onLButtonUp(int mX, int mY)
{
}
 
void OCApplicationManager::onRButtonDown(int mX, int mY) 
{
}
 
void OCApplicationManager::onRButtonUp(int mX, int mY)
{
}
 
void OCApplicationManager::onMButtonDown(int mX, int mY) 
{
}
 
void OCApplicationManager::onMButtonUp(int mX, int mY)
{
}
 
void OCApplicationManager::onJoyAxis(Uint8 which, Uint8 axis, Sint16 value) 
{
}
 
void OCApplicationManager::onJoyButtonDown(Uint8 which, Uint8 button) 
{
}
 
void OCApplicationManager::onJoyButtonUp(Uint8 which, Uint8 button) 
{
}
 
void OCApplicationManager::onJoyHat(Uint8 which, Uint8 hat, Uint8 value) 
{
}
 
void OCApplicationManager::onJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) 
{
}
 
void OCApplicationManager::onMinimize() 
{
}
 
void OCApplicationManager::onRestore() 
{
}
 
void OCApplicationManager::onResize(int w,int h) 
{
}
 
void OCApplicationManager::onExpose() 
{
}
 
void OCApplicationManager::onExit() 
{
   m_running = false;
}
 
void OCApplicationManager::onUser(Uint8 type, int code, void* data1, void* data2)
{
}
