//
//  Boundry.h
//  SpaceGoat
//
//  Created by Stephen John Russell on 18/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef __SpaceGoat__Boundry__
#define __SpaceGoat__Boundry__

#include <iostream>
#include "GL/glew.h"
#include <GLUT/glut.h>

class Boundry {
    
public:
    
    float x, y, z;
    int tubeZ;
    GLuint texture_id_bound;
    GLUquadric *quad;
    
    Boundry();
    void setup();
    void draw();
    void setID(GLuint texture_id);
    void setLocation(int xx, int yy, int zz);
};

#endif /* defined(__SpaceGoat__Boundry__) */
