//
//  GamePlay.cpp
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "GamePlay.h"

using namespace std;

GamePlay::GamePlay() {
    
}

void GamePlay::setup(unsigned int numV, float *ssInit[]) {
    // call glewInit() to initialize the OpenGL extension entry points.
    GLenum err = glewInit();
    
    if (GLEW_OK != err) {
        // Lets hope ths doesn't happen!
        printf("Error: %s\n", glewGetErrorString(err));
        exit(0);
    }
    
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    //glutKeyboardFunc(keyInput);
    
    glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    setupLights();
    ship.setup(ssInit[0], ssInit[1], ssInit[3], numV);
}

void GamePlay::setupLights() {
    
    // Define light parameters
    lightDiffuse  = (float[]) {  1.0f,  1.0f,   .5f,  1.0f };
    lightSpecular = (float[]) {  1.0f,  1.0f,   .5f,  1.0f };
    lightAmbient  = (float[]) {   .2f,   .2f,   .1f,  1.0f };
    lightPosition = (float[]) { -4.0f,  4.0f,  4.0f,  1.0f };
    
    // Apply to scene
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,lightPosition);
    
    // Not forgetting to activate
	glEnable(GL_LIGHT1);
}

/* Keyboard input processing routine */
void GamePlay::keyInput(unsigned char key, int x, int y) {
//    // What's that code again??
//    printf("key : %c : %i\n", key, key);
//    switch(key)
//    {
//            // Press escape to exit.
//        case 27:
//            exit(0);
//            break;
//        case 97:
//            xPos -= 0.05;
//            if (xPos < -1) {
//                xPos = -1;
//            }
//            break;
//        case 100:
//            xPos += 0.05;
//            if (xPos > 1) {
//                xPos = 1;
//            }
//            break;
//        case 119:
//            yrot -= 0.01;
//            //            if (yrot < 0) {
//            //                yrot = 0;
//            //            }
//            break;
//        case 32:
//            shootPhazer();
//            break;
//        case 115:
//            yrot += 0.01;
//            //            if (yrot > 1) {
//            //                yrot = 1;
//            //            }
//            break;
//        default:
//            break;
//    }
//    display();
}


void GamePlay::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
    
    ship.draw();
    
    glutSwapBuffers();

}

void GamePlay::resize(int width, int height) {
    if(height == 0)
		height = 1;
    
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	gluPerspective(45.0f, GLfloat(width)/GLfloat(height), 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}