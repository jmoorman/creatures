#include "oc_view.h"

#include <OPENGL/gl.h>
#include <OPENGL/glu.h>
#include <OPENGL/glext.h>

OCView::OCView(SDL_Window *window, unsigned int width, unsigned int height, OCModel *model)
      : width_(width), height_(height), model_(model)
{
   renderer_ = SDL_CreateRenderer(window, -1, 0);

   SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
   SDL_RenderClear(renderer_);
   SDL_RenderPresent(renderer_);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60, width_ / (double)height_, 0.1, 135.0);
   //glOrtho(0, m_screen->w, m_screen->h, 0, 1, -1);
   glMatrixMode(GL_MODELVIEW);
   glViewport(0, 0, width_, height_);

   glEnable(GL_TEXTURE_2D);

   glLoadIdentity();
}

void OCView::render()
{

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   
   gluLookAt(50, 5, 0, 0, 0, 0, 0, 1, 0);
   model_->dynamics_world()->debugDrawWorld();

   SDL_RenderPresent(renderer_);
}

OCView::~OCView()
{
   SDL_DestroyRenderer(renderer_);
}
