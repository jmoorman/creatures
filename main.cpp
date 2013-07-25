#include "oc_application_manager.h"
#include "neuron.h"

int main(int argc, char **argv)
{
   OCApplicationManager app(1366, 768);
   ThresholdNeuron tn(0.7);
   return app.execute();
}


