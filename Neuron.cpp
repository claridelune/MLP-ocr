#include "Neuron.h"
#include <cmath>

Neuron::Neuron(int numNextNeurons, int _index): index(_index)
{
    for (int i = 0; i < numNextNeurons; i++) {
        weights.emplace_back();
        weights.back() = Neuron::randomWeight();
    }
}

void Neuron::feedForward(const Layer &prevLayer)
{
    double sum = 0.0;
    for (int i = 0; i < prevLayer.size(); i++) {
        // std::cout << "value prev: " << prevLayer[i].getValue() << " weight: " << prevLayer[i].weights[index] << std::endl;
        sum += prevLayer[i].getValue() * prevLayer[i].weights[index];
    }
    // std::cout << "sum: "<< sum << std::endl;
    value = sigmoid(sum);
    // std::cout << "value: " << value << std::endl;
}

void Neuron::calcHiddenErrors(const Layer &nextLayer)
{
    // sum
    double sum = 0.0;
    for (int i = 0; i < nextLayer.size() - 1; i++) {
        sum += weights[i] * nextLayer[i].getError();
    }
    error = sum * dSigmoid();
}

void Neuron::calcWeights(Layer &prevLayer, double n)
{
    for (int i = 0; i < prevLayer.size(); ++i) {
        Neuron &neuron = prevLayer[i];
        double oldWeight = neuron.weights[index];

        // std::cout << "value: " << neuron.getValue() << std::endl;
        // std::cout << "n: " << n << std::endl;
        // std::cout << "error: " << error << std::endl;
        neuron.weights[index] = oldWeight + neuron.getValue()*n*error;
    }
}

double Neuron::sigmoid(double x)
{
    return 1/(1 + std::exp(-x));
}

double Neuron::dSigmoid()
{
    return value*(1-value);
}

void Neuron::setValue(double x)
{
    value = x;
}

double Neuron::getValue() const
{
    return value;
}

void Neuron::setError(double x)
{
    error = x;
}

double Neuron::getError() const
{
    return error;
}
