//
//  main.cpp
//  pingPong
//Benjamin Gil Mendoza A01337094
//Andres Villavicencio A01420384
//  Created by Benjamin Gil on 8/23/16.
//  Copyright © 2016 Benjamin Gil. All rights reserved.
//

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined WIN32
#include "glew.h"
#include "freeglut.h"
#endif

#include <stdio.h>
/*
 ToDo: configure the blue paddle with the 'i' and 'k' keys.
 Then add and program the ball (it may be a square) so you can play.
 */

float c1x;
float c1y;
float c2x;
float c2y;
float paddleWidth;
float paddleHeight;
float ballx;
float bally;
float ball;
float speedX;
float speedY;


void init(void)
{
    c1x = -4.0f;
    c1y =  0.0f;
    c2x =  3.5f;
    c2y =  0.0f;
    
    speedX=0.02f;
    speedY=0.02f;
    
    ballx = 0.0f;
    bally =  0.0f;
    ball =  0.25f;
  
    
    paddleWidth = 0.25f;
    paddleHeight = 1.0f;
    
    // Select clearing color:
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
    // Initialize 2D viewing values:
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    /*
     Remember that for 3D mode (Perspective projection) we used:
     glMatrixMode(GL_MODELVIEW); // 3D Mode.
     glLoadIdentity(); // Reset.
     glViewport(0, 0, x, y); // Limits.
     gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Camera.
     */
    
    // Set Orthogonal projection parameters (left, right, bottom, top, zNear, zFar):
    glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
}




// Idle callback. Game logic here (score, math, AI):
void idle()
{
    if(ballx >3.5f){
        if(bally>=c2y && bally<=c2y+paddleHeight){
            speedX=speedX*-1;
            
        }
    }else if (ballx<-3.5f){
        if(bally>=c1y && bally<=c1y+paddleHeight){
            speedX=speedX*-1;
        }
    }
    if(bally >=4.8f){
        
            speedY=speedY*-1;
            
        
    }else if (bally<= -5.0f){
       speedY=speedY*-1;
    }
    
    
    
    glutPostRedisplay();
    
}

// Keyboard callback:
void keyboard(unsigned char c, int x, int y)
{
    switch (c)
    {
        case 'w':
            if (c1y < 4)
            {
                c1y += 0.3f;
            }
            break;
        case 's':
            if (c1y > -5)
            {
                c1y -= 0.3f;
            }
            break;
        case 'i':
            if (c2y < 4)
            {
                c2y += 0.3f;
            }
        break;
        case 'k':
            if (c2y > -5)
            {
                c2y -= 0.3f;
            }
        break;
    }
}

// Display callback:
void display(){
    
    // Clear pixels:
    glClear(GL_COLOR_BUFFER_BIT); // We're not using the depth buffer here.
    // When we used the depth buffer we had: glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Left (red) paddle:
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    {
        glVertex2f(c1x,               c1y				);
        glVertex2f(c1x + paddleWidth, c1y				);
        glVertex2f(c1x + paddleWidth, c1y + paddleHeight);
        glVertex2f(c1x,               c1y + paddleHeight);
    }
    glEnd();
    
    // Right (blue) paddle:
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    {
        glVertex2f(c2x,				  c2y				);
        glVertex2f(c2x + paddleWidth, c2y				);
        glVertex2f(c2x + paddleWidth, c2y + paddleHeight);
        glVertex2f(c2x,               c2y + paddleHeight);
    }
    glEnd();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    {
        
        glVertex2f(ballx,				  bally				);
        glVertex2f(ballx + ball, bally				);
        glVertex2f(ballx + ball, bally + ball);
        glVertex2f(ballx,               bally + ball);
    }
    glEnd();
    
    ballx+=speedX;
    bally+=speedY;
    
    glFlush(); // Single buffer! For 2 buffers we had: glutSwapBuffers();
   
    glutPostRedisplay();
}

/*
 Declare initial window size, position, and display mode
 (single buffer and RGB).  Open window with "PONG!"
 in its title bar.  Call initialization routines.
 Register callback function to display graphics.
 Enter main loop and process events.
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    // Using one buffer:
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // For 3D we had: glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("PONG!");
    init();
    
    // Register callbacks:
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    
    // Go!
    glutMainLoop();
    return 0;   // ANSI C requires main to return int.
}