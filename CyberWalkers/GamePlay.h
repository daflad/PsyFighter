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
#include <thread>
#include "space_craft_001.h"
#include "BMPLoader.h"
#include "camera.h"

class GamePlay {
public:
    
    BMPClass bmp;
    GLuint texture_id;
    float *lightDiffuse;
    float *lightSpecular;
    float *lightAmbient;
    float *lightPosition;
    
    void setup();
    void draw();
    void resize(int width, int height);
    void setupLights();
    void keyInput(unsigned char key, int x, int y);
};

#endif /* defined(__CyberWalkers__GamePlay__) */