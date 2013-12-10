
#include "GL/glew.h"
#include <GLUT/glut.h>
#include <thread>

#include "template.h"
#include "SpaceShip.h"
#include "BMPLoader.h"
#include "camera.h"

BMPClass bmp;
GLuint texture_id;
float lightDiffuse[]  = { 1.0f, 1.0f, .5f, 1.0f };    // direct light
float lightSpecular[] = { 1.0f, 1.0f, .5f, 1.0f };    // highlight
float lightAmbient[]  = { .2f, .2f, .1f, 1.0f };  // scattered light
float lightPosition[] = { -4.0f, 4.0f, 4.0f, 1.0f };

GLuint vboId = 0;           // ID of VBO for vertex arrays

GLfloat	yrot = 1;				// Y Rotation
GLfloat xPos = 0;
GLfloat phaz = 1;


long cur_fps=0;
long old_time=0;
long old_fps=0;

void shootPhazer(){
    phaz -= 0.05;
    if (phaz < 0) {
        phaz = 1;
    }
}
void fire() {
    // Constructs the new thread and runs it. Does not block execution.
    std::thread t1(shootPhazer);
    //Makes the main thread wait for the new thread to finish execution, therefore blocks execution.
    t1.join();
}

/* This is where you put all your OpenGL drawing commands */
void display(void)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
    
    

    
    
    glutSwapBuffers();      //swaps the front and back buffers
}

/* Initialisation routine - acts like your typical constructor in a Java program. */
void setup(void)										// All Setup For OpenGL Goes Here
{
    // call glewInit() to initialize the OpenGL extension entry points.
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(0);
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    								// Enable Light
    quad = gluNewQuadric();
 //   glutTimerFunc(TIMERDELAY, updateScene, 0);
    glDepthRange(0, 100);
    glutKeyboardFunc(keyInput);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// Type of depth testing to do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,lightPosition);	// Position The Light
	glEnable(GL_LIGHT1);								// Enable Light One
    
    

}

/* Tells the program how to resize your OpenGL Window */
void resize(int width, int height)
{
    
	if (height==0)										// Prevent a divide by zero by
	{										            // making height equal one
		height=1;
	}
    
	glViewport(0,0,(GLsizei)width,(GLsizei)height);		// Set viewport size to be entire OpenGL window
    
	glMatrixMode(GL_PROJECTION);						// Select the Projection Matrix
	glLoadIdentity();									// Reset the Projection Matrix
    
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(145.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
    
	glMatrixMode(GL_MODELVIEW);							// Select the Modelview Matrix
	glLoadIdentity();									// Reset the Modelview Matrix
}

/* Keyboard input processing routine */
void keyInput(unsigned char key, int x, int y)
{
    // What's that code again??
    printf("key : %c : %i\n", key, key);
    switch(key)
    {
            // Press escape to exit.
        case 27:
            exit(0);
            break;
        case 97:
            xPos -= 0.05;
            if (xPos < -1) {
                xPos = -1;
            }
            break;
        case 100:
            xPos += 0.05;
            if (xPos > 1) {
                xPos = 1;
            }
            break;
        case 119:
            yrot -= 0.01;
            if (yrot < 0) {
                yrot = 0;
            }
            break;
        case 32:
            shootPhazer();
            break;
        case 115:
            yrot += 0.01;
            if (yrot > 1) {
                yrot = 1;
            }
            break;
        default:
            break;
    }
    display();
}

// Return milliseconds since start
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
    
   // sprintf(temp,"Bunny mesh using vertex buffer objects: %d triangles; %d fps",NUM_TRIANGLES, old_fps);
    glutSetWindowTitle(temp);
}