//
//  GamePlay.cpp
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "GamePlay.hpp"

using namespace std;

GamePlay::GamePlay() {
    ship = SpaceShip();
    solar = SolarSystem();
    xPos = 0;
    yPos = 0;
    zPos = 0;
    yaw = 0;
    pitch = 0;
    dist = 0;
    tex_ind = 0;
}

void GamePlay::setup() {
    // call glewInit() to initialize the OpenGL extension entry points.
    GLenum err = glewInit();
    
    
    if (GLEW_OK != err) {
        // Lets hope ths doesn't happen!
        printf("Error: %s\n", glewGetErrorString(err));
        exit(0);
    }
    
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glEnable ( GL_TEXTURE_2D );
    GLuint *textures = new GLuint[2];
    glGenTextures(2, textures);
    ship.setID(texture_id[tex_ind++]);
    ship.setup();
    solar.setup();
}

/* Keyboard input processing routine */
void GamePlay::keyInput(unsigned char key, int x, int y) {
    switch(key) {
        // Press escape to exit.
        case 27:
            exit(0);
            break;
        case 119:
            yPos -= 0.1;
            break;
        case 115:
            yPos += 0.1;
            break;
        case 97:
            xPos += 0.1;
            break;
        case 100:
            xPos -= 0.1;
            break;
        case 113:
            zPos -= 1;
            break;
        case 101:
            zPos += 0.1;
            break;
        case 106:
            yaw -= 1;
            break;
        case 108:
            yaw += 1;
            break;
        case 39:
            //Nothing yet but will be go!! 39 = ' apostophie
            break;
        case 32:
            //Nothing yet but will be fire!! 32 = space
            break;
        default:
            break;
    }
}


void GamePlay::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
    glLoadIdentity();
    glPushMatrix();
    ship.draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(xPos, yPos, zPos);
    glRotatef(yaw, 0, 1, 0);
    glRotatef(pitch, 0, 0, 1);
    solar.draw();
    glPopMatrix();
    
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