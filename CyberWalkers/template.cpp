// ----------------------------------------------------------------------------
// Simple sample to prove that Assimp is easy to use with OpenGL.
// It takes a file name as command line parameter, loads it using standard
// settings and displays it.
//
// If you intend to _use_ this code sample in your app, do yourself a favour
// and replace immediate mode calls with VBOs ...
//
// The vc8 solution links against assimp-release-dll_win32 - be sure to
// have this configuration built.
// ----------------------------------------------------------------------------

#include <stdlib.h>

#include <GLUT/glut.h>

// assimp include files. These three are usually needed.
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


// current rotation angle
static float angle = 0.f;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

// ----------------------------------------------------------------------------
void reshape(int width, int height)
{
	const double aspectRatio = (float) width / height, fieldOfView = 45.0;
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fieldOfView, aspectRatio,
                   1.0, 1000.0);  /* Znear and Zfar */
	glViewport(0, 0, width, height);
}


// ----------------------------------------------------------------------------
void display(void)
{
	float tmp;
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.f,0.f,3.f,0.f,0.f,-5.f,0.f,1.f,0.f);
    
	// rotate it around the y axis
	glRotatef(angle,0.f,1.f,0.f);
    
	// scale the whole asset to fit into our view frustum
	tmp = scene_max.x-scene_min.x;
	tmp = aisgl_max(scene_max.y - scene_min.y,tmp);
	tmp = aisgl_max(scene_max.z - scene_min.z,tmp);
	tmp = 1.f / tmp;
	glScalef(tmp, tmp, tmp);
    
    // center the model
	glTranslatef( -scene_center.x, -scene_center.y, -scene_center.z );
    
    // if the display list has not been made yet, create a new one and
    // fill it with scene contents
	if(scene_list == 0) {
	    scene_list = glGenLists(1);
	    glNewList(scene_list, GL_COMPILE);
        // now begin at the root node of the imported data and traverse
        // the scenegraph by multiplying subsequent local transforms
        // together on GL's matrix stack.
	    recursive_render(scene, scene->mRootNode);
	    glEndList();
	}
    
	glCallList(scene_list);
    
	glutSwapBuffers();
    
	do_motion();
}

// ----------------------------------------------------------------------------
int loadasset (const char* path)
{
	// we are taking one of the postprocessing presets to avoid
	// spelling out 20+ single postprocessing flags here.
	scene = aiImportFile(path,aiProcessPreset_TargetRealtime_MaxQuality);
    
	if (scene) {
		get_bounding_box(&scene_min,&scene_max);
		scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
		scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
		scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
		return 0;
	}
	return 1;
}

// ----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	struct aiLogStream stream;
    
	glutInitWindowSize(900,600);
	glutInitWindowPosition(100,100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
    
	glutCreateWindow("Assimp - Very simple OpenGL sample");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    
	// get a handle to the predefined STDOUT log stream and attach
	// it to the logging system. It remains active for all further
	// calls to aiImportFile(Ex) and aiApplyPostProcessing.
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
	aiAttachLogStream(&stream);
    
	// ... same procedure, but this stream now writes the
	// log messages to assimp_log.txt
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_FILE,"assimp_log.txt");
	aiAttachLogStream(&stream);
    
	// the model name can be specified on the command line. If none
	// is specified, we try to locate one of the more expressive test
	// models from the repository (/models-nonbsd may be missing in
	// some distributions so we need a fallback from /models!).
	if( 0 != loadasset( argc >= 2 ? argv[1] : "../../test/models-nonbsd/X/dwarf.x")) {
		if( argc != 1 || (0 != loadasset( "../../../../test/models-nonbsd/X/dwarf.x") && 0 != loadasset( "../../test/models/X/Testwuson.X"))) {
			return -1;
		}
	}
    
	glClearColor(0.1f,0.1f,0.1f,1.f);
    
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);    // Uses default lighting parameters
    
	glEnable(GL_DEPTH_TEST);
    
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);
    
	// XXX docs say all polygons are emitted CCW, but tests show that some aren't.
	if(getenv("MODEL_IS_BROKEN"))
		glFrontFace(GL_CW);
    
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    
	glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
    
	// cleanup - calling 'aiReleaseImport' is important, as the library
	// keeps internal resources until the scene is freed again. Not 
	// doing so can cause severe resource leaking.
	aiReleaseImport(scene);
    
	// We added a log stream to the library, it's our job to disable it
	// again. This will definitely release the last resources allocated
	// by Assimp.
	aiDetachAllLogStreams();
	return 0;
}
