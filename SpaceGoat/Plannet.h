//
//  Plannet.h
//  SpaceGoat
//
//  Created by Stephen John Russell on 13/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef __SpaceGoat__Plannet__
#define __SpaceGoat__Plannet__

#include <iostream>
#include "GL/glew.h"
#include <GLUT/glut.h>
#include "BMPLoader.h"

class Plannet {
    
public:
    
    float x, y, z, dist;
    int yaw, pitch;
    BMPClass bmp1;
    GLuint texture_id_planet;
    
    Plannet();
    void setup();
    void draw();
    void setID(GLuint texture_id);
};

#endif /* defined(__SpaceGoat__Plannet__) */
