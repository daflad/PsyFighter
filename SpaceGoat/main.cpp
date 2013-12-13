//
//  main.cpp
//  Three-Dimentional Gasket
//
//  Created by Liang Sun on 1/6/13.
//  Copyright (c) 2013 Liang Sun. All rights reserved.
//

#include "main.h"

using namespace std;

int main(int argc, char** argv) {
    
    printf("Application Started");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    
    gp = GamePlay();
    glutInitWindowSize(1280, 800);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("GLUT Program");
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);
    glutReshapeFunc(resize);
    gp.setup();
    glutMainLoop();
    return 0;
}

void display(void){
    gp.draw();
}

void resize(int w, int h){
    gp.resize(w,h);
}

void keyInput(unsigned char key, int x, int y){
    gp.keyInput(key, x, y);
    printf("key : %c : %i\n",key,key);
    display();
}
