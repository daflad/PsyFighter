//
//  GamePlay.cpp
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "GamePlay.h"

using namespace std;

void GamePlay::setup() {
    // call glewInit() to initialize the OpenGL extension entry points.
    GLenum err = glewInit();
    
    if (GLEW_OK != err) {
        // Lets hope ths doesn't happen!
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(0);
    }
    
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    // Enable Light

    //   glutTimerFunc(TIMERDELAY, updateScene, 0);
    glDepthRange(0, 100);
    //glutKeyboardFunc(keyInput);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// Type of depth testing to do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
}

void GamePlay::setupLights() {
    // Define light parameters
    lightDiffuse  = (float[]) {  1.0f,  1.0f,   .5f,  1.0f };   // direct light
    lightSpecular = (float[]) {  1.0f,  1.0f,   .5f,  1.0f };   // highlight
    lightAmbient  = (float[]) {   .2f,   .2f,   .1f,  1.0f };   // scattered light
    lightPosition = (float[]) { -4.0f,  4.0f,  4.0f,  1.0f };
    // Apply to scene
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,lightPosition);
    // Not forgetting to activate
	glEnable(GL_LIGHT1);
}

/* Keyboard input processing routine */
void keyInput(unsigned char key, int x, int y)
{
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


void GamePlay::draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
    
    
    
    
    
    glutSwapBuffers();      //swaps the front and back buffers

}

void GamePlay::resize(int width, int height){
    
}