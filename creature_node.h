#pragma once

#include <btBulletDynamicsCommon.h>

#include <vector>

class CreatureNode
{
 public:
  CreatureNode(float scale, float density, btVector3 &dimensions);
  ~CreatureNode();

  btRigidBody *body_;
  btVector3 dimensions_;
  float scale_; // [0.5, 2]
  float density_; // [0 - 1]
}
