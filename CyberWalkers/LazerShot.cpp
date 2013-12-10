//
//  LazerShot.cpp
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "LazerShot.h"

LazerShot::LazerShot(){
    
}

// Initiate lazer values
void LazerShot::init(){
    
}
// Update location of lazer in scene
void LazerShot::update(){
    
}
// Draw lazer to screen
void LazerShot::draw(){
    
    glPushMatrix();
    glScalef(s, s, s);
    glTranslatef(0.2, y, z);
    gluSphere(quad, lazerSize, gridCols, gridRows);
    glTranslatef(-0.4, 0, 0);
    gluSphere(quad, lazerSize, gridCols, gridRows);
    glPopMatrix();
}