//
//  SolarSystem.cpp
//  SpaceGoat
//
//  Created by Stephen John Russell on 14/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#include "SolarSystem.hpp"

using namespace std;

SolarSystem::SolarSystem() {
    numPlannets = rand() % 9 + 1;
    printf("Number Of Plannets : %i\n", numPlannets);
}

void SolarSystem::setup() {
    
}

void SolarSystem::draw() {
    
}