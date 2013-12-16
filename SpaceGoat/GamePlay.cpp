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
    lx = 0;
    lz = 0;
    ly = 0;
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
    gluPerspective(90.0f, GLfloat(1280)/GLfloat(800), 0.1f, 100.0f);
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
    printf("speed\t:%f\nyaw\t:%f\npitch\t:%f\nroll\t:%f\n\n",speed,yaw, pitch, roll);
    if (keyStrokes['w'] == true || keyStrokes['W'] == true) {
        pitch -= 0.5;
        ship.pitch -= speed;
    } else {
        if (ship.pitch > 0) {
            ship.pitch -= speed;
        }
    }
    if (keyStrokes['s'] == true || keyStrokes['S'] == true) {
        pitch += 0.5;
        ship.pitch += speed;
    } else {
        if (ship.pitch < 0) {
            ship.pitch += speed;
        }
    }
    if (keyStrokes['a'] == true || keyStrokes['A'] == true) {
        yaw -= 0.5;
        ship.roll += speed;
    } else {
        if (ship.roll > 0) {
            ship.roll -= speed;
        }
    }
    if (keyStrokes['d'] == true || keyStrokes['D'] == true) {
        yaw += 0.5;
        ship.roll -= speed;
    } else {
        if (ship.roll < 0) {
            ship.roll += speed;
        }
    }
    if (keyStrokes['q'] == true || keyStrokes['Q'] == true) {
        roll -= 0.5;
    }
    if (keyStrokes['e'] == true || keyStrokes['E'] == true) {
        roll += 0.5;
    }
    if (keyStrokes['i'] == true || keyStrokes['I'] == true) {
        speed += 0.0001;
    }
    if (keyStrokes['k'] == true || keyStrokes['K'] == true) {
        speed -= 0.0001;
    }
    
    lx = sin(deg2rad(yaw));
    lz = -cos(deg2rad(yaw));
    ly = sin(deg2rad(pitch));
    
    xPos += lx * speed;
    yPos += ly * speed;
    zPos += lz * speed;
}

void GamePlay::intiKeyBools(){
    for (int i = 0; i < 256; i++) {
        keyStrokes[i] = false;
    }
}

void GamePlay::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    ship.draw();
    glPopMatrix();
    glPushMatrix();
    gluLookAt(	xPos, yPos, zPos, xPos+lx, yPos+ly,  zPos+lz, 0.0f, 1.0f,  0.0f);
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