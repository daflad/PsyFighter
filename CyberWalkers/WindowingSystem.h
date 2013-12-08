//
//  WindowingSystem.h
//  CyberWalkers
//
//  Created by Stephen Russell on 09/10/2013.
//  Copyright (c) 2013 Stephen John Russell. All rights reserved.
//

#ifndef __CyberWalkers__WindowingSystem__
#define __CyberWalkers__WindowingSystem__

#include <stdio.h>          // Header File For Standard Input / Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <iostream>

#include <GLUT/glut.h>		// Header file for the glut library.
                            // glut.h calls gl.h and glu.h

// These are the functions that you will use to create and interact with your GL scene:
void drawScene(void);
void resize(int w, int h);
void setup(void);
void keyInput(unsigned char key, int x, int y);

#endif /* defined(__CyberWalkers__WindowingSystem__) */
