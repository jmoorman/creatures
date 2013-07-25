#include <OPENGL/gl.h>
#include <OPENGL/glu.h>
#include <OPENGL/glext.h>

#include "oc_debug_draw.h"

void OCDebugDraw::drawLine(const btVector3 &from, 
                           const btVector3 &to,
                           const btVector3 &fromColor,
                           const btVector3 &toColor)
{
   glBegin(GL_LINES);
      glColor3f(fromColor.x(), fromColor.y(), fromColor.z());
      glVertex3f(from.x(), from.y(), from.z());
      glColor3f(toColor.x(), toColor.y(), toColor.z());
      glVertex3f(to.x(), to.y(), to.z());
   glEnd();
}

void OCDebugDraw::drawLine(const btVector3 &from, 
                      const btVector3 &to,
                      const btVector3 &color)
{
   drawLine(from, to, color, color);
}

void OCDebugDraw::drawContactPoint(const btVector3 &PointOnB, 
                                   const btVector3 &normalOnB, 
                                   btScalar distance, 
                                   int lifeTime, 
                                   const btVector3 &color)
{
}

void OCDebugDraw::reportErrorWarning(const char *warningString)
{
}

void OCDebugDraw::draw3dText(const btVector3 &location, const char *textString)
{
}

void OCDebugDraw::setDebugMode(int debugMode)
{
}

int OCDebugDraw::getDebugMode() const
{
   return btIDebugDraw::DBG_DrawWireframe;
}
