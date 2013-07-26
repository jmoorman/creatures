#include "creature_node.h"

CreatureNode::CreatureNode(float scale, float density, 
                           const std::shared_ptr<btCollisionShape> &shape)
    : scale_(scale), density_(density), shape_(shape), body_(NULL)
{
}

CreatureNode::CreatureNode(float scale, float density, btVector3 &dimensions) 
    : scale_(scale), density_(density), body_(NULL)
{
   shape_(new btBoxShape(dimensions));
}

CreatureNode::~CreatureNode()
{
   delete body_;
}

void CreatureNode::AddToWorld(btDynamicsWorld *world, btVector3 &pos)
{
   btTransform start_transform;
   start_transform.setOrigin(pos);
   btDefaultMotionState *motion_state = 
      new btDefaultMotionState(start_transform);
   
   //TODO: calculate mass as density * volume using hierarchical scale 
   btScalar mass(1.f);
   btVector3 local_inertia(0, 0, 0);
   shape_->calculateLocalInertia(mass, local_inertia);

   btRigidBody::btRigidBodyConstructionInfo info(mass, 
                                                 motion_state,
                                                 shape.get(),
                                                 local_inertia);
   body_ = new btRigidBody(info);
   world->addRigidBody(body_);
}
