#include "neuron.h"

class Effector
{
 public:
  Effector();
  ~Effector();

  void Act()=0;
 private:
  Neuron *input_;
};

class JointEffector : public Effector
{
 public:
  JointEffector();
  ~JointEffector();

  void Act();
 private:
  Joint *joint_;
};
