//
//  SolarSystem.h
//  SpaceGoat
//
//  Created by Stephen John Russell on 14/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef __SpaceGoat__SolarSystem__
#define __SpaceGoat__SolarSystem__

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "GL/glew.h"
#include <GLUT/glut.h>
#include "Plannet.hpp"

class SolarSystem {
    
public:
    
    int numPlannets;
    
    Plannet *plannets;

    SolarSystem();
    void setup();
    void draw();
    void setID(GLuint texture_id);
};

#endif /* defined(__SpaceGoat__SolarSystem__) */
