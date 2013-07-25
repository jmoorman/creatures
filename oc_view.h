#pragma once

#include <SDL2/SDL.h>

#include "oc_model.h"

class OCView
{
public:
   OCView(SDL_Window *window, unsigned int width, unsigned int height, OCModel *model);
   ~OCView();
   virtual void render();
private:
   SDL_Renderer *renderer_;
   unsigned int width_;
   unsigned int height_;
   OCModel *model_;
};
