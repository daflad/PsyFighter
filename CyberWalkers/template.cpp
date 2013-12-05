#include "template.h"
#include "space_craft_001.h"

/* This is where you put all your OpenGL drawing commands */
void display(void)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
    // draw data
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, space_craft_001Verts);
    glNormalPointer(GL_FLOAT, 0, space_craft_001Normals);
    glTexCoordPointer(2, GL_FLOAT, 0, space_craft_001TexCoords);
    glDrawArrays(GL_TRIANGLES, 0, space_craft_001NumVerts);
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glutSwapBuffers();      //swaps the front and back buffers
}

/* Initialisation routine - acts like your typical constructor in a Java program. */
void setup(void)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// Type of depth testing to do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    
    
    // set input data to arrays
//    glVertexPointer(3, GL_FLOAT, 0, space_craft_001Verts);
//    glNormalPointer(GL_FLOAT, 0, space_craft_001Normals);
//    glTexCoordPointer(2, GL_FLOAT, 0, space_craft_001TexCoords);

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
    switch(key)
    {
            // Press escape to exit.
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}