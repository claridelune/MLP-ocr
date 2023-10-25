#include <GL/freeglut.h>
#include <vector>
#include <iostream>

const int rows = 6;
const int cols = 5;
const int totalBits = 30;
std::vector<bool> bits(totalBits, false);

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
        std::cout << bits[i];
    }
    //AQUI ESTÁ LA MAGIA bits[]
    std::cout << std::endl;
}

int main(int argc, char** argv) {
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
