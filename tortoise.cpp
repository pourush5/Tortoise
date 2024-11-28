#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

float tortoiseX = 200.0f;
float tortoiseY = 150.0f;
float tortoiseAngle = 0.0f;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void bresenhamLine(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int sx = (dx > 0) ? 1 : -1;
    int sy = (dy > 0) ? 1 : -1;
    dx = abs(dx);
    dy = abs(dy);

    if (dx > dy) {
        int err = dx / 2;
        while (x0 != x1) {
            drawPixel(x0, y0);
            err -= dy;
            if (err < 0) {
                y0 += sy;
                err += dx;
            }
            x0 += sx;
        }
    } else {
        int err = dy / 2;
        while (y0 != y1) {
            drawPixel(x0, y0);
            err -= dx;
            if (err < 0) {
                x0 += sx;
                err += dy;
            }
            y0 += sy;
        }
    }
    drawPixel(x1, y1);
}

void drawtortoise() {
    glBegin(GL_TRIANGLES);
    glVertex2f(tortoiseX, tortoiseY);
    glVertex2f(tortoiseX - 5, tortoiseY - 10);
    glVertex2f(tortoiseX + 5, tortoiseY - 10);
    glEnd();
}

void moveForward(float distance) {
    float rad = tortoiseAngle * (M_PI / 180.0f);
    float newX = tortoiseX + distance * cos(rad);
    float newY = tortoiseY + distance * sin(rad);
    bresenhamLine(tortoiseX, tortoiseY, newX, newY);
    tortoiseX = newX;
    tortoiseY = newY;
}

void turn(float angle) {
    tortoiseAngle += angle;
    tortoiseAngle = fmod(tortoiseAngle, 360.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    bresenhamLine(10, 10, 200, 150);
    drawtortoise();

    glFlush();
}
void renderBitmapString(float x, float y, void *font, const char *string) {
    glRasterPos2f(x, y);
    while (*string) {
        glutBitmapCharacter(font, *string);
        string++;
    }
}
void displaySecondWindow() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);
    glVertex2f(100, 100);
    glVertex2f(300, 100);
    glVertex2f(300, 200);
    glVertex2f(100, 200);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    renderBitmapString(110, 150, GLUT_BITMAP_HELVETICA_18, "Instructions:");
    renderBitmapString(110, 130, GLUT_BITMAP_HELVETICA_18, "Press 'w' to move forward, 's' to move backward");
    renderBitmapString(110, 120, GLUT_BITMAP_HELVETICA_18, "Press 'a' to rotate left, 'd' to rotate right");
    renderBitmapString(110, 110, GLUT_BITMAP_HELVETICA_18, "Press 'r' to reset position ");

    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            moveForward(10.0f);
            break;
        case 's':
            moveForward(-10.0f);
            break;
        case 'a':
            turn(-15.0f);
            break;
        case 'd':
            turn(15.0f);
            break;
        case 'r':
            tortoiseX = 200.0f;
            tortoiseY = 150.0f;
            tortoiseAngle = 0.0f;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("tortoise Cursor");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(500, 100);
    int secondWindow = glutCreateWindow("Second Window");
    init();
    glutDisplayFunc(displaySecondWindow);
    glutMainLoop();
    return 0;
}
