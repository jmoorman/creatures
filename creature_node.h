#pragma once

#include <vector>
#include <memory>

#include <btBulletDynamicsCommon.h>


class CreatureNode
{
 public:
  CreatureNode(float scale, float density, const std::shared_ptr<btCollisionShape> &shape);
  ~CreatureNode();
  
  float scale_; // [0.5, 2]
  float density_; // [0 - 1]
  
  /* Needs to be reused descendants but deleted when this genetic line 
   * ceases to exist.
   */
  std::shared_ptr<btCollisionShape> shape_; //This should be reused by descendants
  
  btRigidBody *body_;
};
