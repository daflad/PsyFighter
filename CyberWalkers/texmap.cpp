/*********************************SPACE EXPLORATION**********************************************************/


/* A code that simulates the space, right from big bang theory implementing various objects in space */
/* CODE REQUIREMENTS: Requires Graphics Accelarator , the Code best runs with  nVdia 7400  graphic card accelarator
	DOES NOT RUN ON SYSTEMS HAVING GENERAL GRAPHIC CARDS : REASON BEING HIGH REQUIREMENT OF GRAPHIC MEMORY
	HERE IT IS DUE TO HUGE TEXTURE MAPPING.*/
/* CODE DEVELOPED BY GROUP NUMBER 9  OF RGIIT( A CAMPUS OF IIITA)*/
/* USES OPEN GL UTILITY KIT TO RENDER GRAPHICS*/

#include <GLUT/glut.h>
#include "texture.h"
#include <stdio.h>			// Header File For Standard Input/Output
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define	MAX_PARTICLES	1500     // Number Of Particles To Create in the big bang and the comet
#define	MAX_PARTICLES1	200		// number of particles after the explosion
float xt=-120,yt=-120,zt=-20,xt2=-120,yt2=-120,zt2=-20,xt3=-250,yt3=-250,zt3=-20;//Initial location of the comets 
float	slowdown=2.0f;				// Slow Down Particles
float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)
float	zoomc=-40.0f;				// Used To Zoom Out
GLuint	loopc,loopb;						// Misc Loop Variable
int           Width;            /* Width of window */
int           Height;           /* Height of window */

/* declaring the variables used for texture mapping*/
GLuint        background,Planet,c_star,s_gal,e_gal;             //Background//Planet


float ast_rot=0;   //rotating the asteriod on it`s own axes
float tran=0,tranb=0;	// translating the entire scene... 

float x,y;
GLUquadricObj *obj;  //using quadric objects for the creation of the asteriods
const	int num=30;	// Number Of Stars To Draw in the spiral galaxy 

/*variables to handle collision in b/w the asteriods*/
float Ascountx1=150; 	
float Ascountx2=-150;
float Ascountx11=150;
float Ascountx21=-150;
float xc1=0,xc2=0;

/* to handle the big bang , explosion , comet*/
typedef struct						// Create A Structure For Particle
{
	bool	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed
	float	r;						// Red Value
	float	g;						// Green Value
	float	b;						// Blue Value
	float	x;						// X Position
	float	y;						// Y Position
	float	z;						// Z Position
	float	xi;						// X Direction
	float	yi;						// Y Direction
	float	zi;						// Z Direction
	float	xg;						// X Gravity
	float	yg;						// Y Gravity
	float	zg;						// Z Gravity
}
particles;							// Particles Structure

particles particle[MAX_PARTICLES],particleb[MAX_PARTICLES],particle2[MAX_PARTICLES],particle3[MAX_PARTICLES];	// Particle Array (Room For Particle Info)


/* to handle the spiral galaxy*/
typedef struct				// Create A Structure For Star
{
	int r, g, b;			// Stars Color
	GLfloat dist,			// Stars Distance From Center
			angle;			// Stars Current Angle
}
stars;
stars star[num];			// Need To Keep Track Of 'num' Stars i.e total number of stars in the spiral galaxy

GLfloat	zoomg=-50.0f;		// Distance Away From Stars
GLfloat tilt=30.0f;			// Tilt The View
GLfloat	spin;				// Spin Stars

GLuint	loopg;				// General Loop Variable
void TimerFunction(int value)
	{
		ast_rot+=0.5;   // rotation of the asteriod around it`s own axes
		tran+=0.1;		// Animating
		tranb+=1;	

		/* speed of comet 1*/

		xt=xt+0.1;	
		yt=yt+0.1;
		zt=zt+0.1;

		/*speed of the comet 2*/
		xt2=xt2+0.2;
		yt2=yt2+0.2;
		zt2=zt2+0.2;

		/*speed of the comet 3*/

		xt3=xt+0.2;
		yt3=yt3+0.4;
		zt3=zt3+0.2;

		/* Variables for collision identification */
		
		Ascountx1=Ascountx1-0.1;
		Ascountx2=Ascountx2+0.1;
		Ascountx11=Ascountx11-0.5;
		Ascountx21=Ascountx21+0.5;

		glutPostRedisplay();
	glutTimerFunc(33,TimerFunction, 1);
	} // For Animation
void explosion(void)					//for explosion after the asteriod collision
{
	glEnable(GL_BLEND);					//enabling the blend function and setting the alpha value to 1 to enable transperancy
	glBindTexture(GL_TEXTURE_2D, c_star); // binding the texture to every particle i.e each quad
	glColor4f(1,1,1,1);                   //setting the values of r , g, b to 1 1 1 to get white

	for (loopb=0;loopb<MAX_PARTICLES1;loopb++)					// Loop Through All The Particles
	{
		if (particleb[loopb].active)							// If The Particle Is Active
		{
			float x=particleb[loopb].x;						// Grab Our Particle X Position
			float y=particleb[loopb].y;						// Grab Our Particle Y Position
			float z=particleb[loopb].z+zoomc;					// Particle Z Pos + Zoom

			// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life

			glColor4f(1,1,0,1);

			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			    glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
				glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
				glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
				glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
			glEnd();										// Done Building Triangle Strip

			/* setting the speeds on the coordinate axes*/
			particleb[loopb].x+=particleb[loopb].xi/(slowdown*1000);// Move On The X Axis By X Speed
			particleb[loopb].y+=particleb[loopb].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
			particleb[loopb].z+=particleb[loopb].zi/(slowdown*1000);// Move On The Z Axis By Z Speed

			/* Gravity set inorder move the particles*/
			particleb[loopb].xi+=particleb[loopb].xg;			// Take Pull On X Axis Into Account
			particleb[loopb].yi+=particleb[loopb].yg;			// Take Pull On Y Axis Into Account
			particleb[loopb].zi+=particleb[loopb].zg;			// Take Pull On Z Axis Into Account
			//particleb[loopb].life-=particleb[loopb].fade;		// Reduce Particles Life By 'Fade'
			
		}
	}
	
	glDisable(GL_BLEND);  // disabling the blend function inorder to disable the transperancy
}

void setuprc()
{	
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency
	glEnable(GL_BLEND);
	

	/* Initializing for the spiral galaxy*/
	for (loopg=0; loopg<num; loopg++)
	{
		star[loopg].angle=0.0f;						// angle made with axes of the spiral galaxy 
		star[loopg].dist=(float(loopg)/num)*5.0f;  // distance from the center of the spiral galaxy of each star
		/*setting the star color to white*/
		star[loopg].r=255;
		star[loopg].g=255;
		star[loopg].b=255;
	}
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform is transperancy
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	/*Initialize the values of the COMET 1 */
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBindTexture(GL_TEXTURE_2D,c_star);				// Select Our Texture
	for (loopc=0;loopc<MAX_PARTICLES;loopc++)			// Initials All The Textures
	{
		particle[loopc].active=true;								// Make All The Particles Active
		particle[loopc].life=1.0f;								// Give All The Particles Full Life
		particle[loopc].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
		particle[loopc].xi=0;										// Random Speed On X Axis
		particle[loopc].yi=0;										// Random Speed On Y Axis
		particle[loopc].zi=0;										// Random Speed On Z Axis
		particle[loopc].xg=5.0f;									// Set Horizontal Pull To Zero
		particle[loopc].yg=-5.0f;									// Set Vertical Pull Downward
		particle[loopc].zg=.0f;										// Set Pull On Z Axis To Zero
	}
	
	/* Initialize the values of the COMET 2 */
	for (loopc=0;loopc<MAX_PARTICLES;loopc++)				// Initials All The Textures
	{
		particle2[loopc].active=true;								// Make All The Particles Active
		particle2[loopc].life=1.0f;								// Give All The Particles Full Life
		particle2[loopc].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
		particle2[loopc].xi=0;										// Random Speed On X Axis
		particle2[loopc].yi=0;										// Random Speed On Y Axis
		particle2[loopc].zi=0;										// Random Speed On Z Axis
		particle2[loopc].xg=5.0f;									// Set Horizontal Pull To Zero
		particle2[loopc].yg=5.0f;								// Set Vertical Pull Downward
		particle2[loopc].zg=0.0f;									// Set Pull On Z Axis To Zero
	}

	/*Initialize the values of COMET 3*/
	for (loopc=0;loopc<MAX_PARTICLES;loopc++)				// Initials All The Textures
	{
		particle3[loopc].active=true;								// Make All The Particles Active
		particle3[loopc].life=1.0f;								// Give All The Particles Full Life
		particle3[loopc].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
		particle3[loopc].xi=0;									// Random Speed On X Axis
		particle3[loopc].yi=0;									// Random Speed On Y Axis
		particle3[loopc].zi=0;									// Random Speed On Z Axis
		particle3[loopc].xg=-2.0f;								// Set Horizontal Pull To Zero
		particle3[loopc].yg=-8.0f;								// Set Vertical Pull Downward
		particle3[loopc].zg=0.0f;								// Set Pull On Z Axis To Zero
	}

	/*Initialize the values fot the BIG BANG*/
	for (loopb=0;loopb<MAX_PARTICLES;loopb++)				// Initials All The Textures
	{
		particleb[loopb].active=true;								// Make All The Particles Active
		particleb[loopb].life=1.0f;								// Give All The Particles Full Life
		particleb[loopb].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
		particleb[loopb].xi=float((rand()%50)-26.0f)*10.0f+10;		// Random Speed On X Axis
		particleb[loopb].yi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Y Axis
		particleb[loopb].zi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Z Axis
		particleb[loopb].xg=0.0f;									// Set Horizontal Pull To Zero
		particleb[loopb].yg=0.0f;								// Set Vertical Pull Downward
		particleb[loopb].zg=0.0f;									// Set Pull On Z Axis To Zero
	}


	
}
void comet(void)
{
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, c_star);
	for (loopc=0;loopc<MAX_PARTICLES;loopc++)					// Loop Through All The Particles
	{
		if (particle[loopc].active)							// If The Particle Is Active
		{
			float x=particle[loopc].x;						// Grab Our Particle X Position
			float y=particle[loopc].y;						// Grab Our Particle Y Position
			float z=particle[loopc].z+zoomc;					// Particle Z Pos + Zoom

			// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
			glColor4f(1,1,1,1);
			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			    glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
				glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
				glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
				glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
			glEnd();										// Done Building Triangle Strip

			particle[loopc].x+=particle[loopc].xi/(slowdown*1000);// Move On The X Axis By X Speed
			particle[loopc].y+=particle[loopc].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
			particle[loopc].z+=particle[loopc].zi/(slowdown*1000);// Move On The Z Axis By Z Speed

			particle[loopc].xi+=particle[loopc].xg;			// Take Pull On X Axis Into Account
			particle[loopc].yi+=particle[loopc].yg;			// Take Pull On Y Axis Into Account
			particle[loopc].zi+=particle[loopc].zg;			// Take Pull On Z Axis Into Account
			particle[loopc].life-=particle[loopc].fade;		// Reduce Particles Life By 'Fade'
			if (particle[loopc].life<0.0f)					// If Particle Is Burned Out
			{
				particle[loopc].life=1.0f;					// Give It New Life
				particle[loopc].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Value
				particle[loopc].x=0.0f;						// Center On X Axis
				particle[loopc].y=0.0f;						// Center On Y Axis
				particle[loopc].z=0.0f;						// Center On Z Axis
				particle[loopc].xi=xspeed+float((rand()%60)-32.0f);	// X Axis Speed And Direction
				particle[loopc].yi=yspeed+float((rand()%60)-30.0f);	// Y Axis Speed And Direction
				particle[loopc].zi=float((rand()%60)-30.0f);	// Z Axis Speed And Direction
				
			}
		}
	}
	glDisable(GL_BLEND);
}
void comet2(void)
{
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, c_star);
	for (loopc=0;loopc<MAX_PARTICLES;loopc++)					// Loop Through All The Particles
	{
		if (particle2[loopc].active)							// If The Particle Is Active
		{
			float x=particle2[loopc].x;						// Grab Our Particle X Position
			float y=particle2[loopc].y;						// Grab Our Particle Y Position
			float z=particle2[loopc].z+zoomc;					// Particle Z Pos + Zoom

			// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
			glColor4f(1,1,1,1);
			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			    glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
				glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
				glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
				glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
			glEnd();										// Done Building Triangle Strip

			particle2[loopc].x+=particle2[loopc].xi/(slowdown*1000);// Move On The X Axis By X Speed
			particle2[loopc].y+=particle2[loopc].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
			particle2[loopc].z+=particle2[loopc].zi/(slowdown*1000);// Move On The Z Axis By Z Speed

			particle2[loopc].xi+=particle2[loopc].xg;			// Take Pull On X Axis Into Account
			particle2[loopc].yi+=particle2[loopc].yg;			// Take Pull On Y Axis Into Account
			particle2[loopc].zi+=particle2[loopc].zg;			// Take Pull On Z Axis Into Account
			particle2[loopc].life-=particle2[loopc].fade;		// Reduce Particles Life By 'Fade'
			if (particle2[loopc].life<0.0f)					// If Particle Is Burned Out
			{
				particle2[loopc].life=1.0f;					// Give It New Life
				particle2[loopc].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Value
				particle2[loopc].x=0.0f;						// Center On X Axis
				particle2[loopc].y=0.0f;						// Center On Y Axis
				particle2[loopc].z=0.0f;						// Center On Z Axis
				particle2[loopc].xi=xspeed+float((rand()%60)-32.0f);	// X Axis Speed And Direction
				particle2[loopc].yi=yspeed+float((rand()%60)-30.0f);	// Y Axis Speed And Direction
				particle2[loopc].zi=float((rand()%60)-30.0f);	// Z Axis Speed And Direction
			}
		}
	}
	glDisable(GL_BLEND);
}
void comet3(void)
{
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, c_star);
	for (loopc=0;loopc<MAX_PARTICLES;loopc++)					// Loop Through All The Particles
	{
		if (particle3[loopc].active)							// If The Particle Is Active
		{
			float x=particle3[loopc].x;						// Grab Our Particle X Position
			float y=particle3[loopc].y;						// Grab Our Particle Y Position
			float z=particle3[loopc].z+zoomc;					// Particle Z Pos + Zoom

			// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
			glColor4f(1,1,1,1);
			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			    glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
				glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
				glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
				glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
			glEnd();										// Done Building Triangle Strip

			particle3[loopc].x+=particle3[loopc].xi/(slowdown*1000);// Move On The X Axis By X Speed
			particle3[loopc].y+=particle3[loopc].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
			particle3[loopc].z+=particle3[loopc].zi/(slowdown*1000);// Move On The Z Axis By Z Speed

			particle3[loopc].xi+=particle3[loopc].xg;			// Take Pull On X Axis Into Account
			particle3[loopc].yi+=particle3[loopc].yg;			// Take Pull On Y Axis Into Account
			particle3[loopc].zi+=particle3[loopc].zg;			// Take Pull On Z Axis Into Account
			particle3[loopc].life-=particle3[loopc].fade;		// Reduce Particles Life By 'Fade'
			if (particle3[loopc].life<0.0f)					// If Particle Is Burned Out
			{
				particle3[loopc].life=1.0f;					// Give It New Life
				particle3[loopc].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Value
				particle3[loopc].x=0.0f;						// Center On X Axis
				particle3[loopc].y=0.0f;						// Center On Y Axis
				particle3[loopc].z=0.0f;						// Center On Z Axis
				particle3[loopc].xi=xspeed+float((rand()%60)-32.0f);	// X Axis Speed And Direction
				particle3[loopc].yi=yspeed+float((rand()%60)-30.0f);	// Y Axis Speed And Direction
				particle3[loopc].zi=float((rand()%60)-30.0f);	// Z Axis Speed And Direction
			}
		}
	}
	glDisable(GL_BLEND);
}
/* Function for the implementation of the big bang*/
void bigbang(void)
{
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, c_star);
	for (loopb=0;loopb<MAX_PARTICLES;loopb++)					// Loop Through All The Particles
	{
		if (particleb[loopb].active)							// If The Particle Is Active
		{
			float x=particleb[loopb].x;						// Grab Our Particle X Position
			float y=particleb[loopb].y;						// Grab Our Particle Y Position
			float z=particleb[loopb].z+zoomc;					// Particle Z Pos + Zoom

			// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
			glColor4f(1,1,1,1);
			glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			    glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
				glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
				glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
				glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
			glEnd();										// Done Building Triangle Strip

			particleb[loopb].x+=particleb[loopb].xi/(slowdown*1000);// Move On The X Axis By X Speed
			particleb[loopb].y+=particleb[loopb].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
			particleb[loopb].z+=particleb[loopb].zi/(slowdown*1000);// Move On The Z Axis By Z Speed

			particleb[loopb].xi+=particleb[loopb].xg;			// Take Pull On X Axis Into Account
			particleb[loopb].yi+=particleb[loopb].yg;			// Take Pull On Y Axis Into Account
			particleb[loopb].zi+=particleb[loopb].zg;			// Take Pull On Z Axis Into Account
		}
	}
	glDisable(GL_BLEND);
}

/* Back ground Image of the scene*/
void farsight(void)
{
	glPushMatrix();
	glTranslatef(0.0, 0.0, -1000.0);
	glBindTexture(GL_TEXTURE_2D, background);
	glRotatef(90,0,0,1);
	glScalef(4,4,1);
	glBegin(GL_QUADS);
	{
		 glTexCoord3f(0.0,0.0,0.0);glVertex3f(-150,225,0);
		 glTexCoord3f(0,1.0,0.0);glVertex3f(150,225,0);
         glTexCoord3f(1.0,1.0,0.0);glVertex3f(150,-225,0);
		 glTexCoord3f(1.0,0.0,0.0);glVertex3f(-150,-225,0);
	}
	glEnd();
	glPopMatrix();
}
void spheres(void)
{
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D,Planet);
	gluSphere(obj, 2.0,6.0,4.0);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
}
void s_galaxy(float sx,float sy,float sz,float rot,float px,float py,float pz)//float sgal_locx,float sgal_locy,float sgal_locz)
{
	
	glBindTexture(GL_TEXTURE_2D,s_gal);			// Select Our Texture
	for (loopg=0; loopg<num; loopg++)						// Loop Through All The Stars
	{
		glLoadIdentity();								// Reset The View Before We Draw Each Star
		glTranslatef(0,0,tran);
		glTranslatef(sx,sy,sz);							//position of the spiral galaxy
		glRotatef(rot,px,py,pz);						//orientation of the spiral galaxy
		glRotatef(tilt,1.0f,0.0f,0.0f);					// Tilt The View (Using The Value In 'tilt')
		glRotatef(star[loopg].angle,0.0f,1.0f,0.0f);		// Rotate To The Current Stars Angle
		glTranslatef(star[loopg].dist,0.0f,0.0f);		// Move Forward On The X Plane
		glRotatef(-star[loopg].angle,0.0f,1.0f,0.0f);	// Cancel The Current Stars Angle
		glRotatef(-tilt,1.0f,0.0f,0.0f);				// Cancel The Screen Tilt
		
		glRotatef(spin,0.0f,0.0f,1.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
		glEnd();

		spin+=0.01f;
		star[loopg].angle+=float(loopg)/num;
		
	}
	
}


void eGalaxy()
{
    float x,y,z,a,b,angle;
	x = 1.5;
		y =1.25;
	for(int i=0; i<40; i++)
	{
		
		//z = rand()%10;
		angle = 0;
		for(int i=0; i<20; i++)
		{
		a = x*cos(angle);
		b = y*sin(angle);
		if(a>-1 && a < 1)
		{
			a=x*cos(angle);
		}
		if(b>-1 && b<1)
			b=y*sin(angle);
        //glTranslatef(0,0,z);
		glBindTexture(GL_TEXTURE_2D, e_gal);
		//glColor3f(0,0,1);

		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0,0.0);glVertex2f(a,b);
			glTexCoord2f(0,1.0);glVertex2f(a,b+1);
			glTexCoord2f(1,1.0);glVertex2f(a+1,b+1);
			glTexCoord2f(1.0,0.0);glVertex2f(a+1,b);
		}
		glEnd();
		angle=angle+0.3;
		}
		x=x-0.025;
		y=y-0.01;
		
		//glRectf(a,b,a+2,b+2);
		//glTranslatef(0,0,-z);
	}
}

void Star()
{
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, c_star);
	glBegin(GL_QUADS);
	{
	     glTexCoord3f(0.0,0.0,0.0);glVertex3f(0,0,0);
		 glTexCoord3f(0,1.0,0.0);glVertex3f(0,1,0);
         glTexCoord3f(1.0,1.0,0.0);glVertex3f(1,1,0);
		 glTexCoord3f(1.0,0.0,0.0);glVertex3f(1,0,0);
	}
	glEnd();
	glDisable(GL_BLEND);
}


void
Redraw(void)
    {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(tran<40);
	{
		glPushMatrix();
		glTranslatef(0,0,-10);
		glTranslatef(0,0,tran);
		glDisable(GL_BLEND);
		bigbang();
		glDisable(GL_BLEND);
		glColor3f(0,0,0);
		glPopMatrix();
	}


	if(tran>40)
	{
	glPushMatrix();
	glTranslatef(0,0,-100);
	glColor3f(1,1,1);
	glRectf(0,0,100,100);
	glTranslatef(0,0,+120);
	glPopMatrix();
	glPushMatrix();
	farsight();
	farsight();
	glPopMatrix();

/***************COLLSION********************/
	glPushMatrix();
	glTranslatef(-30,-30,0);

	if(Ascountx1>4 && Ascountx2<-4)
	{
		glPushMatrix();
		glTranslatef(Ascountx1,0,-125);
		glRotatef(90,0,1,0);
		glScalef(1,1,2);
		spheres();
		glTranslatef(-Ascountx1,0,125);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(Ascountx2,0,-125);
		glRotatef(90,0,1,0);
		glScalef(1,1,2);
		spheres();
		glTranslatef(-Ascountx2,0,125);
		glPopMatrix();
	}

if(Ascountx1<=4 && Ascountx1>=-4 && Ascountx2<=4 && Ascountx2>=-4)
	{
		glEnable(GL_BLEND);
		float yc1=xc1*0.5,yc2=xc2*0.5,yc3=xc1*(-0.5),yc4=xc2*(-0.5);
		glPushMatrix();
		glTranslatef(xc1,yc1,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc1,-yc1,125);
		glPopMatrix();
		xc1=xc1-0.1;

		glPushMatrix();
		glTranslatef(xc1,yc3,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc1,-yc3,125);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xc2,yc2,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc2,-yc2,125);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xc2,yc4,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc2,-yc4,125);
		glPopMatrix();

		xc2=xc2+0.1;



		glPushMatrix();
		glTranslatef(0,0,-120);
		//bigbang();
		glTranslatef(-12,-12,0);
		explosion();
		glTranslatef(0,0,120);
		glPopMatrix();
	}
		
	
    if(Ascountx1<4 && Ascountx2>-4)
	{

		glEnable(GL_BLEND);
		float yc1=xc1*0.5,yc2=xc2*0.5,yc3=xc1*(-0.5),yc4=xc2*(-0.5);
		glPushMatrix();
		glTranslatef(xc1,yc1,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc1,-yc1,125);
		glPopMatrix();
		xc1=xc1-0.1;

		glPushMatrix();
		glTranslatef(xc1,yc3,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc1,-yc3,125);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xc2,yc2,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc2,-yc2,125);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(xc2,yc4,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc2,-yc4,125);
		glPopMatrix();

		xc2=xc2+0.1;
		glDisable(GL_BLEND);

	}
	glPopMatrix();


	/***************COLLSION********************/
	glPushMatrix();
	glTranslatef(-30,25,-240);

	if(Ascountx11>4 && Ascountx21<-4)
	{
		glPushMatrix();
		glTranslatef(Ascountx11,0,-125);
		glRotatef(90,0,1,0);
		glScalef(1,1,2);
		spheres();
		glTranslatef(-Ascountx11,0,125);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(Ascountx21,0,-125);
		glRotatef(90,0,1,0);
		glScalef(1,1,2);
		spheres();
		glTranslatef(-Ascountx21,0,125);
		glPopMatrix();
	}

if(Ascountx11<=4 && Ascountx11>=-4 && Ascountx21<=4 && Ascountx21>=-4)
	{
		glEnable(GL_BLEND);
		float yc1=xc1*0.5,yc2=xc2*0.5,yc3=xc1*(-0.5),yc4=xc2*(-0.5);
		glPushMatrix();
		glTranslatef(xc1,yc1,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc1,-yc1,125);
		glPopMatrix();
		xc1=xc1-0.1;

		glPushMatrix();
		glTranslatef(xc1,yc3,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc1,-yc3,125);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xc2,yc2,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc2,-yc2,125);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xc2,yc4,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc2,-yc4,125);
		glPopMatrix();

		xc2=xc2+0.1;



		glPushMatrix();
		glTranslatef(0,0,-120);
		//bigbang();
		glTranslatef(-12,-12,0);
		explosion();
		glTranslatef(0,0,120);
		glPopMatrix();
	}
		
	
    if(Ascountx1<4 && Ascountx2>-4)
	{

		glEnable(GL_BLEND);
		float yc1=xc1*0.5,yc2=xc2*0.5,yc3=xc1*(-0.5),yc4=xc2*(-0.5);
		glPushMatrix();
		glTranslatef(xc1,yc1,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc1,-yc1,125);
		glPopMatrix();
		xc1=xc1-0.1;

		glPushMatrix();
		glTranslatef(xc1,yc3,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc1,-yc3,125);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(xc2,yc2,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc2,-yc2,125);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(xc2,yc4,-125);
		glRotatef(90,0,1,0);
		glScalef(0.4,0.4,1);
		spheres();
		glTranslatef(-xc2,-yc4,125);
		glPopMatrix();

		xc2=xc2+0.1;
		glDisable(GL_BLEND);

	}
	glPopMatrix();
		
	glPushMatrix();
	glTranslatef(0,0,tran);
	//Comet
	//glLoadIdentity();										// Reset The ModelView Matrix
	glPushMatrix();
	glTranslatef(100,-100,0);
	glPushMatrix();
	glTranslatef(-xt,yt,-700);
	comet();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(10,-10,-250);
	glPushMatrix();
	glTranslatef(-xt2,-yt2,zt2);
	comet2();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(10,-10,-500);
	glPushMatrix();
	glTranslatef(xt3,yt3,zt3);
	comet3();
	glPopMatrix();
	glPopMatrix();

	/* START OF STARS*/
	glPushMatrix();
	glTranslatef(1,5,-10);
	Star();
	glTranslatef(-1,-5,10);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,-8,-10);
	Star();
	glTranslatef(6,8,10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5,-7.5,-10);
	Star();
	glTranslatef(3.5,7.5,10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,2,-20);
	Star();
	glTranslatef(-4,-2,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,-30);
	Star();
	glTranslatef(0,0,30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5,1,-30);
	Star();
	glTranslatef(-5,-1,30);
	glPopMatrix();
	
		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-40);
	Star();
	glTranslatef(-10,-10,40);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-40);
	Star();
	glTranslatef(-10,-6,40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,10,-40);
	Star();
	glTranslatef(-6,-10,40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-40);
	Star();
	glTranslatef(-10,-6,40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13,-12,-10);
	Star();
	glTranslatef(13,12,10);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-40);
	Star();
	glTranslatef(-10,-10,40);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-40);
	Star();
	glTranslatef(-10,-6,40);
	glPopMatrix();

	//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-305);
	Star();
	glTranslatef(-10,-10,305);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-310);
	Star();
	glTranslatef(-10,-6,310);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,-10,-315);
	Star();
	glTranslatef(-6,10,315);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(-10,10,-320);
	Star();
	glTranslatef(10,-10,320);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,-6,-325);
	Star();
	glTranslatef(-10,6,325);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-11,-9,-40);
	Star();
	glTranslatef(11,9,40);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-40);
	Star();
	glTranslatef(-10,-10,40);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(2,6,-330);
	Star();
	glTranslatef(-2,-6,330);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7,1.8,-335);
	Star();
	glTranslatef(7,-1.8,335);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(-4.4,7.8,-340);
	Star();
	glTranslatef(4.4,-7.8,340);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,-1,-350);
	Star();
	glTranslatef(-10,1,350);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9,3,-355);
	Star();
	glTranslatef(9,-3,355);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(1,1,-360);
	Star();
	glTranslatef(-1,-1,360);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(1,6,-40);
	Star();
	glTranslatef(-1,-6,40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2,-3,-365);
	Star();
	glTranslatef(2,3,365);

		//Stars.....
	glPushMatrix();
	glTranslatef(-5.9,1,-370);
	Star();
	glTranslatef(5.9,-1,370);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-45);
	Star();
	glTranslatef(-10,-6,45);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,-3.5,-25);
	Star();
	glTranslatef(-4,3.5,25);
	glPopMatrix();
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-35);
	Star();
	glTranslatef(-10,-10,35);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.5,3,-25);
	Star();
	glTranslatef(7.5,-3,25);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(3,3,-375);
	Star();
	glTranslatef(-3,-3,375);
	//glPopMatrix();
	glPushMatrix();
	glTranslatef(3,-7,-50);
	Star();
	glTranslatef(-3,7,50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10,6,-380);
	Star();
	glTranslatef(-10,-6,380);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,10,-385);
	Star();
	glTranslatef(-1,-10,385);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-55);
	Star();
	glTranslatef(-10,-10,55);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,-6,-390);
	Star();
	glTranslatef(-10,6,390);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2,-10,-395);
	Star();
	glTranslatef(-2,10,-395);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-7,-7,-400);
	Star();
	glTranslatef(7,7,400);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(3,-7,-5);
	Star();
	glTranslatef(-3,7,5);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(8,-9,-405);
	Star();
	glTranslatef(-8,9,405);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-2,-8,0);
	Star();
	glTranslatef(2,8,0);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-3,-9,10);
	Star();
	glTranslatef(3,9,-10);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-9,-5,-65);
	Star();
	glTranslatef(9,-5,65);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(10,6.8,-65);
	Star();
	glTranslatef(-10,-6.8,65);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(10,3,-80);
	Star();
	glTranslatef(-10,-3,80);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(3,-7,-50);
	Star();
	glTranslatef(-3,7,50);
	glPopMatrix();

    	glPushMatrix();
	glTranslatef(9,-7,-410);
	Star();
	glTranslatef(-9,7,410);
	glPopMatrix();

	//...............................

	
		//Stars.....
	glPushMatrix();
	glTranslatef(1,5,-70);
	Star();
	glTranslatef(-1,-5,70);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(4,2,-65);
	Star();
	glTranslatef(-4,-2,65);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,-8,-65);
	Star();
	glTranslatef(6,8,65);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5,-7.5,-85);
	Star();
	glTranslatef(3.5,7.5,85);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,2,-80);
	Star();
	glTranslatef(-4,-2,80);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4,2,-75);
	Star();
	glTranslatef(4,-2,75);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(6,8,-70);
	Star();
	glTranslatef(-6,-8,70);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10,-8,-60);
	Star();
	glTranslatef(10,8,60);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-10,8,-65);
	Star();
	glTranslatef(10,-8,65);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(0,0,-76);
	Star();
	glTranslatef(0,0,76);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5,1,-90);
	Star();
	glTranslatef(-5,-1,90);
	glPopMatrix();
	
		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-85);
	Star();
	glTranslatef(-10,-10,85);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-70);
	Star();
	glTranslatef(-10,-6,70);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,10,-55);
	Star();
	glTranslatef(-6,-10,55);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-65);
	Star();
	glTranslatef(-10,-10,65);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-75);
	Star();
	glTranslatef(-10,-6,75);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13,-12,-83);
	Star();
	glTranslatef(13,12,83);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-93);
	Star();
	glTranslatef(-10,-10,93);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-1,6,-95);
	Star();
	glTranslatef(1,-6,95);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,10,-100);
	Star();
	glTranslatef(-6,-10,100);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(2,7,-95);
	Star();
	glTranslatef(-2,-7,95);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-97);
	Star();
	glTranslatef(-10,-6,97);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,-10,-77);
	Star();
	glTranslatef(-6,10,77);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(-10,10,-105);
	Star();
	glTranslatef(10,-10,105);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,-6,-102);
	Star();
	glTranslatef(-10,6,102);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-11,-9,-110);
	Star();
	glTranslatef(11,9,110);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(-5,4,-108);
	Star();
	glTranslatef(5,-4,108);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(3,2,-109);
	Star();
	glTranslatef(-3,-2,109);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7,10,-105);
	Star();
	glTranslatef(7,-10,105);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(1,1,-105);
	Star();
	glTranslatef(-1,-1,105);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,-1,-114);
	Star();
	glTranslatef(6,1,114);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9,3,-110);
	Star();
	glTranslatef(9,-3,110);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-110);
	Star();
	glTranslatef(-10,-10,110);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-115);
	Star();
	glTranslatef(-10,-6,115);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2,-3,-120);
	Star();
	glTranslatef(2,3,120);

		//Stars.....
	glPushMatrix();
	glTranslatef(-6,1,-120);
	Star();
	glTranslatef(6,-1,120);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-1,-6,-120);
	Star();
	glTranslatef(1,6,120);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,-3.5,-117);
	Star();
	glTranslatef(-4,3.5,117);
	glPopMatrix();
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(-10,10,-125);
	Star();
	glTranslatef(10,-10,125);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.5,3,-125);
	Star();
	glTranslatef(7.5,-3,125);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(-8,10,-127);
	Star();
	glTranslatef(8,-10,127);
	//glPopMatrix();
	glPushMatrix();
	glTranslatef(3,-7,-125);
	Star();
	glTranslatef(-3,7,125);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-7,-4.5,-125);
	Star();
	glTranslatef(7,4.5,125);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1,-5,-125);
	Star();
	glTranslatef(1,5,125);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(-9,3,-130);
	Star();
	glTranslatef(9,-3,130);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-10,6,-130);
	Star();
	glTranslatef(10,-6,130);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2,-10,-50);
	Star();
	glTranslatef(-2,10,50);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-7,-7,-50);
	Star();
	glTranslatef(7,7,50);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(3,-7,-5);
	Star();
	glTranslatef(-3,7,5);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(8,-9,-50);
	Star();
	glTranslatef(-8,9,50);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-2,-8,0);
	Star();
	glTranslatef(2,8,0);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-3,-9,10);
	Star();
	glTranslatef(3,9,-10);
	glPopMatrix();

	//

	glPushMatrix();
	glTranslatef(-10,10,-145);
	Star();
	glTranslatef(10,-10,145);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(4,7.8,-150);
	Star();
	glTranslatef(-4,-7.8,150);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.8,9,-155);
	Star();
	glTranslatef(6.8,-9,155);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(-10,-10,-160);
	Star();
	glTranslatef(10,10,160);
	//glPopMatrix();

	//

	glPushMatrix();
	glTranslatef(-8.8,7.7,-165);
	Star();
	glTranslatef(8.8,-7.7,165);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(2.2,4.6,-170);
	Star();
	glTranslatef(-2.2,-4.6,170);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.2,-7,-175);
	Star();
	glTranslatef(-3.2,7,175);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(-9,-9,-180);
	Star();
	glTranslatef(9,9,180);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,9.2,-185);
	Star();
	glTranslatef(6,-9.2,185);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(7,3,-190);
	Star();
	glTranslatef(-7,-3,190);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2,-8,-195);
	Star();
	glTranslatef(2,8,195);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(1,-1,-200);
	Star();
	glTranslatef(-1,1,200);
	//glPopMatrix();

	//...............................

		glPushMatrix();
	glTranslatef(3,-7,-150);
	Star();
	glTranslatef(-3,7,150);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(7,-9,-100);
	Star();
	glTranslatef(-7,-9,100);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(23,-17,-50);
	Star();
	glTranslatef(-23,17,50);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(6,10,-40);
	Star();
	glTranslatef(-6,-10,40);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-40);
	Star();
	glTranslatef(-10,-10,40);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-40);
	Star();
	glTranslatef(-10,-6,40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,10,-40);
	Star();
	glTranslatef(-6,-10,40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8.8,-7,-205);
	Star();
	glTranslatef(8.8,7,205);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-3,7.7,-210);
	Star();
	glTranslatef(3,-7.7,210);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.6,2.3,-215);
	Star();
	glTranslatef(-5.6,-2.3,215);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(9,-5.5,-220);
	Star();
	glTranslatef(-9,5.5,220);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4,-3.3,-225);
	Star();
	glTranslatef(4,3.3,225);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8.9,3,-230);
	Star();
	glTranslatef(8.9,4,230);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9,1,-235);
	Star();
	glTranslatef(-9,-1,235);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(3,-9,-240);
	Star();
	glTranslatef(-3,9,240);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9,-9,-245);
	Star();
	glTranslatef(9,9,245);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,3,-250);
	Star();
	glTranslatef(6,-3,250);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,9,-255);
	Star();
	glTranslatef(-1,-9,255);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(6.9,-4,-260);
	Star();
	glTranslatef(-6.9,4,260);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4,-6.3,-265);
	Star();
	glTranslatef(4,6.3,265);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.5,3,-270);
	Star();
	glTranslatef(5.5,3,270);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5,2.3,-275);
	Star();
	glTranslatef(-5,-2.3,275);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(9,-3,-280);
	Star();
	glTranslatef(-9,3,280);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7,-4,-285);
	Star();
	glTranslatef(7,4,285);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.9,9,-290);
	Star();
	glTranslatef(5.9,-9,290);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.9,9,-415);
	Star();
	glTranslatef(5.9,-9,415);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-6,-9,-418);
	Star();
	glTranslatef(6,9,418);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(4,5,-422);
	Star();
	glTranslatef(-4,-5,422);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-3.3,6.2,-428);
	Star();
	glTranslatef(3.3,-6.2,428);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-9,3,-435);
	Star();
	glTranslatef(9,-3,435);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,4,-438);
	Star();
	glTranslatef(-10,-4,438);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(5,-5,-440);
	Star();
	glTranslatef(-5,5,440);
	glPopMatrix();

	//Stars.....
	glPushMatrix();
	glTranslatef(1,5,-440);
	Star();
	glTranslatef(-1,-5,440);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,-8,-445);
	Star();
	glTranslatef(6,8,445);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5,-7.5,-450);
	Star();
	glTranslatef(3.5,7.5,450);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,2,-455);
	Star();
	glTranslatef(-4,-2,455);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,-460);
	Star();
	glTranslatef(0,0,460);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5,1,-465);
	Star();
	glTranslatef(-5,-1,465);
	glPopMatrix();
	
		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-470);
	Star();
	glTranslatef(-10,-10,470);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-475);
	Star();
	glTranslatef(-10,-6,475);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,10,-480);
	Star();
	glTranslatef(-6,-10,480);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-485);
	Star();
	glTranslatef(-10,-6,485);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13,-12,-490);
	Star();
	glTranslatef(13,12,490);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-495);
	Star();
	glTranslatef(-10,-10,495);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-500);
	Star();
	glTranslatef(-10,-6,500);
	glPopMatrix();

	//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-505);
	Star();
	glTranslatef(-10,-10,505);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-510);
	Star();
	glTranslatef(-10,-6,510);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,-10,-515);
	Star();
	glTranslatef(-6,10,515);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(-10,10,-520);
	Star();
	glTranslatef(10,-10,520);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,-6,-525);
	Star();
	glTranslatef(-10,6,525);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-11,-9,-530);
	Star();
	glTranslatef(11,9,530);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-535);
	Star();
	glTranslatef(-10,-10,535);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(2,6,-540);
	Star();
	glTranslatef(-2,-6,540);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7,1.8,-545);
	Star();
	glTranslatef(7,-1.8,545);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(-4.4,7.8,-550);
	Star();
	glTranslatef(4.4,-7.8,550);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,-1,-550);
	Star();
	glTranslatef(-10,1,550);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9,3,-555);
	Star();
	glTranslatef(9,-3,555);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(1,1,-560);
	Star();
	glTranslatef(-1,-1,560);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(1,6,-570);
	Star();
	glTranslatef(-1,-6,570);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2,-3,-565);
	Star();
	glTranslatef(2,3,565);

		//Stars.....
	glPushMatrix();
	glTranslatef(-5.9,1,-570);
	Star();
	glTranslatef(5.9,-1,570);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-575);
	Star();
	glTranslatef(-10,-6,575);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,-3.5,-580);
	Star();
	glTranslatef(-4,3.5,580);
	glPopMatrix();
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-585);
	Star();
	glTranslatef(-10,-10,585);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.5,3,-590);
	Star();
	glTranslatef(7.5,-3,590);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(3,3,-595);
	Star();
	glTranslatef(-3,-3,595);
	//glPopMatrix();
	glPushMatrix();
	glTranslatef(3,-7,-600);
	Star();
	glTranslatef(-3,7,600);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10,6,-605);
	Star();
	glTranslatef(-10,-6,605);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,10,-610);
	Star();
	glTranslatef(-1,-10,610);
	glPopMatrix();

		//Stars.....
	glPushMatrix();
	glTranslatef(10,10,-615);
	Star();
	glTranslatef(-10,-10,615);
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(10,-6,-620);
	Star();
	glTranslatef(-10,6,620);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2,-10,-625);
	Star();
	glTranslatef(-2,10,625);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-7,-7,-630);
	Star();
	glTranslatef(7,7,630);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(3,-7,-635);
	Star();
	glTranslatef(-3,7,635);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(8,-9,-640);
	Star();
	glTranslatef(-8,9,640);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-2,-8,645);
	Star();
	glTranslatef(2,8,645);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-3,-9,650);
	Star();
	glTranslatef(3,9,-650);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-9,-5,-655);
	Star();
	glTranslatef(9,-5,655);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(10,6.8,-650);
	Star();
	glTranslatef(-10,-6.8,650);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(10,3,-665);
	Star();
	glTranslatef(-10,-3,665);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(3,-7,-670);
	Star();
	glTranslatef(-3,7,670);
	glPopMatrix();

    	glPushMatrix();
	glTranslatef(9,-7,-675);
	Star();
	glTranslatef(-9,7,675);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,5,-680);
	Star();
	glTranslatef(-1,-5,680);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,2,-685);
	Star();
	glTranslatef(-4,-2,685);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,-8,-690);
	Star();
	glTranslatef(6,8,690);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5,-7.5,-695);
	Star();
	glTranslatef(3.5,7.5,695);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,2,-700);
	Star();
	glTranslatef(-4,-2,700);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4,2,-710);
	Star();
	glTranslatef(4,-2,710);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(6,8,-715);
	Star();
	glTranslatef(-6,-8,715);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10,-8,-720);
	Star();
	glTranslatef(10,8,720);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10,8,-725);
	Star();
	glTranslatef(10,-8,725);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,-730);
	Star();
	glTranslatef(0,0,730);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5,1,-735);
	Star();
	glTranslatef(-5,-1,735);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(10,10,-740);
	Star();
	glTranslatef(-10,-10,740);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-745);
	Star();
	glTranslatef(-10,-6,745);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,10,-750);
	Star();
	glTranslatef(-6,-10,750);
	glPopMatrix();
		
	glPushMatrix();
	glTranslatef(10,10,-755);
	Star();
	glTranslatef(-10,-10,755);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-760);
	Star();
	glTranslatef(-10,-6,760);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13,-12,-765);
	Star();
	glTranslatef(13,12,765);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,10,-770);
	Star();
	glTranslatef(-10,-10,770);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1,6,-775);
	Star();
	glTranslatef(1,-6,775);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,10,-780);
	Star();
	glTranslatef(-6,-10,780);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2,7,-785);
	Star();
	glTranslatef(-2,-7,785);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-790);
	Star();
	glTranslatef(-10,-6,790);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,-10,-795);
	Star();
	glTranslatef(-6,10,795);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10,10,-800);
	Star();
	glTranslatef(10,-10,800);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,-6,-805);
	Star();
	glTranslatef(-10,6,805);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-11,-9,-810);
	Star();
	glTranslatef(11,9,810);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5,4,-815);
	Star();
	glTranslatef(5,-4,815);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3,2,-820);
	Star();
	glTranslatef(-3,-2,820);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7,10,-825);
	Star();
	glTranslatef(7,-10,825);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,1,-820);
	Star();
	glTranslatef(-1,-1,820);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,-1,-830);
	Star();
	glTranslatef(6,1,830);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9,3,-835);
	Star();
	glTranslatef(9,-3,835);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,10,-840);
	Star();
	glTranslatef(-10,-10,840);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-845);
	Star();
	glTranslatef(-10,-6,845);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2,-3,-850);
	Star();
	glTranslatef(2,3,850);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,1,-855);
	Star();
	glTranslatef(6,-1,855);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1,-6,-860);
	Star();
	glTranslatef(1,6,860);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,-3.5,-865);
	Star();
	glTranslatef(-4,3.5,865);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-10,10,-870);
	Star();
	glTranslatef(10,-10,870);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.5,3,-875);
	Star();
	glTranslatef(7.5,-3,875);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8,10,-880);
	Star();
	glTranslatef(8,-10,880);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3,-7,-885);
	Star();
	glTranslatef(-3,7,885);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7,-4.5,-890);
	Star();
	glTranslatef(7,4.5,890);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1,-5,-885);
	Star();
	glTranslatef(1,5,885);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9,3,-890);
	Star();
	glTranslatef(9,-3,890);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10,6,-900);
	Star();
	glTranslatef(10,-6,900);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2,-10,-895);
	Star();
	glTranslatef(-2,10,895);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7,-7,-905);
	Star();
	glTranslatef(7,7,905);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3,-7,-910);
	Star();
	glTranslatef(-3,7,910);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8,-9,-915);
	Star();
	glTranslatef(-8,9,915);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2,-8,920);
	Star();
	glTranslatef(2,8,920);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3,-9,925);
	Star();
	glTranslatef(3,9,-925);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10,10,-930);
	Star();
	glTranslatef(10,-10,930);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4,7.8,-935);
	Star();
	glTranslatef(-4,-7.8,935);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.8,9,-940);
	Star();
	glTranslatef(6.8,-9,940);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10,-10,-950);
	Star();
	glTranslatef(10,10,950);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8.8,7.7,-965);
	Star();
	glTranslatef(8.8,-7.7,965);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.2,4.6,-955);
	Star();
	glTranslatef(-2.2,-4.6,955);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.2,-7,-960);
	Star();
	glTranslatef(-3.2,7,960);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9,-9,-970);
	Star();
	glTranslatef(9,9,970);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6,9.2,-975);
	Star();
	glTranslatef(6,-9.2,975);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7,3,-980);
	Star();
	glTranslatef(-7,-3,980);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2,-8,-985);
	Star();
	glTranslatef(2,8,985);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,-1,-990);
	Star();
	glTranslatef(-1,1,990);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(3,-7,-450);
	Star();
	glTranslatef(-3,7,450);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7,-9,-300);
	Star();
	glTranslatef(-7,-9,300);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(23,-17,-450);
	Star();
	glTranslatef(-23,17,450);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,10,-440);
	Star();
	glTranslatef(-6,-10,440);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,10,-340);
	Star();
	glTranslatef(-10,-10,340);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10,6,-240);
	Star();
	glTranslatef(-10,-6,240);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(10,4,-295);
	Star();
	glTranslatef(-10,-4,295);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5,-5,-300);
	Star();
	glTranslatef(-5,5,300);
	glPopMatrix();
	/*End of the stars*/
	
	/*Start of Asteroids*/
	glPushMatrix();
	glTranslatef(-20,0,-30);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,1,2);
	spheres();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(40,30,-95);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,2,1);
	spheres();
	glTranslatef(40,30,-95);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40,10,-195);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,2,1);
	spheres();
	glTranslatef(40,10,-195);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40,20,-205);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,2,1);
	spheres();
	glTranslatef(40,-20,-205);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-35,-30,-150);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,2,1);
	spheres();
	glTranslatef(35,30,150);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(147,39,-123);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,2,1);
	spheres();
	glTranslatef(-147,-39,123);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(40,30,-295);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,2,1);
	spheres();
	glTranslatef(40,30,-295);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-140,-30,-590);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,2,1);
	spheres();
	glTranslatef(140,30,590);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20,-50,-250);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,2,1);
	spheres();
	glTranslatef(-20,50,250);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(67,23,-750);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,2,1);
	spheres();
	glTranslatef(-67,-23,750);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100,0,-1000);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,2,1);
	spheres();
	glTranslatef(100,0,1000);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23,40,-175);
	glRotatef(ast_rot,0,1,0);
	spheres();
	glTranslatef(23,-40,175);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-30,410,-1000);
	glRotatef(ast_rot,0,1,0);
	spheres();
	glTranslatef(30,-410,1000);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-203,40,-750);
	glRotatef(ast_rot,0,1,0);
	spheres();
	glTranslatef(203,-40,750);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-123,140,-750);
	glRotatef(ast_rot,0,1,0);
	spheres();
	glTranslatef(123,-140,750);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(30,40,-500);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,2,1);
	spheres();
	glTranslatef(-30,-40,-500);
	glPopMatrix();

		
	glPushMatrix();
	glEnable(GL_BLEND);
	glTranslatef(30,40,-500);
	glRotatef(ast_rot,0,1,0);
	glScalef(1,2,1);
	spheres();
	glTranslatef(-30,-40,-500);
	glPopMatrix();
	
	glPopMatrix();
	/*END OF ASTERIODS*/


	/*Spiral galaxy*/

	glPushMatrix();
	s_galaxy(-10,23,-200,-30,0,0,1);
	s_galaxy(10,-50,-350,30,0,0,1);
	s_galaxy(-100,-150,-500,60,0,0,1);
	s_galaxy(150,-150,-750,-45,0,0,1);
	s_galaxy(20,-50,-800,30,0,0,1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(50,-50,-250);
	eGalaxy();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glPopMatrix();
	}
	glutSwapBuffers();
}

void
Resize(int width, 
       int height) 
    {
	Width  = width;
    Height = height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)width / (float)height, 0.1, 15000.0);
    glMatrixMode(GL_MODELVIEW);
    }
int                
main(int  argc,    /* I - Number of command-line arguments */
     char *argv[]) /* I - Command-line arguments */
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(750, 500);
    glutCreateWindow("Space Explorer");
	glutFullScreen();
    glutDisplayFunc(Redraw);
	glutReshapeFunc(Resize);
    

	obj = gluNewQuadric();
    gluQuadricTexture(obj,GL_TRUE);

     s_gal= TextureLoad("/Users/stephenjohnrussell/dev/CyberWalkers/CyberWalkers/data/c_star.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR,
                                GL_REPEAT);
	Planet = TextureLoad("/Users/stephenjohnrussell/dev/CyberWalkers/CyberWalkers/data/asteroid.bmp",GL_FALSE,GL_LINEAR,GL_LINEAR,GL_REPEAT);

	background = TextureLoad("/Users/stephenjohnrussell/dev/CyberWalkers/CyberWalkers/data/sgal.bmp",GL_FALSE,GL_LINEAR,GL_LINEAR,GL_REPEAT);
	c_star= TextureLoad("/Users/stephenjohnrussell/dev/CyberWalkers/CyberWalkers/data/c_star.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR,
                                GL_REPEAT);
	e_gal= TextureLoad("/Users/stephenjohnrussell/dev/CyberWalkers/CyberWalkers/data/c_star.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR,
                                GL_REPEAT);
	glutTimerFunc(33, TimerFunction, 1);
	setuprc();   
    glutMainLoop();
    return (0);
    }























