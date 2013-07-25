#pragma once

#include <vector>

class Neuron
{
 public:
  Neuron(unsigned int num_inputs);
  ~Neuron();

  float GetValue(); //Returns the value of this node and marks it
  void ClearMark(); //Sets mark to false
 
 protected:
  std::vector<Neuron *> inputs_; //List of inputs to this node
  unsigned int num_inputs_; //The number of inputs this node has
  float value_; //The computed value of this node
  bool mark_; //Indicates whether or not this node has been visited
 private:
  virtual void ComputeValue() = 0; //Computes the value of this node
};

//Sums the inputs
//Input: 2
//Output: 1
class SumNeuron : public Neuron
{
 public:
  SumNeuron();
  ~SumNeuron();
  void ComputeValue();
};

//Thresholds the input
//Input: 1
//Output: 1
class ThresholdNeuron : public Neuron
{
 public:
  ThresholdNeuron(float threshold);
  ~ThresholdNeuron();
  void ComputeValue();
 private:
  float threshold_;
};

//Saves a value
//Input: 1
//Output: 1
class MemoryNeuron : public Neuron
{
 public:
  MemoryNeuron();
  ~MemoryNeuron();
  void ComputeValue();
};

//Detects hunger in the creature
//Input: 0
//Output: 1
class HungerNeuron : public Neuron
{
  HungerNeuron();
  ~HungerNeuron();
  void ComputeValue();
};
