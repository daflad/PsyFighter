//
//  SpaceShip.h
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef __CyberWalkers__SpaceShip__
#define __CyberWalkers__SpaceShip__

#include <iostream>
#include "GL/glew.h"
#include <GLUT/glut.h>
#include "BMPLoader.hpp"
#include <vector>

using namespace std;

class SpaceShip {

public:

    float x, y, z, dist, speed;
    
    float yaw, pitch, roll;
    GLuint texture_id_ship;
    BMPClass bmp;
    SpaceShip();
    void setup(float xPos, float yPos, float zPos);
    void draw();
    void setID(GLuint texture_id);
    
    
};

#endif /* defined(__CyberWalkers__SpaceShip__) */
