#include "neuron.h"

Neuron::Neuron(unsigned int num_inputs) 
    : num_inputs_(num_inputs), value_(0), mark_(false)
{}

Neuron::~Neuron()
{}

float Neuron::GetValue()
{
  if(!mark_)
  {
    mark_ = true;
    ComputeValue();
  }
  return value_;
}

void Neuron::ClearMark()
{
  mark_ = false;
}

SumNeuron::SumNeuron() : Neuron(2)
{}

SumNeuron::~SumNeuron()
{}

void SumNeuron::ComputeValue()
{
  value_ = inputs_[0]->GetValue() + inputs_[1]->GetValue();
}

ThresholdNeuron::ThresholdNeuron(float threshold) 
    : Neuron(1), threshold_(threshold)
{}

ThresholdNeuron::~ThresholdNeuron()
{}

void ThresholdNeuron::ComputeValue()
{
  value_ = inputs_[0]->GetValue() < threshold_ ? -1.0 : 1.0; 
}

MemoryNeuron::MemoryNeuron() : Neuron(1)
{}

MemoryNeuron::~MemoryNeuron()
{}

void MemoryNeuron::ComputeValue()
{
  value_ = inputs_[0]->GetValue();
}

HungerNeuron::HungerNeuron() : Neuron(0)
{}

HungerNeuron::~HungerNeuron()
{}

void HungerNeuron::ComputeValue()
{
  value_ = 0;
}

int main()
{
  ThresholdNeuron tn(0.7);
  return 0;
}
