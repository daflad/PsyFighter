//
//  SolarSystem.cpp
//  SpaceGoat
//
//  Created by Stephen John Russell on 14/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "SolarSystem.hpp"

SolarSystem::SolarSystem() {
    numPlannets = 300;
    plannets.assign(numPlannets, *new Plannet());
    textures.assign(numPlannets, *new GLuint);
    for (int i = 0; i < numPlannets; i++) {
        plannets.at(i).setID(textures.at(i));
        plannets.at(i).setLocation(rand() % 30, rand() % 30,-rand() % 30 - i);
    }
    printf("Number Of Plannets : %i\n", numPlannets);
}

void SolarSystem::setup() {
    for (int i = 0; i < numPlannets; i++) {
        plannets.at(i).setup();
    }
}

void SolarSystem::draw() {
    glPushMatrix();
    for (int i = 0; i < numPlannets; i++) {
        plannets.at(i).draw();
    }
    glPopMatrix();
}

bool SolarSystem::collisionDetection(float xPos, float yPos, float zPos) {
    for (int i = 0; i < numPlannets; i++) {
        float dx = xPos - plannets.at(i).x;
        float dy = yPos - 0.3 - plannets.at(i).y;
        float dz = zPos - plannets.at(i).z;
        float dx2 = dx * dx;
        float dy2 = dy * dy;
        float dz2 = dz * dz;
        float dist = sqrt(dx2 + dy2 + dz2);
        if (plannets.at(i).s >= (dist * 2) ) {
            return true;
        }
    }
    return false;
}