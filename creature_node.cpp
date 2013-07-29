#include "creature_node.h"

CreatureNode::CreatureNode(float scale, 
                           float density, 
                           const std::shared_ptr<btBoxShape> &shape)
    : scale_(scale), density_(density), shape_(shape), body_(NULL)
{
}

CreatureNode::CreatureNode(float scale, float density, const btVector3 &dimensions) 
    : scale_(scale), 
      density_(density), 
      shape_(new btBoxShape(dimensions)), 
      body_(NULL) 
{
}

CreatureNode::~CreatureNode()
{
}

void CreatureNode::AddToWorld(btDynamicsWorld *world, const btVector3 &pos)
{
   btTransform start_transform;
   start_transform.setIdentity();
   start_transform.setOrigin(pos);
   btDefaultMotionState *motion_state = 
      new btDefaultMotionState(start_transform);
   
   //TODO: calculate mass as density * volume using hierarchical scale 
   btScalar mass(1.f);
   btVector3 local_inertia(0, 0, 0);
   shape_->calculateLocalInertia(mass, local_inertia);

   btRigidBody::btRigidBodyConstructionInfo info(mass, 
                                                 motion_state,
                                                 shape_.get(),
                                                 local_inertia);
   body_ = new btRigidBody(info);
   world->addRigidBody(body_);
}
   
void CreatureNode::RemoveFromWorld(btDynamicsWorld *world)
{
   if(body_)
   {
      world->removeCollisionObject(body_);
      if(auto ms = body_->getMotionState())
      {
         delete ms;
      }
      delete body_;
   }
}
