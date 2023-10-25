#ifndef DATA_VISUALIZER_H
#define DATA_VISUALIZER_H

#include <GL/freeglut.h>
#include <vector>
#include <iostream>

class DataVisualizer {
public:
    DataVisualizer(const std::vector<std::vector<double>>& trainingData, 
                   const std::vector<std::vector<double>>& testData, 
                   const std::vector<int>& predictions);

    void display();
    void run();

private:
    static const int cellSize = 20;

    std::vector<std::vector<double>> trainingData;
    std::vector<std::vector<double>> testData;
    std::vector<int> predictions;

    std::vector<double> currentTrainingData;
    std::vector<double> currentTestData;
    int currentPrediction;

    void drawData(const std::vector<std::vector<double>>& data, int xOffset, int yOffset);
    void drawNumber(const std::vector<double>& number, int xStart, int yStart);
    void renderBitmapString(float x, float y, void *font, const char *string);
    static void displayCallback();
    void displayNumber(int number);
    
    static DataVisualizer* currentInstance;
};

#endif // DATA_VISUALIZER_H

