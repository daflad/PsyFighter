//
//  SpaceShip.cpp
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "SpaceShip.h"
#include "space_craft_001.h"

using namespace std;

GLuint checkError(const char *context)
{
    GLuint err = glGetError();
    if (err > 0 )  {
        std::cout << "0x" << std::hex << err << " glGetError() in " << context
        << std::endl;
    }
    return err;
}

SpaceShip::SpaceShip() {
    x = 0;
    y = 0;
    z = 0;
    dist = 0.2;
}

void SpaceShip::setup() {
    // set input data to arrays
    glVertexPointer(3, GL_FLOAT, 0, space_craft_001Verts);
    glNormalPointer(GL_FLOAT, 0, space_craft_001Normals);
    glTexCoordPointer(2, GL_FLOAT, 0, space_craft_001TexCoords);
    
    glEnable ( GL_TEXTURE_2D );
    glGenTextures(1, &texture_id);
    string fname = "/Users/stephenjohnrussell/dev/SpaceGoat/SpaceGoat/texture.bmp";
    BMPClass bmp;
	BMPLoad(fname,bmp);
    glBindTexture ( GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,3,bmp.width,bmp.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp.bytes);
}

void SpaceShip::draw() {
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, space_craft_001Verts);
    glNormalPointer(GL_FLOAT, 0, space_craft_001Normals);
    glTexCoordPointer(2, GL_FLOAT, 0, space_craft_001TexCoords);
    glScalef(dist, dist, dist);
    glTranslatef(0, -0.18, -1.15);
    glRotatef(3, 0, 1, 0);
    glRotatef(20, 1, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, space_craft_001NumVerts);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}