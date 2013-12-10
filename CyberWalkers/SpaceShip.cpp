//
//  SpaceShip.cpp
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "SpaceShip.h"

SpaceShip::SpaceShip() {
    
}

void SpaceShip::setup() {
    std::string f = "/Users/stephenjohnrussell/dev/CyberWalkers/CyberWalkers/spaceship_panel_texture_by_dactilardesign-d4v9zb4.bmp";
    glEnable ( GL_TEXTURE_2D );
    glGenTextures (1, &texture_id);
	BMPLoad(f,bmp);
    glBindTexture ( GL_TEXTURE_2D, texture_id );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp.width,bmp.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp.bytes);
    // set input data to arrays
    glVertexPointer(3, GL_FLOAT, 0, SpaceShipObjectVerts);
    glNormalPointer(GL_FLOAT, 0, SpaceShipObjectNormals);
    glTexCoordPointer(2, GL_FLOAT, 0, SpaceShipObjectTexCoords);
}

void SpaceShip::draw() {
    // enble vertex arrays
    // draw data
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glVertexPointer(3, GL_FLOAT, 0, SpaceShipObjectVerts);
    glNormalPointer(GL_FLOAT, 0, SpaceShipObjectNormals);
    glTexCoordPointer(2, GL_FLOAT, 0, SpaceShipObjectTexCoords);
    
    glPushMatrix();
    glScalef();
    glTranslatef(x, -0.5, -1.05);
    glRotatef(183, 0, 1, 0);
    glRotatef(20, 1, 0, 0);
    //glRotatef(-30, 0, 0, 1);
    glDrawArrays(GL_TRIANGLES, 0, SpaceShipObjectNumVerts);
    glPopMatrix();

    
    // Disable client states:
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}