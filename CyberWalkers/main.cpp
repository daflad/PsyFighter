//
//  main.cpp
//  Three-Dimentional Gasket
//
//  Created by Liang Sun on 1/6/13.
//  Copyright (c) 2013 Liang Sun. All rights reserved.
//

#include "main.h"
#include "SpaceShipObject.h"


int main(int argc, char** argv)
{
    float *ssInit[] = {space_craft_001Verts, space_craft_001Normals, space_craft_001TexCoords};
    printf("Application Started");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    gp = GamePlay();
    glutInitWindowSize(1280, 800);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("GLUT Program");
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);
    gp.setup(space_craft_001NumVerts, ssInit);
    glutMainLoop();
    return 0;
}

void display(void){
    gp.draw();
}

void resize(int w, int h){
    
}

void keyInput(unsigned char key, int x, int y){
    
}
