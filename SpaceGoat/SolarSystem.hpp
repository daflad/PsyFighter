//
//  SolarSystem.h
//  SpaceGoat
//
//  Created by Stephen John Russell on 14/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef __SpaceGoat__SolarSystem__
#define __SpaceGoat__SolarSystem__

// C++ Libs
#include <iostream>
#include <vector>

#include "GL/glew.h"
#include <GLUT/glut.h>
#include "Plannet.hpp"
#include "Boundry.hpp"

using namespace std;

class SolarSystem {
    
public:
    
    int numPlannets;
    float tubeZ;
    
    vector<Plannet> plannets;
    Boundry bound;
    GLuint textures;
    GLuint st;
    
    SolarSystem();
    void setup();
    void draw();
    void setID(GLuint texture_id);
    bool collisionDetection(float xPos, float yPos, float zPos);
    void make_plannets(int start);
};

#endif /* defined(__SpaceGoat__SolarSystem__) */
