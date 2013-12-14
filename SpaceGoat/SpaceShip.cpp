//
//  SpaceShip.cpp
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "SpaceShip.hpp"
#include "space_craft_001.hpp"


using namespace std;

SpaceShip::SpaceShip() {
    x = 0;
    y = 0;
    z = -0.2;
    yaw = 0;
    pitch = 0;
    dist = 1;
}

void SpaceShip::setID(GLuint texture_id) {
    texture_id_ship = texture_id;
}

void SpaceShip::setup() {
    string fname = "/Users/stephenjohnrussell/dev/SpaceGoat/SpaceGoat/textures/texture.bmp";
	BMPLoad(fname,bmp);
}

void SpaceShip::draw() {
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v_quads_s);
    glNormalPointer(GL_FLOAT, 0, vn_quads_s);
    glTexCoordPointer(2, GL_FLOAT, 0, vt_quads_s);
    glBindTexture ( GL_TEXTURE_2D, texture_id_ship);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,bmp.width,bmp.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp.bytes);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.width, bmp.height, GL_RGB, GL_UNSIGNED_BYTE, bmp.bytes);
    glTranslatef(x, y, z);
    glRotatef(yaw, 0, 0, 1);
    glRotatef(pitch, 1, 0, 0);
    glRotatef(3, 0, 1, 0);
    glScalef(dist, dist, dist);
    glDrawArrays(GL_QUADS, 0, 1696);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}