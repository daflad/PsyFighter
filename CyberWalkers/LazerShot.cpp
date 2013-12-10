//
//  LazerShot.cpp
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "LazerShot.h"

LazerShot::LazerShot() {
    x = 0.2;
    y = 0;
    z = 0;
}

// Initiate lazer values
void LazerShot::init() {
    quad = gluNewQuadric();
}

// Update location of lazer in scene
void LazerShot::update() {
    s -= 0.01;
}

// Draw lazer to screen
void LazerShot::draw() {    
    glPushMatrix();
    glScalef(s, s, s);
    glTranslatef(x, y, z);
    gluSphere(quad, lazerSize, gridCols, gridRows);
    glTranslatef(x-0.4, 0, 0);
    gluSphere(quad, lazerSize, gridCols, gridRows);
    glPopMatrix();
}