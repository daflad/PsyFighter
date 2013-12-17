//
//  SolarSystem.cpp
//  SpaceGoat
//
//  Created by Stephen John Russell on 14/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "SolarSystem.hpp"

SolarSystem::SolarSystem() {
    float dists[] = {579500, 1081100, 1495700, 2278400, 7781400, 14270000, 28703000, 44999000, 59130000};
    float diams[] = {4866, 12106, 12742, 6760, 142984, 116438, 46940, 45432, 2274};
    numPlannets = 9;
    plannets.assign(numPlannets, *new Plannet());
    textures.assign(numPlannets, *new GLuint);
    for (int i = 0; i < numPlannets; i++) {
        plannets.at(i).setID(++textures.at(0));
        plannets.at(i).setLocation(0, 0,-dists[i], diams[i]);
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
        float dist = dx2 + dy2 + dz2;
        if (0.26 > dist) {
            return true;
        }
    }
    return false;
}