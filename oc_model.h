#pragma once

#include <btBulletDynamicsCommon.h>

class OCModel
{
 public:
  OCModel();
  ~OCModel();
  virtual void init();
  virtual void update(float dt);
  virtual void cleanup();
   
  btDiscreteDynamicsWorld *dynamics_world(){ return dynamics_world_; }
 private:
  btAlignedObjectArray<btCollisionShape *> collision_shapes_;
  btBroadphaseInterface *broadphase_;
  btCollisionDispatcher *dispatcher_;
  btConstraintSolver *solver_;
  btDefaultCollisionConfiguration *collision_configuration_;
  btDiscreteDynamicsWorld *dynamics_world_;
};
