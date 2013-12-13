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
#include "GamePlay.h"

// These are the functions that you will use to create and interact with your GL scene:
void display(void);
void resize(int w, int h);
void keyInput(unsigned char key, int x, int y);
GamePlay gp;

#endif
