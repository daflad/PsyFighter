
#include "GL/glew.h"
#include <GLUT/glut.h>

#include "template.h"
#include "space_craft_001.h"
#include "BMPLoader.h"
#include "camera.h"




BMPClass bmp;
GLuint texture_id;
GLfloat LightAmbient[]  =	{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse[]  =	{ 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat LightPosition[] =   { 1.0f, 1.0f, 1.0f, 1.0f };

GLuint vboId = 0;           // ID of VBO for vertex arrays

GLfloat	yrot;				// Y Rotation

long cur_fps=0;
long old_time=0;
long old_fps=0;

/* This is where you put all your OpenGL drawing commands */
void display(void)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
    
    // enble vertex arrays
    // draw data
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glVertexPointer(3, GL_FLOAT, 0, space_craft_001Verts);
    glNormalPointer(GL_FLOAT, 0, space_craft_001Normals);
    glTexCoordPointer(2, GL_FLOAT, 0, space_craft_001TexCoords);

    glTranslatef(0.1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(20, 1, 0, 0);
    glRotatef(-30, 0, 0, 1);
    
    glDrawArrays(GL_TRIANGLES, 0, space_craft_001NumVerts);
    
    // Disable client states:
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    
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
 //   glutTimerFunc(TIMERDELAY, updateScene, 0);
    glDepthRange(0, 1);
    glutKeyboardFunc(keyInput);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// Type of depth testing to do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    std::string f = "/Users/stephenjohnrussell/dev/CyberWalkers/CyberWalkers/spaceship_panel_texture_by_dactilardesign-d4v9zb4.bmp";
    glEnable ( GL_TEXTURE_2D );
    glGenTextures (1, &texture_id);
	BMPLoad(f,bmp);
    glBindTexture ( GL_TEXTURE_2D, texture_id );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp.width,bmp.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp.bytes);
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
	glEnable(GL_LIGHT1);								// Enable Light One
    
    // set input data to arrays
    glVertexPointer(3, GL_FLOAT, 0, space_craft_001Verts);
    glNormalPointer(GL_FLOAT, 0, space_craft_001Normals);
    glTexCoordPointer(2, GL_FLOAT, 0, space_craft_001TexCoords);

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
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
    
	glMatrixMode(GL_MODELVIEW);							// Select the Modelview Matrix
	glLoadIdentity();									// Reset the Modelview Matrix
}

/* Keyboard input processing routine */
void keyInput(unsigned char key, int x, int y)
{
    // What's that code again??
    printf("key : %c\n", key);
    switch(key)
    {
            // Press escape to exit.
        case 27:
            printf("EXIT : %c\n", key);
            exit(0);
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