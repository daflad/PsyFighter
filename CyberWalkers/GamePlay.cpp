//
//  GamePlay.cpp
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "GamePlay.h"

void GamePlay::setup(){
    // call glewInit() to initialize the OpenGL extension entry points.
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(0);
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
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
    std::string f = "/Users/stephenjohnrussell/dev/CyberWalkers/CyberWalkers/spaceship_panel_texture_by_dactilardesign-d4v9zb4.bmp";
    glEnable ( GL_TEXTURE_2D );
    glGenTextures (1, &texture_id);
	BMPLoad(f,bmp);
    glBindTexture ( GL_TEXTURE_2D, texture_id );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp.width,bmp.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp.bytes);
        // set input data to arrays
    glVertexPointer(3, GL_FLOAT, 0, space_craft_001Verts);
    glNormalPointer(GL_FLOAT, 0, space_craft_001Normals);
    glTexCoordPointer(2, GL_FLOAT, 0, space_craft_001TexCoords);
}

void GamePlay::setupLights() {
    lightDiffuse  = (float[]){ 1.0f, 1.0f, .5f, 1.0f };    // direct light
    lightSpecular = (float[]){ 1.0f, 1.0f, .5f, 1.0f };    // highlight
    lightAmbient  = (float[]){ .2f, .2f, .1f, 1.0f };  // scattered light
    lightPosition = (float[]){ -4.0f, 4.0f, 4.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,lightPosition);	// Position The Light
	glEnable(GL_LIGHT1);								// Enable Light One
}

/* Keyboard input processing routine */
void keyInput(unsigned char key, int x, int y)
{
    // What's that code again??
    printf("key : %c : %i\n", key, key);
    switch(key)
    {
            // Press escape to exit.
        case 27:
            exit(0);
            break;
        case 97:
            xPos -= 0.05;
            if (xPos < -1) {
                xPos = -1;
            }
            break;
        case 100:
            xPos += 0.05;
            if (xPos > 1) {
                xPos = 1;
            }
            break;
        case 119:
            yrot -= 0.01;
            //            if (yrot < 0) {
            //                yrot = 0;
            //            }
            break;
        case 32:
            shootPhazer();
            break;
        case 115:
            yrot += 0.01;
            //            if (yrot > 1) {
            //                yrot = 1;
            //            }
            break;
        default:
            break;
    }
    display();
}


void GamePlay::draw(){
    
}

void GamePlay::resize(int width, int height){
    
}