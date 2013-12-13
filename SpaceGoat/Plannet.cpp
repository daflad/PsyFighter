//
//  Planet.cpp
//  SpaceGoat
//
//  Created by Stephen John Russell on 13/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "Plannet.h"
#include "globe.h"


using namespace std;

Plannet::Plannet() {
    x = 0;
    y = 0;
    z = 0;
    yaw = 0;
    pitch = 0;
    dist = 1;
}

void Plannet::setID(GLuint texture_id) {
    texture_id_planet = texture_id;
}

void Plannet::setup() {
    // set input data to arrays
    
    glVertexPointer(3, GL_FLOAT, 0, v_quads_g);
    glTexCoordPointer(2, GL_FLOAT, 0, vt_quads_g);
    glNormalPointer(GL_FLOAT, 0, vn_quads_g);
    
    string fname = "/Users/stephenjohnrussell/dev/SpaceGoat/SpaceGoat/world00.bmp";
	BMPLoad(fname,bmp1);
    glBindTexture ( GL_TEXTURE_2D, texture_id_planet);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_SPHERE_MAP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_SPHERE_MAP);
    glTexImage2D(GL_TEXTURE_2D,0,3,bmp1.width,bmp1.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp1.bytes);
}

void Plannet::draw() {
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v_quads_g);
    glTexCoordPointer(2, GL_FLOAT, 0, vt_quads_g);
    glNormalPointer(GL_FLOAT, 0, vn_quads_g);
    glDrawArrays(GL_QUADS, 0, 1440);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}