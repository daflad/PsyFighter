//
//  main.h
//  CyberWalkers
//
//  Created by Stephen Russell on 09/10/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef CyberWalkers_main_h
#define CyberWalkers_main_h

#include "GL/glew.h"
#include <GLUT/glut.h>
#include "GamePlay.hpp"

// These are the functions that you will use to create and interact with your GL scene:
void display(void);
void resize(int w, int h);
void keyUp(unsigned char key, int x, int y);
void keyDown(unsigned char key, int x, int y);
void update();
GamePlay gp;

#endif
