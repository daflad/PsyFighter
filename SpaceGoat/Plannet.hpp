//
//  Plannet.h
//  SpaceGoat
//
//  Created by Stephen John Russell on 13/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef __SpaceGoat__Plannet__
#define __SpaceGoat__Plannet__

// C++ Libs
#include <iostream>
// OpenGL Libs
#include "GL/glew.h"
#include <GLUT/glut.h>
// Local headers
#include "BMPLoader.hpp"
#include <math.h>
class Plannet {
    
public:
    
    float x, y, z, s;
    float pos[4][4];

    BMPClass bmp1;
    GLuint texture_id_planet;
    
    Plannet();
    void setup();
    void draw();
    void setID(GLuint texture_id);
    void setLocation(int xx, int yy, int zz, float ss);
};

#endif /* defined(__SpaceGoat__Plannet__) */
