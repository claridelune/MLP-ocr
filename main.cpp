#include "Perceptron.h"
#include "utils.h"
#include <vector>

void printData(const std::vector<std::vector<double>>& data) {
    for (const auto& row : data) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main(){
    std::vector<int> setup = {30, 2, 2, 1, 10};
    std::vector<std::vector<double>> trainingData = readFile("training_data.txt");
    std::vector<std::vector<double>> testData = readFile("test_data.txt");
    std::vector<int> trainingLabels = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Perceptron ocr(setup);
    
    /* std::cout << "Training Data:" << std::endl;
    printData(trainingData);
    
    std::cout << "\nTest Data:" << std::endl;
    printData(testData); */

    // Entrenar la red
    for (int epoch = 0; epoch < 20000; epoch++) {
        for (size_t i = 0; i < trainingData.size(); i++) {
            ocr.feedForward(trainingData[i]);
            ocr.backPropagation(targetToVector(trainingLabels[i]));
        }
    }

    // Probar
    for (size_t i = 0; i < testData.size(); i++) {
        ocr.feedForward(testData[i]);
        std::vector<double> resultVals;
        ocr.getOutput(resultVals);

        int predict = vectorToNumber(resultVals);
        /* for (auto i: resultVals){
            std::cout << i << " ";
        } */
        std::cout << "Predicted number: " << predict << std::endl;

    }
    return 0;
}
