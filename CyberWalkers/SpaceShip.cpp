//
//  SpaceShip.cpp
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "SpaceShip.h"

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
    dist = 1;
}

void SpaceShip::setup(float *verts, float *norms, float *texts, unsigned int numV) {
    SpaceShipObjectNumVerts = numV;
    std::string f = "/Users/stephenjohnrussell/dev/CyberWalkers/CyberWalkers/spaceship.bmp";
    glEnable ( GL_TEXTURE_2D );
//    glEnableClientState(GL_NORMAL_ARRAY);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//    glEnableClientState(GL_VERTEX_ARRAY);
    glGenTextures (1, &texture_id);
	BMPLoad(f, bmp);
    glBindTexture ( GL_TEXTURE_2D, texture_id );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,bmp.width,bmp.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp.bytes);
    // set input data to arrays
    glVertexPointer(3, GL_FLOAT, 0, verts);
    glNormalPointer(GL_FLOAT, 0, norms);
    glTexCoordPointer(2, GL_FLOAT, 0, texts);
}

void SpaceShip::draw() {
    
    
    // enble vertex arrays
    // draw data
    

    //glVertexPointer(3, GL_FLOAT, 0, SpaceShipObjectVerts);
    //glNormalPointer(GL_FLOAT, 0, SpaceShipObjectNormals);
    //glTexCoordPointer(2, GL_FLOAT, 0, SpaceShipObjectTexCoords);
    
    glPushMatrix();
    glScalef(dist, dist, dist);
    glTranslatef(x, -0.5, -1.05);
    glRotatef(183, 0, 1, 0);
    glRotatef(20, 1, 0, 0);
    //glRotatef(-30, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glDrawArrays(GL_TRIANGLES, 0, SpaceShipObjectNumVerts);
    glPopMatrix();

    checkError("Draw :: glBindTexture");
}