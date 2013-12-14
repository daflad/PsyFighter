//
//  SolarSystem.cpp
//  SpaceGoat
//
//  Created by Stephen John Russell on 14/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "SolarSystem.hpp"

SolarSystem::SolarSystem() {
    numPlannets = rand() % 8 + 5;
    plannets.assign(numPlannets, *new Plannet());
    textures.assign(numPlannets, *new GLuint);
    for (int i = 0; i < numPlannets; i++) {
        plannets.at(i).setID(textures.at(i));
        float a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        plannets.at(i).setLocation((rand() % 2 ) - a, (rand() % 2 ) - xb, -rand() % 10);
    }
    printf("Number Of Plannets : %i\n", numPlannets);
}

void SolarSystem::setup() {
    for (int i = 0; i < numPlannets; i++) {
        plannets.at(i).setup();
    }
}

void SolarSystem::draw() {
    for (int i = 0; i < numPlannets; i++) {
        plannets.at(i).draw();
    }
}