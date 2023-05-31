#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

void draw_pixel(float x, float y)
{
    glBegin(GL_QUADS);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
}

void draw_circle(float x, float y, float r)
{
    for(int i = -r; i<r; i++){
        for(int j = -sqrt(r*r - i*i); j<sqrt(r*r - i*i); j++){
            draw_pixel(x+j,y+i);
        }
    }
}

void init() 
{
    glClearColor(0, 0, 0, 0);
}

void draw_line(int x1, int y1, int x2, int y2)
{
    // Sorts points so that point 1 is on the left
    if(x1 > x2){
        swap(x1,x2);
        swap(y1,y2);
    }

    // Transforms points so that the line has 0 <= slope <= 1
    bool negative_slope = (float)(y2-y1)/(x2-x1) < 0;
    if(negative_slope)
    {
        y1 = -y1;
        y2 = -y2;
    }

    bool greater_than_one = (float)(y2-y1)/(x2-x1) > 1;
    if(greater_than_one)
    {
        swap(x1,y1);
        swap(x2,y2);
    }

    // Line Algorithm data
    float dx = x2 - x1;
    float dy = y2 - y1;
    float B = y1 - x1*(dy/dx);

    float a = dy;
    float b = -dx;
    float c = B*dx;

    // Starts drawing line at (x1,y1)
    int y = y1;
    for(int x = x1; x <= x2; x++)
    {
        // Transforms points back to their original position
        float xt = x;
        float yt = y;
        if(greater_than_one) swap(xt,yt);
        if(negative_slope) yt = -yt;

        // Draws pixel
        draw_pixel(xt,yt);

        // Decision variable
        float d = a*(x+1) + b*(y+.5) + c;

        // Chooses next pixel (NE or E);
        if(d > 0)
        {
            y = y + 1;
        }
    }
}

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Defines P1
    int x1 = -100;
    int y1 = -50;

    // Draws a red circle on P1
    glColor3f(1,0,0);
    draw_circle(x1,y1,5);

    // Defines P2
    int x2 = 200;
    int y2 = -100;

    // Draws a blue circle on P2
    glColor3f(0,0,1);
    draw_circle(x2,y2,5);

    // Draws a green line
    glColor3f(0,1,0);
    draw_line(x1,y1,x2,y2);

    glFlush();
}

void resize_window_to_screen(GLsizei screen_width, GLsizei screen_height) 
{
    // Defines viewport
    glViewport(0, 0, screen_width, screen_height);

    // Initializes system coordinates
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Sets window coordinates so (0,0) is its center and it has the same size as the screen
    gluOrtho2D(-screen_width/2.0, screen_width/2.0, -screen_height/2.0, screen_height/2.0);
}

int main(int argc, char **argv) 
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(10, 50);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Bresenham's Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(resize_window_to_screen);
    glutMainLoop();
}
