//
//  WindowingSystem.cpp
//  CyberWalkers
//
//  Created by Stephen Russell on 09/10/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

/*
 *      We will use this template for all OpenGL examples in ICP3036
 *
 *      The main GLUT routine is set up here
 */
#include "WindowingSystem.h"		// Header File For WindowingSystem.cpp
#include <GLUT/glut.h>

// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main(int argc, char **argv)
{
    // Initialize GLUT.
    glutInit(&argc, argv);
    
    // Set display mode with an RGB colour buffer, double buffering and a depth buffer..
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    
    // Set OpenGL window size
    glutInitWindowSize(640, 480);
    
    // Set position of OpenGL window upper-left corner
    glutInitWindowPosition(100, 100);
    
    // Create OpenGL window with title
    glutCreateWindow("ICP3036 OpenGL Template");
    
    // Initialize
    setup();
    
    // Register display routine
    glutDisplayFunc(drawScene);
    
    // Register reshape routine
    glutReshapeFunc(resize);
    
    // Register keyboard routine
    glutKeyboardFunc(keyInput);
    
    // Begin processing
    glutMainLoop();
    
    return 0;  
}