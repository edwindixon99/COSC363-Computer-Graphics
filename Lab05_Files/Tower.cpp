//===================================================================
//  COSC363 Computer Graphics (2020). University of Canterbury.
//
//  Tower.cpp
//  See Lab05.pdf for details
//===================================================================

#include <cmath>
#include <GL/freeglut.h>
#include "loadBMP.h"
using namespace std;

#define PI 3.14159265

GLuint txId;			//Texture id
float viewAngle = 0.0;	//Camera view angle

//--------Loads a bitmap texture------------------------------------------
void loadTexture()				
{
	glGenTextures(1, &txId); 				// Create a Texture object
	glBindTexture(GL_TEXTURE_2D, txId);		//Use this texture
    loadBMP("TowerTexture.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

//-----Computes surface normal vector-------------------------------
void normal(float x1, float y1, float z1,
            float x2, float y2, float z2,
            float x3, float y3, float z3 )
{
    float nx, ny, nz;
    nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
    ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
    nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}

//-----------------------------------------------------------------------
void initialise(void)
{
//=====Uncomment the following 3 lines before implementing texture mapping=====
	loadTexture();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId);
//=============================================================================
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0., 0., 0.);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, 1.0, 40.0, 1000.);;
}


//------------------------------------------------------------------ 
void display(void) 
{ 
	float theta = -10;
	float lpos[4]={-100., 100., 0., 1.};	//light's position
	float eye_x, eye_z;						//Camera position
	const float CDR = 3.14159265/180.0;		//Degrees to radians conversion factor
	const int N = 19;						//Number of vertices of the base polygon

    float vx[N] = {0., 8., 11., 11., 10.4, 9.5, 8., 6., 3., 0., -3., -6., -8., -9.5, -10.4, -11., -11., -8., 0.};
    float vy[N] = {0};
    float vz[N] = {19.4, 8., 5., 0., -4., -8., -11., -12., -12.4, -12.5, -12.4, -12., -11., -8., -4., 0., 5., 8., 19.4};
    float wx[N], wy[N], wz[N];
    
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	eye_x = 150.0 * sin(viewAngle*CDR);   //Update camera position
	eye_z = 150.0 * cos(viewAngle*CDR);

	gluLookAt(eye_x, 100.0, eye_z, 0.0, 100.0, 0.0, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	
    glColor3f(0., 1., 1.);
    
// ==== Remove the following 5 lines of code and replace with a 3D model! ====

// ============================================================================
	float text[N] = {0,0.15,0.2,0.25,0.3,0.35,0.4,0.433,0.466,0.499,0.5322, 0.655,0.6,0.65,0.7,0.75,0.8,0.85,1};
	for(int j = 0; j < 8; j++) //36 slices in 10 deg steps
	{
		for(int i = 0; i < N; i++) //N vertices along each slice
		{
			wx[i] = vx[i] * cos(theta * PI / 180.0) + vz[i] * sin(theta * PI / 180.0); 
			wy[i] = vy[i] + 20;
			wz[i] = -vx[i] * sin(theta * PI / 180.0) + vz[i] * cos(theta * PI / 180.0);
		 }
		 
		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i < N; i++) {
			
			glTexCoord2f(text[i], 0);
			 glVertex3f(vx[i], vy[i], vz[i]);
			 
			 if(i > 0) normal(wx[i-1], wy[i-1], wz[i-1],
			 vx[i], vy[i], vz[i],
			 wx[i], wy[i], wz[i]);
			 
			 glTexCoord2f(text[i], 1);
			 glVertex3f(wx[i], wy[i], wz[i]);
			 
		}
		glEnd();

		for(int i = 0; i < N; i++) //N vertices along each slice
		{
			vx[i] = wx[i];
			vy[i] = wy[i];
			vz[i] = wz[i]; 
		 }
	 }





	glFlush(); 
} 


//-------special keyboard function callback-------------------------------
void special(int key, int xp, int yp)
{
	if(key==GLUT_KEY_LEFT)
		viewAngle += 5.0;
	else if(key==GLUT_KEY_RIGHT)
		viewAngle -= 5.0;
	glutPostRedisplay();
}


//------------------------------------------------------------------- 
int main(int argc, char **argv) 
{ 
	glutInit(&argc, argv);            
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);  
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("The Turning Torso");
	initialise();
	glutDisplayFunc(display); 
	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}

