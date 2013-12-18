//
//  Boundry.cpp
//  SpaceGoat
//
//  Created by Stephen John Russell on 18/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "Boundry.hpp"
#include "BMPLoader.hpp"


using namespace std;

Boundry::Boundry() {
    x = 0;
    y = 0;
    z = 0;
    tubeZ = -1000;
    quad = gluNewQuadric();
}

void Boundry::setLocation(int xx, int yy, int zz) {
    x = xx;
    y = yy;
    z = zz;
}

void Boundry::setID(GLuint texture_id) {
    texture_id_bound = texture_id;
}

void Boundry::setup() {
    string fname = "/Users/stephenjohnrussell/dev/SpaceGoat/SpaceGoat/textures/box06.bmp";
    BMPClass bmp2;
    BMPLoad(fname,bmp2);
    gluQuadricTexture(quad, true);
    glBindTexture ( GL_TEXTURE_2D, texture_id_bound);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,3,bmp2.width,bmp2.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp2.bytes);
}

void Boundry::draw() {
    glPushMatrix();
    glRotatef(0, 1, 0, 0);
    glTranslatef(0, 0, tubeZ);
    glBindTexture ( GL_TEXTURE_2D, texture_id_bound);
    gluCylinder(quad, 10, 10, 1000, 10, 10);
    glPopMatrix();
}