
#include "oc_model.h"
#include "oc_debug_draw.h"

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
   {
   btBoxShape *ground_shape = 
         new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
   collision_shapes_.push_back(ground_shape);
   btTransform ground_transform;
   ground_transform.setIdentity();
   ground_transform.setOrigin(btVector3(0, -50, 0));
   btScalar mass(0.);
   btVector3 local_inertia(0, 0, 0);
   btDefaultMotionState *my_motion_state = new btDefaultMotionState(ground_transform);
   btRigidBody::btRigidBodyConstructionInfo rb_info(mass, 
                                                    my_motion_state,
                                                    ground_shape, 
                                                    local_inertia);
   btRigidBody *body = new btRigidBody(rb_info);
   dynamics_world_->addRigidBody(body);
   }

   {

      btBoxShape *col_shape = new btBoxShape(btVector3(1, 1, 1));
      collision_shapes_.push_back(col_shape);
      btTransform start_transform;
      btScalar mass(1.f);
      btVector3 local_inertia(0, 0, 0);
      col_shape->calculateLocalInertia(mass, local_inertia);
      
      float array_size = 5;
      float start_x = -5 - array_size/2;
      float start_y = -5;
      float start_z = -3 - array_size/2;
      for (int k = 0; k < array_size; k++)
      {
         for (int i = 0; i < array_size; i++)
         {
            for (int j = 0; j < array_size; j++)
            {
               start_transform.setOrigin(btVector3(
                        btScalar(2.0 * i + start_x),
                        btScalar(20 + 2.0 * k + start_y),
                        btScalar(2.0 * j + start_z)));

               btDefaultMotionState *my_motion_state = 
                     new btDefaultMotionState(start_transform);
               btRigidBody::btRigidBodyConstructionInfo rb_info(mass,
                                                                my_motion_state,
                                                                col_shape,
                                                                local_inertia);
               btRigidBody *body = new btRigidBody(rb_info);
               dynamics_world_->addRigidBody(body);
               
            }
         }
      }
   }
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

