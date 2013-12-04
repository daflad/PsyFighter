//
//  GluQuadsView.cpp
//  CyberWalkers
//
//  Created by Stephen Russell on 09/10/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "GluQuadsView.h"
#include "main.h"
#include <GLUT/glut.h>


void display()
{
    
    float red   = 0.0f;
    float green = 0.8f;
    float blue  = 0.0f;
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(red, green, blue);
    
    
    //This produces a line style sphere:
    GLUquadric *quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_LINE);
    gluSphere(quad,  1.0,  15,  15);
    gluDeleteQuadric(quad);
    
    glColor3f(red, green, blue);
    
    // Notice that the three squares are
    // exactly the same size, but are drawn at
    // different distances from the screen
    glBegin(GL_QUADS);
    
    //1st Plane
    glVertex3i(0, 30, 30);
    glVertex3i(10, 30, 30);
    glVertex3i(10, 20, 30);
    glVertex3i(0, 20, 30);
    
    //2nd Plane
    glVertex3i(20, 20, 37);
    glVertex3i(30, 20, 37);
    glVertex3i(30, 10, 37);
    glVertex3i(20, 10, 37);
    
    //3rd Plane
    glVertex3i(40, 10, 45);
    glVertex3i(50, 10, 45);
    glVertex3i(50, 0, 45);
    glVertex3i(40, 0, 45);
    
    glEnd();
}

void setup() {
    
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// Type of depth testing to do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
}

void resize(int width, int height)
{
    
	if (height==0)										// Prevent a divide by zero by
	{										            // making height equal one
		height=1;
	}
    
	glViewport(0,0,(GLsizei)width,(GLsizei)height);		// Set viewport size to be entire OpenGL window
    
	glMatrixMode(GL_PROJECTION);						// Select the Projection Matrix
	glLoadIdentity();									// Reset the Projection Matrix
    
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
    
	glMatrixMode(GL_MODELVIEW);							// Select the Modelview Matrix
	glLoadIdentity();									// Reset the Modelview Matrix
}

void keyInput(unsigned char key, int x, int y)
{
    printf ("Key: %c", key);
    switch(key)
    {
            // Press escape to exit.
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}
