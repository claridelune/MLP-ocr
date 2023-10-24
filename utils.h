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
