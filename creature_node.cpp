#include "creature_node.h"

CreatureNode::CreatureNode(float scale, float density, 
                           const std::shared_ptr<btCollisionShape> &shape)
    : scale_(scale), density_(density), shape_(shape)
{
}

CreatureNode::~CreatureNode()
{

}


