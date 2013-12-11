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
#include "BMPLoader.h"
#include "camera.h"
#include "SpaceShip.h"
#include "LazerShot.h"

class GamePlay {
public:
    
    float *lightDiffuse;
    float *lightSpecular;
    float *lightAmbient;
    float *lightPosition;
    
    SpaceShip ship;
    
    GamePlay(unsigned int numV, float *ssInit[]);
    static void draw(void);
    void resize(int w, int h);
    void setup(void);
    void updateScene(int value);
    static void keyInput(unsigned char key, int x, int y);
    void setupLights();
};

#endif /* defined(__CyberWalkers__GamePlay__) */
