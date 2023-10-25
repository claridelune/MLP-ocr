#include "Perceptron.h"
#include "utils.h"
#include "DataVisualizer.h"
#include <vector>

int main(){
    std::vector<int> setup = {30, 10};
    std::vector<std::vector<double>> trainingData = readFile("training_data.txt");
    std::vector<std::vector<double>> testData = readFile("test_data.txt");
    std::vector<int> trainingLabels = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Perceptron ocr(setup);
    
    // Entrenar la red
    for (int epoch = 0; epoch < 500; epoch++) {
        for (size_t i = 0; i < trainingData.size(); i++) {
            ocr.feedForward(trainingData[i]);
            ocr.backPropagation(targetToVector(trainingLabels[i%10]));
        }
    }

    // Probar
    std::vector<int> predictions;
    for (size_t i = 0; i < testData.size(); i++) {
        ocr.feedForward(testData[i]);
        std::vector<double> resultVals;
        ocr.getOutput(resultVals);

        int predict = vectorToNumber(resultVals);
        /* for (auto i: resultVals){
            std::cout << i << " ";
        } */
        std::cout << "Predicted number: " << predict << std::endl;
        predictions.push_back(predict);

    }

    DataVisualizer visualizer(trainingData, testData, predictions);
    visualizer.run();
    return 0;
}
