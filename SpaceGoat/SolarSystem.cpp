//
//  SolarSystem.cpp
//  SpaceGoat
//
//  Created by Stephen John Russell on 14/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "SolarSystem.hpp"
//#include "BMPLoader.cpp"

SolarSystem::SolarSystem() {
    make_plannets(0);
    tubeZ = -1000;
}

void SolarSystem::make_plannets(int start) {
    numPlannets = 10;
    plannets.assign(start + numPlannets, *new Plannet());
    textures = *new GLuint;
    
    for (int i = start; i < start   + numPlannets; i++) {
        
        plannets.at(i).setID(++textures);
//        plannets.at(i).setLocation(1 - rand(), 1 - rand(), -rand() % 10 * i);
        plannets.at(i).setLocation(5 - rand() % 10, 5 -rand() % 10 , -rand() % 150 * i);
        
        printf("Location : %.2f,%.2f,%.2f\n", plannets.at(i).x, plannets.at(i).y,plannets.at(i).z);
    }
    bound.setID(++textures);
    printf("Number Of Plannets : %i\n", numPlannets);
}

void SolarSystem::setup() {
    for (int i = 0; i < numPlannets; i++) {
        plannets.at(i).setup();
    }
    bound.setup();
}

void SolarSystem::draw() {
    glPushMatrix();
    bound.draw();
    for (int i = 0; i < numPlannets; i++) {
        plannets.at(i).draw();
    }
    glPopMatrix();
}

bool SolarSystem::collisionDetection(float xPos, float yPos, float zPos) {
    for (int i = 0; i < numPlannets; i++) {
        Plannet *p = &plannets.at(i);
        if (p->z < zPos) {
            float dx = xPos - p->x;
            float dy = yPos - p->y;
            float dz = zPos - p->z;
            float dx2 = dx * dx;
            float dy2 = dy * dy;
            float dz2 = dz * dz;
            float dist = sqrt(dx2 + dy2 + dz2);
            if ((float)p->s / 8 > dist) {
                return true;
            }
        } else {
            plannets.at(i).setLocation(xPos, yPos , zPos - 100 -rand() % 150 * i * 2);
        }
    }
    return false;
}