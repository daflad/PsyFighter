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
    ship = *new SpaceShip();
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
    glClearDepth(10.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    ship.setup();
}

/* Keyboard input processing routine */
void GamePlay::keyInput(unsigned char key, int x, int y) {
    switch(key) {
        // Press escape to exit.
        case 27:
            exit(0);
            break;
        case 119:
            ship.y -= 0.01;
            printf("dist:%f\n",ship.dist);
            break;
        case 115:
            ship.y += 0.01;
            printf("dist:%f\n",ship.dist);
            break;
        case 97:
            ship.x -= 0.01;
            printf("dist:%f\n",ship.dist);
            break;
        case 100:
            ship.x += 0.01;
            printf("dist:%f\n",ship.dist);
            break;
        case 113:
            ship.z -= 0.01;
            printf("dist:%f\n",ship.dist);
            break;
        case 101:
            ship.z += 0.01;
            printf("dist:%f\n",ship.dist);
            break;
        case 122:
            ship.dist -= 0.01;
            if (ship.dist < 0) {
                ship.dist = 0.001;
            }
            printf("dist:%f\n",ship.dist);
            break;
        case 120:
            ship.dist += 0.01;
            printf("dist:%f\n",ship.dist);
            break;
        case 106:
            ship.yaw--;
            printf("dist:%f\n",ship.dist);
            break;
        case 108:
            ship.yaw++;
            printf("dist:%f\n",ship.dist);
            break;
        case 105:
            ship.pitch--;
            printf("dist:%f\n",ship.dist);
            break;
        case 107:
            ship.pitch++;
            printf("dist:%f\n",ship.dist);
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