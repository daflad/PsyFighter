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
#include "BMPLoader.h"
#include "SpaceShipObject.h"

class SpaceShip {

public:

    float x, y, z, ;
    
    BMPClass bmp;
    GLuint texture_id;
    
    SpaceShip();
    void setup();
    void draw();    
};

#endif /* defined(__CyberWalkers__SpaceShip__) */
