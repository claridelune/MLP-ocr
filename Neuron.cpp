#include "Neuron.h"
#include <cmath>

Neuron::Neuron(int numNextNeurons, int _index): index(_index)
{
    for (int i = 0; i < numNextNeurons; i++) {
        weights.emplace_back();
        weights.back() = 0;
    }
}

void Neuron::feedForward(const Layer &prevLayer)
{
    double sum = 0.0;
    for (int i = 0; i < prevLayer.size(); i++) {
        sum += prevLayer[i].getValue() * prevLayer[i].weights[index];
    }
    value = sigmoid(sum);
}

double Neuron::sigmoid(double x)
{
    return 1/(1 + std::exp(-x));
}

double Neuron::dSigmoid()
{
    return value*(1-value);
}

void Neuron::setValue(int x)
{
    value = x;
}

int Neuron::getValue() const
{
    return value;
}

void Neuron::setError(int x)
{
    error = x;
}

int Neuron::getError() const
{
    return error;
}
