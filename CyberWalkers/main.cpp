//
//  main.cpp
//  Three-Dimentional Gasket
//
//  Created by Liang Sun on 1/6/13.
//  Copyright (c) 2013 Liang Sun. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include "template.h"



int main(int argc, char** argv)
{
    printf("Application Started");
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    
    glutInitWindowSize(1280, 800);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("GLUT Program");
    
    glutDisplayFunc(display);
    
    setup();
    glutMainLoop();
    return 0;
}