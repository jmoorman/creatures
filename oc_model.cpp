#include <vector>
#include <iostream>

#include "oc_model.h"
#include "oc_debug_draw.h"
#include "creature_node.h"

OCModel::OCModel()
{}

OCModel::~OCModel()
{}

void OCModel::init()
{
   collision_configuration_ = new btDefaultCollisionConfiguration();
   dispatcher_ = new btCollisionDispatcher(collision_configuration_);
   broadphase_ = new btDbvtBroadphase();
   solver_ = new btSequentialImpulseConstraintSolver;
   dynamics_world_ = new btDiscreteDynamicsWorld(dispatcher_, broadphase_, 
         solver_, collision_configuration_);
   dynamics_world_->setGravity(btVector3(0, -10, 0));
   dynamics_world_->setDebugDrawer(new OCDebugDraw());
   
   //Temporary stuff to get it working
   btBoxShape *ground_shape = 
         new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
   btTransform ground_transform;
   ground_transform.setIdentity();
   ground_transform.setOrigin(btVector3(0, -50, 0));
   btScalar mass(0.);
   btVector3 local_inertia(0, 0, 0);
   btDefaultMotionState *my_motion_state = new btDefaultMotionState(ground_transform);
   btRigidBody::btRigidBodyConstructionInfo ground_info(mass, 
                                                    my_motion_state,
                                                    ground_shape, 
                                                    local_inertia);
   btRigidBody *ground = new btRigidBody(ground_info);
   dynamics_world_->addRigidBody(ground);

      //collision_shapes_.push_back(col_shape);
      //std::cout << "local inertia: ( " << local_inertia.x() << ", " << local_inertia.y() << ", " <<  local_inertia.z() << " )\n"; 
               
   //CreatureNode *creature = new CreatureNode(1, 1, btVector3(1, 1, 1));
   //CreatureNode *creature = new CreatureNode(1, 1, col_shape);
   //creatures_.push_back(creature);
   //creature->AddToWorld(dynamics_world_, btVector3(
   //         btScalar(start_x + 20),
   //         btScalar(20 + start_y),
   //         btScalar(start_z + 20)));
               
   mass = 1.f;
   btTransform start_transform;
   start_transform.setIdentity();
   start_transform.setOrigin(btVector3(
                       btScalar(-5),
                       btScalar(15),
                       btScalar(-5)));
   my_motion_state = new btDefaultMotionState(start_transform);
   btBoxShape *col_shape = new btBoxShape(btVector3(1, 1, 1));
   col_shape->calculateLocalInertia(mass, local_inertia);

   btRigidBody::btRigidBodyConstructionInfo rb_info(mass,
         my_motion_state,
         col_shape,
         local_inertia);
          
   btRigidBody *body = new btRigidBody(rb_info);
   dynamics_world_->addRigidBody(body);
   
   CreatureNode *c = new CreatureNode(1, 1, btVector3(2, 3, 2));
   c->AddToWorld(dynamics_world_, btVector3(0, 15, 0));

   c = new CreatureNode(1, 1, c->shape_);
   c->AddToWorld(dynamics_world_, btVector3(10, 15, 10));
   
}

void OCModel::update(float dt)
{
   dynamics_world_->stepSimulation(dt);
}

void OCModel::cleanup()
{
   for(int i = dynamics_world_->getNumCollisionObjects()-1; i >= 0; i--)
   {
      btCollisionObject *obj = dynamics_world_->getCollisionObjectArray()[i];
      btRigidBody *body = btRigidBody::upcast(obj);
      if (body && body->getMotionState())
      {
         delete body->getMotionState();
      }
      dynamics_world_->removeCollisionObject(obj);
      delete obj;
   }
   for(int j = 0; j < collision_shapes_.size(); j++)
   {
      btCollisionShape *shape = collision_shapes_[j];
      delete shape;
   }
   collision_shapes_.clear();
   delete dynamics_world_;
   delete solver_;
   delete broadphase_;
   delete dispatcher_;
   delete collision_configuration_;
}

