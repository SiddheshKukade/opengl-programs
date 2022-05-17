
//GlReadPixels method : 
    // void glReadPixels(  GLint x,
    //     GLint y,
    //     GLsizei width,
    //     GLsizei height,
    //     GLenum format,
    //     GLenum type,
    //     void * data);
    // glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
//Parameters
    // x, y
    // Specify the window coordinates of the first pixel that is read from the frame buffer. 
    //This location is the lower left corner of a rectangular block of pixels.

    // width, height
    // Specify the dimensions of the pixel rectangle. width and height of one correspond to a single pixel.

    // format
    // Specifies the format of the pixel data. The following symbolic values are accepted: GL_ALPHA, GL_RGB, and GL_RGBA.

    // type
    // Specifies the data type of the pixel data. Must be one of GL_UNSIGNED_BYTE, 
    //GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, or GL_UNSIGNED_SHORT_5_5_5_1.

    // data
    // Returns the pixel data.
#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;

void init(){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,640,0,480);
}
// Algorithm to fill boundary of object.
void boundary_fill(int x, int y, float* fillColor, float* bc){
    //receives x y and fill color and background color
    float color[3]; // to store r ,g ,b values
    //Description. glReadPixels and glReadnPixels return pixel data from the frame buffer, 
    //starting with the pixel whose lower left corner is at location ( x , y ), into client memory starting at location data 
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
        // void glReadPixels(  GLint x,
    //     GLint y,
    //     GLsizei width,
    //     GLsizei height,
    //     GLenum format,
    //     GLenum type,
    //     void * data);
    //glReadPixels will load the values of rgb in 'color' array.
    if((color[0]!=bc[0] || color[1]!=bc[1] || color[2]!=bc[2])&&(color[0]!=fillColor[0] || color[1]!=fillColor[1] || color[2]!=fillColor[2]))
    { // just checking that the color is neither background nor fillColor (Meaning the pixel is already colorred ) 
        glColor3f(fillColor[0],fillColor[1],fillColor[2]);
        //setting the color and plotting the points
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        // using flush to make that all methods get executed 
        glFlush();
        //applying the method on 4 corresponding points  top ,left ,down ,right providing same fillColor and background color
        boundary_fill(x+1,y,fillColor,bc); // 
        boundary_fill(x-1,y,fillColor,bc);
        boundary_fill(x,y+1,fillColor,bc);
        boundary_fill(x,y-1,fillColor,bc);
    }   
}
// Algorithm to for flood filling
void floodFill(int x,int y,float* fillColor, float* bc ) {
    //same process explained above
        float color[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
//checkig that the color is not fillColor
    if(color[0]!=fillColor[0] || color[1]!=fillColor[1] || color[2]!=fillColor[2])
    {
        // setPixel(x,y);
                glColor3f(fillColor[0],fillColor[1],fillColor[2]);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        floodFill(x+1,y,fillColor,bc);
        floodFill(x,y+1,fillColor,bc);
        floodFill(x-1,y,fillColor,bc);
        floodFill(x,y-1,fillColor,bc);
        glFlush();
    }
}

// Mouse Interfacing
void mouse(int btn, int state, int x, int y){ 
//btn - on which button event occur (GETS THE CURRENT PRESSED MOUSE BUTTON)
//ALSO RECEIVES THE X Y COR-ORDINATES OF THE CURSOR AND THE STATE STATING IF THE CLICK IS PRESSED HOLD OR LEAVED THE CLICK
     y = 480-y;                                      // x and y used to read pixel from mouse
    if(btn==GLUT_LEFT_BUTTON) //if left button id pressed and after holding the click is leaved 
    {
        if(state==GLUT_DOWN)   
        {
            float bCol[] = {1,0,0};  //red color BOUNDARY
            float color[] = {0,0,1}; //filling color blue COLOR-TO-FILL
            boundary_fill(x,y,color,bCol); //calling boundary fill function
        }
    }
    if((btn==GLUT_RIGHT_BUTTON)&&(state==GLUT_DOWN)) // if right button id pressed and after holding the click is leaved 
       {
                 float back[] = {1,0,0}; // BACKGROUND COLOR 
                 float colorflood[] = {0,1,0}; // COLOR TO FILL
                floodFill(x,y,back,colorflood);
       }
}
void Triangle(){
    // sets the proper line wsith and draws a triangle
    glLineWidth(3); // mention line width
    glPointSize(2); // mention pointsize
    glClear(GL_COLOR_BUFFER_BIT); // clear the color buffer
    glColor3f(1,0,0); // draw triangle with red color
    glBegin(GL_LINE_LOOP);
        glVertex2i(150,100); 
        glVertex2i(300,300);
        glVertex2i(450,100);
    glEnd();
    glFlush();
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Boundary Filling Algorithm");
    //drawing the triangle and then calling the mouse functions to start the polygon filling process 
    glutDisplayFunc(Triangle); //callback function
    glutMouseFunc(mouse); //callback function
    init();
    glutMainLoop();
    return 0;
}
