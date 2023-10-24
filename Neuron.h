#include <vector>
#include <cmath>
#include <iostream>

class Neuron;

typedef std::vector<Neuron> Layer;

class Neuron
{
    public:
        Neuron(int numNextNeurons, int index);
        void feedForward(const Layer &prevLayer);
        void calcHiddenErrors(const Layer &nextLayer);
        void calcWeights(Layer &prevLayer, double n);
        void setValue(double x);
        double getValue() const;
        void setError(double x);
        double getError() const;
        double dSigmoid();
        std::vector<double> weights;
    private:
        double sigmoid(double x);
        static double randomWeight(void) { return static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * 2.0 - 1.0; }
        double value;
        double error;
        int index;
};
