#include "Perceptron.h"

Perceptron::Perceptron(const std::vector<int> setup)
{
    for (auto it = setup.begin(); it != setup.end(); ++it) {
        layers.emplace_back();

        int numNextNeurons = (std::next(it) == setup.end()) ? 0 : *std::next(it);

        for (unsigned neuronnum = 0; neuronnum <= *it; ++neuronnum) {
            layers.back().emplace_back(numNextNeurons, neuronnum);
            std::cout << "made a neuron!" << std::endl;
        }
    }

    layers.back().back().setValue(1.0);
}

void Perceptron::feedForward(std::vector<double> &input)
{
    for (int i = 0; i < input.size(); i++) {
        layers[0][i].setValue(input[i]);
    }

    for (auto layerIt = std::next(layers.begin()); layerIt != layers.end(); layerIt++) {
        Layer &prevLayer = *std::prev(layerIt);
        for (auto &neuron : *layerIt) {
            neuron.feedForward(prevLayer);
        }
    }
}

void Perceptron::backPropagation(std::vector<double> &target)
{
    // output error
    Layer &backLayer = layers.back();
    auto neuronIt = backLayer.begin();
    auto targetIt = target.begin();
    for (; neuronIt != backLayer.end() && targetIt != target.end(); neuronIt++, targetIt++) {
        double error = (*targetIt - neuronIt->getValue())*neuronIt->dSigmoid();
        neuronIt->setError(error);
        // update output weights
        for (auto &w : neuronIt->weights) {
            w  = w + n*neuronIt->getValue()*neuronIt->getError();
        }
    }

    // hidden error
}

