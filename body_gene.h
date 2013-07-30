#pragma once

#include <vector>

#include "neural_node.h"

class BodyGene
{
 public:
  BodyGene();
  ~BodyGene();
  
  vector<NeuralGene *> neural_genes_;

  btVector3 base_dimensions_;
  btScalar relative_scale_;
  btVector3 relative_position_;
  btVector3 relative_orientation_;
  bool mark_;
};
