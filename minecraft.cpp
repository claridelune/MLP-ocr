#include <GL/freeglut.h>
#include <vector>
#include <iostream>
#include "Perceptron.h"
#include "utils.h"
#include "DataVisualizer.h"
#include <vector>

const int rows = 6;
const int cols = 5;
const int totalBits = 30;
std::vector<bool> bits(totalBits, false);

std::vector<int> setup = {30, 10};
Perceptron ocr(setup);

std::vector<double> boolToDouble(std::vector<bool> b){
    int size = 30;
    std::vector<double> r;

    for (auto i : b) {
        r.push_back(i);
    }
    
    return r;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index = i * cols + j;
            bool bitValue = bits[index];

            if (bitValue) {
                glColor3f(1.0, 1.0, 1.0);  // Blanco para bits 1
            } else {
                glColor3f(0.0, 0.0, 0.0);  // Negro para bits 0
            }

            glRectf(j * (2.0 / cols) - 1.0, 1.0 - (i + 1) * (2.0 / rows),
                    (j + 1) * (2.0 / cols) - 1.0, 1.0 - i * (2.0 / rows));
        }
    }

    glFlush();
}

void printBits();  // Declaración anticipada

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convertir las coordenadas del ratón a las coordenadas de la cuadrícula
        float mouseX = (x / static_cast<float>(glutGet(GLUT_WINDOW_WIDTH))) * 2.0 - 1.0;
        float mouseY = 1.0 - (y / static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT))) * 2.0;

        int row = static_cast<int>((1.0 - mouseY) / (2.0 / rows));
        int col = static_cast<int>((mouseX + 1.0) / (2.0 / cols));

        int index = row * cols + col;
        if (index >= 0 && index < totalBits) {
            bits[index] = !bits[index];
            glutPostRedisplay(); // Actualizar la ventana
            printBits();
        }
    }
}

void printBits() {
    std::cout << "Bits: ";
    for (int i = 0; i < totalBits; i++) {
        std::cout << bits[i] << ",";
    }
    //AQUI ESTÁ LA MAGIA bits[]
    std::cout << std::endl;
    std::vector<double> test;
    test = boolToDouble(bits);

    ocr.feedForward(test);

    std::vector<double> resultvals;
    ocr.getOutput(resultvals);

    int predict = vectorToNumber(resultvals);
    std::cout << "predicted number: " << predict << std::endl;
}

int main(int argc, char** argv) {

    // std::vector<int> setup = {30, 10};
    std::vector<std::vector<double>> trainingData = readFile("training_data.txt");
    // std::vector<std::vector<double>> testData = readFile("test_data.txt");
    std::vector<int> trainingLabels = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // Entrenar la red
    for (int epoch = 0; epoch < 500; epoch++) {
        for (size_t i = 0; i < trainingData.size(); i++) {
            ocr.feedForward(trainingData[i]);
            ocr.backPropagation(targetToVector(trainingLabels[i%10]));
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 300); // Tamaño de la ventana
    glutCreateWindow("Minecraft");

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
