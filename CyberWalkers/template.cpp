#include <GL/glew.h>
#include <GLUT/glut.h>

#include "template.h"
#include "space_craft_001.h"
#include "BMPLoader.h"
#include "camera.h"




BMPClass bmp;
GLuint texture_id;
GLfloat LightAmbient[]=                { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=                { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=        { 1.0f, 1.0f, 2.0f, 1.0f };

GLuint vboId = 0;           // ID of VBO for vertex arrays

GLfloat        yrot;                                // Y Rotation

long cur_fps=0;
long old_time=0;
long old_fps=0;

/* This is where you put all your OpenGL drawing commands */
void display(void)                                                                        // Here's Where We Do All The Drawing
{
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
    
    // enble vertex arrays
    // draw data
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    
    // Vertices and Normals are packed in the same VBO - specify pointers accordingly
    //glNormalPointer(GL_FLOAT, 0, (void*)sizeof(space_craft_001Verts));
    //glVertexPointer(3, GL_FLOAT, 0, 0);
    
    glPushMatrix();
  //  glRotatef(yrot,0.0f,1.0f,0.0f);
  // glTranslatef(0, 0, 0.9);
    
    // Draw the bunny
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glVertexPointer(3, GL_FLOAT, 0, space_craft_001Verts);
    glNormalPointer(GL_FLOAT, 0, space_craft_001Normals);
    glTexCoordPointer(2, GL_FLOAT, 0, space_craft_001TexCoords);
    
    glDrawArrays(GL_TRIANGLES, 0, space_craft_001NumVerts);
    
    
    //Specify the appropriate function call for glDrawElements here:
    //glDrawElements(GL_TRIANGLES,space_craft_001NumVerts,GL_FLOAT,space_craft_001Verts);
    
    // ----------------------------------------------------------------------------------------
    
    glPopMatrix();
    
    // Update the position of the bunny before it is rendered in the next frame:
    // Lab 6 Exercise - change the vale of this increment to 2.0f and then 0.02f
    yrot+=0.2f;
    
    
    // Disable client states:
    glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    
    // it is good idea to release VBOs with ID 0 after use.
   // glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    
    glutSwapBuffers();      //swaps the front and back buffers
}

/* Initialisation routine - acts like your typical constructor in a Java program. */
void setup(void)                                                                                // All Setup For OpenGL Goes Here
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
    
    if (!__GLEW_ARB_vertex_buffer_object)
    {
        fprintf(stderr, "Vertex Buffer Objects not supported on this platform");
        exit(0);
    }
    // It is safe to use the ARB_vertex_buffer_object extension here. */
    // put both vertex coords array, vertex normal array in the same buffer object.
    // glBufferDataARB with NULL pointer reserves only memory space.
    // Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
    // target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
    // Note on exit - delete the VBO - see KillGLWindow()
    glGenBuffersARB(1, &vboId);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(space_craft_001Verts)+sizeof(space_craft_001Normals), 0, GL_STATIC_DRAW_ARB);          //upload to graphics card
    glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(space_craft_001Verts), space_craft_001Verts);                             // copy vertices starting from 0 offest
    glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(space_craft_001Verts), sizeof(space_craft_001Normals), space_craft_001Normals);                // copy normals after vertices
    
    glShadeModel(GL_SMOOTH);                                                        // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                                // Black Background
    glClearDepth(1.0f);                                                                        // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                                                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                                                                // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);        // Really Nice Perspective Calculations
    glEnable(GL_LIGHTING);
    
    // Set up  the light
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);                // Setup The Ambient Light
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);                // Setup The Diffuse Light
    glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);        // Position The Light
    glEnable(GL_LIGHT0);                                                                // Enable Light
    //    glutTimerFunc(TIMERDELAY, updateScene, 0);
    //    glDepthRange(0, 1);
    //    glutKeyboardFunc(keyInput);
    //        glShadeModel(GL_SMOOTH);                                                        // Enable Smooth Shading
    //        glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                                // Black Background
    //        glClearDepth(1.0f);                                                                        // Depth Buffer Setup
    //        glEnable(GL_DEPTH_TEST);                                                        // Enables Depth Testing
    //        glDepthFunc(GL_LEQUAL);                                                                // Type of depth testing to do
    //        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);        // Really Nice Perspective Calculations
        std::string f = "/Users/stephenjohnrussell/dev/CyberWalkers/CyberWalkers/spaceship_panel_texture_by_dactilardesign-d4v9zb4.bmp";
        glEnable ( GL_TEXTURE_2D );
        glGenTextures (1, &texture_id);
        BMPLoad(f,bmp);
        glBindTexture ( GL_TEXTURE_2D, texture_id );
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,0,3,bmp.width,bmp.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp.bytes);
    //    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);                // Setup The Ambient Light
    //        glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);                // Setup The Diffuse Light
    //        glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);        // Position The Light
    //        glEnable(GL_LIGHT1);                                                                // Enable Light One
    //
    // set input data to arrays
    //    glVertexPointer(3, GL_FLOAT, 0, space_craft_001Verts);
    //    glNormalPointer(GL_FLOAT, 0, space_craft_001Normals);
    //    glTexCoordPointer(2, GL_FLOAT, 0, space_craft_001TexCoords);
    
}

/* Tells the program how to resize your OpenGL Window */
void resize(int width, int height)
{
    
    if (height==0)                                                                                // Prevent a divide by zero by
    {                                                                                            // making height equal one
        height=1;
    }
    
    glViewport(0,0,(GLsizei)width,(GLsizei)height);                // Set viewport size to be entire OpenGL window
    
    glMatrixMode(GL_PROJECTION);                                                // Select the Projection Matrix
    glLoadIdentity();                                                                        // Reset the Projection Matrix
    
    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
    
    glMatrixMode(GL_MODELVIEW);                                                        // Select the Modelview Matrix
    glLoadIdentity();                                                                        // Reset the Modelview Matrix
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