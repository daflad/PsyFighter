//
//  main.cpp
//  Three-Dimentional Gasket
//
//  Created by Liang Sun on 1/6/13.
//  Copyright (c) 2013 Liang Sun. All rights reserved.
//

#include "main.hpp"

long cur_fps=0;
long old_time=0;
long old_fps=0;

using namespace std;

int getTimer()
{
    return glutGet(GLUT_ELAPSED_TIME);
}

void CalculateFPS()
{
    char temp[100];
    
    cur_fps++;
    if(getTimer()-old_time >= 1000) // over a second
    {
        old_fps = cur_fps;
        cur_fps = 0;
        old_time =getTimer();
    }
    sprintf(temp,"Bunny mesh using vertex buffer objects: %d fps", old_fps);
    glutSetWindowTitle(temp);
}


int main(int argc, char** argv) {
    
    printf("Application Started");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    
    gp = GamePlay();
    glutInitWindowSize(1280, 800);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("GLUT Program");
    
    // Begin processing
    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);
    glutReshapeFunc(resize);
    glutIdleFunc(update);
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

void update() {
    CalculateFPS();
    glutPostRedisplay();
}