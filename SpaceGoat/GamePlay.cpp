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
    lyaw = 0;
    pitch = 0;
    lpitch = 0;
    roll = 0;
    speed = 0;
    dist = 0;
    tex_ind = 0;
    //intiKeyBools();
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
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glutIgnoreKeyRepeat(1);
    glEnable ( GL_TEXTURE_2D );
    GLuint *textures = new GLuint[2];
    glGenTextures(2, textures);
    
    ship.setID(texture_id[tex_ind++]);
    ship.setup();
    solar.setup();
}

float deg2rad(float d) {
    return d * M_PI / 180;
}

void GamePlay::update() {
    printf("yaw\t:%f\npitch\t:%f\nroll\t:%f\n",yaw, pitch, roll);
    if (keyStrokes['w'] == true || keyStrokes['W'] == true) {
        pitch -= 1;
    }
    if (keyStrokes['s'] == true || keyStrokes['S'] == true) {
        pitch += 1;
    }
    if (keyStrokes['a'] == true || keyStrokes['A'] == true) {
        yaw -= 1;
    }
    if (keyStrokes['d'] == true || keyStrokes['D'] == true) {
        yaw += 1;
    }
    if (keyStrokes['q'] == true || keyStrokes['Q'] == true) {
        roll -= 1;
    }
    if (keyStrokes['e'] == true || keyStrokes['E'] == true) {
        roll += 1;
    }
    if (keyStrokes['i'] == true || keyStrokes['I'] == true) {
        speed += 0.0001;
    }
    if (keyStrokes['k'] == true || keyStrokes['K'] == true) {
        speed -= 0.0001;
    }
//    if (pitch > 360) {
//        pitch = 0;
//    }
//    if (pitch < 0) {
//        pitch = 360;
//    }
//    if (yaw > 359) {
//        yaw = 0;
//    }
//    if (yaw < 1) {
//        yaw = 360;
//    }
    
    float dfo = sqrt((xPos * xPos) + (zPos * zPos));
    
    float xInc = (dfo + speed) * sin(deg2rad(yaw - lyaw));
    float yInc = (dfo + speed) * sin(deg2rad(pitch - lyaw));
    float zInc = (dfo + speed) * cos(deg2rad(yaw - lyaw));
    
    printf("x\t:%f\ny\t:%f\nz\t:%f\n",xInc, yInc, zInc);
//    
//    if (yaw > 90 && yaw < 270) {
//        zInc *= -1;
//    }
//    if (yaw < 180 || yaw > 275) {
//        xInc *= -1;
//    }
    
    xPos = xInc;
    yPos = yInc;
    zPos = zInc;
    
    lyaw = yaw;
    lpitch = pitch;
}

void GamePlay::intiKeyBools(){
    for (int i = 0; i < 256; i++) {
        keyStrokes[i] = false;
    }
}

void GamePlay::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
    glLoadIdentity();
    glPushMatrix();
    glRotatef(roll, 0, 0, 1);
    ship.draw();
    glPopMatrix();
    glPushMatrix();
    glLoadIdentity();
    glRotatef(yaw, 0, 1, 0);
    glRotatef(pitch, 1, 0, 0);
    glTranslatef(xPos, yPos, zPos);
    glPushMatrix();
    solar.draw();
    glPopMatrix();
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