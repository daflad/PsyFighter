//
//  main.cpp
//  Three-Dimentional Gasket
//
//  Created by Liang Sun on 1/6/13.
//  Copyright (c) 2013 Liang Sun. All rights reserved.
//

#include "GamePlay.h"
#include "SpaceShipObject.h"


int main(int argc, char** argv)
{
    float *ssInit[] = {SpaceShipObjectVerts, SpaceShipObjectNormals, SpaceShipObjectTexCoords};
    GamePlay gp = GamePlay(SpaceShipObjectNumVerts, ssInit);
    printf("Application Started");
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    
    glutInitWindowSize(1280, 800);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("GLUT Program");
    
    glutDisplayFunc(GamePlay::draw);
    glutKeyboardFunc(GamePlay::keyInput);
    gp.setup();
    glutMainLoop();
    return 0;
}