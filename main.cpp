#include <iostream>
#include <vector>
#include "Perceptron.h"

int main(){
    std::vector<int> setup = {3, 2, 1};
    Perceptron ocr(setup);

    std::vector<double> input;
    // ocr.feedForward(input);
    // ocr.backPropagation();
    // ocr.getOutput();

    return 0;
}
