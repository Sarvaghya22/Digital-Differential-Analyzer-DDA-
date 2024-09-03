#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h> // Include GLUT header for text rendering

using namespace std;

vector<pair<float, float>> points;  // To store clicked points

void display();
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void drawLineWithPoints(float x1, float y1, float x2, float y2);
void renderBitmapString(float x, float y, void* font, const char* string);

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1000, 1000, "SARVAGHYA DEWANGAN- DDA ALGORITHM", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);

    // Initialize GLUT (needed for text rendering)
    int argc = 1;
    char* argv[1] = { (char*)"Something" };
    glutInit(&argc, argv);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);
    
    //draw grid
    
    glBegin(GL_LINES);
    glColor3f(126 / 255.0f, 128 / 255.0f, 145 / 255.0f);
    glLineWidth(2.0f);
    for (float i = 0.1;i < 2;i = i+ 0.1)
    {
        glVertex2f(-1+i, 1);
        glVertex2f(-1+i, -1);
        
    }
    for (float i = 0.1;i < 2;i = i + 0.1)
    {
        glVertex2f(-1, -1 + i);
        glVertex2f(1, -1 + i);
    }
    glEnd();
    glFlush();


    // Draw the crosshair in the middle
    
    glColor3f(0, 0, 0);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glEnd();
    glFlush();

    // Draw the line if there are exactly two points
    if (points.size() == 2) {
        drawLineWithPoints(points[0].first, points[0].second, points[1].first, points[1].second);
    }

    // Display the text using GLUT
    glColor3f(1, 0, 1);
    renderBitmapString(-0.95f, 0.95f, GLUT_BITMAP_TIMES_ROMAN_24, "Sarvaghya Dewangan");
    renderBitmapString(-0.95f, 0.85f, GLUT_BITMAP_TIMES_ROMAN_24, "500108582");
    
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Get the window size to normalize coordinates
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        // Convert GLFW coordinates to OpenGL coordinates
        float normX = (xpos / windowWidth) * 2.0f - 1.0f;
        float normY = 1.0f - (ypos / windowHeight) * 2.0f;

        // Store the point in the vector
        if (points.size() < 2) {
            points.push_back(make_pair(normX, normY));
        }
        else {
            points.clear();
            points.push_back(make_pair(normX, normY));
        }

        std::cout << "Clicked at (OpenGL coords): " << normX << ", " << normY << std::endl;

        // Redraw the scene to include the new point
        display();
    }
}

void drawLineWithPoints(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    int steps = max(abs(dx), abs(dy)) * 100;  // Increase steps for smoother line

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1;
    float y = y1;

    glColor3f(1.0f, 0.0f, 0.0f);  // Set color to red
    glPointSize(3.0f);            // Set point size

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2f(x, y);  // Plot the point
        x += xIncrement;   // Increment x by xIncrement
        y += yIncrement;   // Increment y by yIncrement
    }
    glEnd();
}

void renderBitmapString(float x, float y, void* font, const char* string) {
    glRasterPos2f(x, y); // Set position
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c); // Render character by character
    }
}
