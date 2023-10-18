#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<double> targetToVector(int target) {
    std::vector<double> targetVals(10, 0.0);
    targetVals[target] = 1.0;
    return targetVals;
}

std::vector<double> lineToVector(const std::string& line) {
    std::vector<double> result;
    std::stringstream ss(line);
    std::string value;

    while (getline(ss, value, ',')) {
        result.push_back(stod(value));
    }

    return result;
}

std::vector<std::vector<double>> readFile(const std::string& filename) {
    std::vector<std::vector<double>> data;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            data.push_back(lineToVector(line));
        }
        file.close();
    }

    return data;
}

int vectorToNumber(const std::vector<double>& outputVals) {
    return std::max_element(outputVals.begin(), outputVals.end()) - outputVals.begin();
}

/* // Función para convertir el vector de salida en un número
int main() {
    // Topología de la red
    vector<unsigned> topology = {30, 15, 10};
    Net myNet(topology);

    // Datos de entrenamiento
    vector<vector<double>> trainingData = {
        // ... [tus datos aquí]
    };
    vector<int> trainingLabels = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // Correspondencia con tus datos

    // Entrenar la red
    for (int epoch = 0; epoch < 2000; epoch++) {
        for (size_t i = 0; i < trainingData.size(); i++) {
            myNet.feedForward(trainingData[i]);
            myNet.backProp(targetToVector(trainingLabels[i]));
        }
    }

    // Datos de prueba
    vector<vector<double>> testData = {
        // ... [tus datos de prueba aquí]
    };

    // Probar la red
    for (size_t i = 0; i < testData.size(); i++) {
        myNet.feedForward(testData[i]);
        vector<double> resultVals;
        myNet.getResults(resultVals);
        int predictedNumber = vectorToNumber(resultVals);
        cout << "Predicted number: " << predictedNumber << endl;
    }

    return 0;
} */
