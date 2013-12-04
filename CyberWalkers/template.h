//
//  template.h
//  CyberWalkers
//
//  Created by Stephen Russell on 09/10/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef __CyberWalkers__template__
#define __CyberWalkers__template__

#include <iostream>
// Include GLM
#include <glm/glm.hpp>
using namespace glm;

// These are the functions that you will use to create and interact with your GL scene:
void display(void);
void resize(int w, int h);
void setup(void);
void keyInput(unsigned char key, int x, int y);

void drawLine(int y);

#endif /* defined(__CyberWalkers__template__) */
