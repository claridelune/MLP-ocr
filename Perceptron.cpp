#include "Perceptron.h"

Perceptron::Perceptron(const std::vector<int> setup)
{   
    for (auto it = setup.begin(); it != setup.end(); ++it) {
        layers.emplace_back();

        int numNextNeurons = (std::next(it) == setup.end()) ? 0 : *std::next(it);

        for (unsigned neuronnum = 0; neuronnum <= *it; ++neuronnum) {
            layers.back().emplace_back(numNextNeurons, neuronnum);
            // std::cout << "made a neuron!" << std::endl;
        }
        layers.back().back().setValue(1.0);
    }
}

void Perceptron::feedForward(std::vector<double> &input)
{
    for (int i = 0; i < input.size(); i++) {
        layers[0][i].setValue(input[i]);
        // std::cout << "value P capa 0: "<< layers[0][i].getValue() << std::endl;
    }

    for (int layerNum = 1; layerNum < layers.size(); ++layerNum) {
        Layer &prevLayer = layers[layerNum - 1];
        for (int n = 0; n < layers[layerNum].size() - 1; ++n) {
            layers[layerNum][n].feedForward(prevLayer);
            // std::cout << "value P: "<< layers[layerNum][n].getValue() << std::endl;
        }
    }
}

void Perceptron::backPropagation(std::vector<double> target)
{
    // output error
    Layer &outputLayer = layers.back();
    for (int i = 0; i < outputLayer.size() - 1; ++i) {
        double error = (target[i] - outputLayer[i].getValue()) * outputLayer[i].dSigmoid();
        outputLayer[i].setError(error);

        for (auto &w : outputLayer[i].weights) {
            w = w + n * outputLayer[i].getValue()*outputLayer[i].getError();
        }
    }

    // hidden error
    for (int layerNum = layers.size() - 2; layerNum > 0; --layerNum) {
        Layer &hiddenLayer = layers[layerNum];
        Layer &nextLayer = layers[layerNum + 1];

        for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
            hiddenLayer[n].calcHiddenErrors(nextLayer);
        }
    }

    //hidden weights
    for (int layerNum = layers.size() - 1; layerNum > 0; --layerNum) {
        Layer &layer = layers[layerNum];
        Layer &prevLayer = layers[layerNum - 1];

        for (unsigned n = 0; n < layer.size() - 1; ++n) {
            layer[n].updateHiddenWeights(prevLayer);
        }
    }
}

void Perceptron::getOutput(std::vector<double> &resultVals) const
{
    resultVals.clear();

    for (int i = 0; i < layers.back().size() - 1; i++) {
        resultVals.push_back(layers.back()[i].getValue());
    }
}
