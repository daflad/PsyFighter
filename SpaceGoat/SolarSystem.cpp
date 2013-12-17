//
//  SolarSystem.cpp
//  SpaceGoat
//
//  Created by Stephen John Russell on 14/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "SolarSystem.hpp"

SolarSystem::SolarSystem() {
    make_plannets(0);
}

void SolarSystem::make_plannets(int start) {
    numPlannets = 300;
    plannets.assign(start + numPlannets, *new Plannet());
    textures = *new GLuint;
    
    for (int i = start; i < start + numPlannets; i++) {
        
        plannets.at(i).setID(textures++);
        plannets.at(i).setLocation(20 - rand() % 40, 10 - rand() % 30,-rand() % 30 - i);
        
        printf("Location : %.2f,%.2f,%.2f\n", plannets.at(i).x, plannets.at(i).y,plannets.at(i).z);
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
        float dy = yPos - plannets.at(i).y;
        float dz = zPos - plannets.at(i).z;
        float dx2 = dx * dx;
        float dy2 = dy * dy;
        float dz2 = dz * dz;
        float dist = dx2 + dy2 + dz2;
        if (1.25 > dist) {
            return true;
        }
    }
    return false;
}