//
//  GamePlay.h
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef __CyberWalkers__GamePlay__
#define __CyberWalkers__GamePlay__

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "GL/glew.h"
#include <GLUT/glut.h>
#include "SpaceShip.hpp"
#include "Plannet.hpp"
#include "SolarSystem.hpp"

class GamePlay {
public:
    
    float *lightDiffuse;
    float *lightSpecular;
    float *lightAmbient;
    float *lightPosition;
    
    float xPos, yPos, zPos, dist, yaw, lyaw, pitch, lpitch, roll, speed;
    bool keyStrokes[256];
    
    SpaceShip ship;
    SolarSystem solar;
    
    GLuint texture_id[2];
    GLuint tex_ind;
    
    GamePlay();
    
    void draw();
    void resize(int w, int h);
    void setup();
    void update();
    void updateScene(int value);
    void keyInput(unsigned char key, int x, int y);
    void setupLights();
    void intiKeyBools();
    void keyDown(unsigned char key, int x, int y);
    void keyUp(unsigned char key, int x, int y);
};

#endif /* defined(__CyberWalkers__GamePlay__) */
