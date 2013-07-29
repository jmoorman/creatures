#pragma once

#include <vector>
#include <memory>

#include <btBulletDynamicsCommon.h>


class CreatureNode
{
 public:

  /*Create a new creature using the given collision shape*/
  CreatureNode(float scale, float density, const std::shared_ptr<btBoxShape> &shape);
  
  /*Create a new creature with the given dimensions*/
  CreatureNode(float scale, float density, const btVector3 &dimensions);
  
  ~CreatureNode();
  
  /*Initialize the physics of the node and add it to the simulation*/
  void AddToWorld(btDynamicsWorld *world, const btVector3 &pos);

  /*Remove rigid body from world and destroy it*/
  void RemoveFromWorld(btDynamicsWorld *world);

 private:
  //std::vector<CreatureNode *> children;
  
  float scale_; // [0.5, 2]
  float density_; // [0 - 1]
  
  /* 
   * Needs to be reused descendants but deleted when this genetic line 
   * ceases to exist.
   */
  std::shared_ptr<btBoxShape> shape_; 
  // btBoxShape *shape_;

  btRigidBody *body_;
};
