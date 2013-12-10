//
//  LazerShot.h
//  CyberWalkers
//
//  Created by Stephen John Russell on 09/12/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.


#ifndef __CyberWalkers__LazerShot__
#define __CyberWalkers__LazerShot__

#include <iostream>

// Spaceship lazers
// Glowing, scaling spheres
class LazerShot {

public:
    
    // Shpere constructor values
    int lazerSize;
    int gridRows;
    int gridCols;
    
    // Location values
    float x, y, z;
    
    // Distance form spaceship
    float scaleFactor;
    
    // Constructor
    LazerShot();
    
    // Initiate lazer values
    void init();
    // Update location of lazer in scene
    void update();
    // Draw lazer to screen
    void draw();
    
};

#endif /* defined(__CyberWalkers__LazerShot__) */
