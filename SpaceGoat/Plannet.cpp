//
//  Planet.cpp
//  SpaceGoat
//
//  Created by Stephen John Russell on 13/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "Plannet.hpp"
#include "astroid_001.hpp"


using namespace std;

Plannet::Plannet() {
    x = 0;
    y = 0;
    z = 0;
    s = rand() % 10;
}

void Plannet::setLocation(int xx, int yy, int zz) {
    x = xx;
    y = yy;
    z = zz;
}

void Plannet::setID(GLuint texture_id) {
    texture_id_planet = texture_id;
}

void Plannet::setup() {
    // set input data to arrays
//    
//    glVertexPointer(3, GL_FLOAT, 0, v_quads_g);
//    glTexCoordPointer(2, GL_FLOAT, 0, vt_quads_g);
//    glNormalPointer(GL_FLOAT, 0, vn_quads_g);
    
//    int pli = rand() % 8;
    string fname = "/Users/stephenjohnrussell/dev/SpaceGoat/SpaceGoat/textures/world08.bmp";
	BMPLoad(fname,bmp1);
    glBindTexture ( GL_TEXTURE_2D, texture_id_planet);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_MIPMAP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_MIPMAP);
    gluBuild2DMipmaps(GL_TEXTURE_2D,3,bmp1.width,bmp1.height,GL_RGB, GL_UNSIGNED_BYTE,bmp1.bytes);
}

void Plannet::draw() {
    glPushMatrix();
    glTranslatef(x, y, z);
    
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, v_quads_a);
    glTexCoordPointer(2, GL_FLOAT, 0, vt_quads_a);
    glNormalPointer(GL_FLOAT, 0, vn_quads_a);

    glBindTexture ( GL_TEXTURE_2D, texture_id_planet);
    glScalef(s, s, s);
    glDrawArrays(GL_QUADS, 0, 304);
//    GLUquadricObj* Sphere = gluNewQuadric();
//    gluQuadricNormals(Sphere, GLU_SMOOTH);
//    gluQuadricTexture(Sphere, GL_TRUE);
//    gluSphere(Sphere,1,10,10);
//    gluDeleteQuadric(Sphere);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    
    glPopMatrix();
}