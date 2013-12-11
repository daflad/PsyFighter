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

class SpaceShip {

public:

    static float x, y, z, dist;
    
    BMPClass bmp;
    static GLuint texture_id;
    
    static unsigned int SpaceShipObjectNumVerts;

    static float *SpaceShipObjectVerts;
    static float *SpaceShipObjectNormals;
    static float *SpaceShipObjectTexCoords;
    
    SpaceShip();
    void init(float *verts, float *norms, float *texts, unsigned int numV);
    void setup();
    static void draw();
    
};

#endif /* defined(__CyberWalkers__SpaceShip__) */
