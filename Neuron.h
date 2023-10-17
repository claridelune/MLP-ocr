#include <vector>
#include <cmath>

class Neuron;

typedef std::vector<Neuron> Layer;

class Neuron
{
    public:
        Neuron(int numNextNeurons, int index);
        void feedForward(const Layer &prevLayer);
        void setValue(int x);
        int getValue() const;
        void setError(int x);
        int getError() const;
        double dSigmoid();
        std::vector<double> weights;
    private:
        double sigmoid(double x);
        double value;
        double error;
        int index;
};
