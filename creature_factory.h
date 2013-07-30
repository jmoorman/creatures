#pragma once

#include "creature.h"

class CreatureFactory
{
 public:
  CreatureFactory();
  ~CreatureFactory();

  Creature * Clone(Creature *creature);
 private:
};
