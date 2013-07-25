#pragma once

#include <btBulletDynamicsCommon.h>

#include <vector>

class CreatureNode
{
 public:
  std::vector<CreatureNode *> children;
}
