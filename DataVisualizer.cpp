#include "DataVisualizer.h"

DataVisualizer* DataVisualizer::currentInstance = nullptr;

DataVisualizer::DataVisualizer(const std::vector<std::vector<double>>& trainingData, 
                               const std::vector<std::vector<double>>& testData, 
                               const std::vector<int>& predictions)
    : trainingData(trainingData), testData(testData), predictions(predictions) {}

void DataVisualizer::display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawData({currentTrainingData}, 10, 50); 
    drawData({currentTestData}, 200, 50); 

    char str[20];
    sprintf(str, "Predicted: %d", currentPrediction);
    renderBitmapString(200 , 10, GLUT_BITMAP_9_BY_15, str);
    glutSwapBuffers();
}

void DataVisualizer::drawData(const std::vector<std::vector<double>>& data, int xOffset, int yOffset) {
    int y = yOffset;
    drawNumber(data[0], xOffset, y);
}

void DataVisualizer::run() {
    int argc = 0;
    char* argv[] = { (char*)"" };
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Data Visualizer");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 400, 0);

    glutDisplayFunc(displayCallback);

    currentInstance = this;

    int number;
    std::cout << "Enter number to visualize (0-9): ";
    std::cin >> number;
    
    if (number >= 0 && number <= 9) {
        displayNumber(number);
        glutMainLoop();
    } else {
        std::cout << "Invalid number." << std::endl;
    }
}

void DataVisualizer::drawNumber(const std::vector<double>& number, int xStart, int yStart) {
    // celdas
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 5; x++) {
            glColor3f(number[y * 5 + x] > 0 ? 1.0 : 0.0, 1.0, 1.0);  // Color basado en el valor
            glBegin(GL_QUADS);
            glVertex2f(xStart + x * cellSize, yStart + y * cellSize);
            glVertex2f(xStart + (x + 1) * cellSize, yStart + y * cellSize);
            glVertex2f(xStart + (x + 1) * cellSize, yStart + (y + 1) * cellSize);
            glVertex2f(xStart + x * cellSize, yStart + (y + 1) * cellSize);
            glEnd();
        }
    }

    //rayas
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i <= 6; i++) {
        glBegin(GL_LINES);
        // horizontales
        glVertex2f(xStart, yStart + i * cellSize);
        glVertex2f(xStart + 5 * cellSize, yStart + i * cellSize);
        // verticales
        if (i < 6) {
            glVertex2f(xStart + i * cellSize, yStart);
            glVertex2f(xStart + i * cellSize, yStart + 6 * cellSize);
        }
        glEnd();
    }
}

void DataVisualizer::renderBitmapString(float x, float y, void *font, const char *string) {
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void DataVisualizer::displayCallback() {
    currentInstance->display();
}

void DataVisualizer::displayNumber(int number) {
    currentTrainingData = trainingData[number];
    currentTestData = testData[number];
    currentPrediction = predictions[number];

    glutPostRedisplay();
}
