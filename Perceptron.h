#include <iostream>
#include <vector>

#include "Neuron.h"

class Perceptron
{
    public:
        Perceptron(const std::vector<int> setup);
        void feedForward(std::vector<double> &input);
        void backPropagation(std::vector<double> target);
        void getOutput(std::vector<double> &result) const;
    private:
        const double n = 0.5;
        std::vector<Layer> layers; // Layers[layerNum][NeuronNum]
};
