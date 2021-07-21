
#include <iostream>
#include <fstream>
#include <climits>
#include <math.h>
#include <GL/freeglut.h>
using namespace std;

//--Globals ---------------------------------------------------------------
float *x, *y, *z;       //vertex coordinate arrays
int *t1, *t2, *t3;      //triangles
int nvrt, ntri;         //total number of vertices and triangles
float angle = -10.0;    //Rotation angle for viewing
float cam_hgt = 100;





void fencepost()
{
	glColor3f(0.5, 0.4, 0.06);      //Head
    glPushMatrix();
      glTranslatef(0, 7.7, 3);
      glScalef(1, 15, 1);
      glutSolidCube(5);
    glPopMatrix();

    glColor3f(0.5, 0.35, 0.05);          //Torso
    glPushMatrix();
		glTranslatef(0, 35, 0);
		glScalef(4, 0.4, 0.2);
		glutSolidCube(20);
    glPopMatrix();
    
    glColor3f(0.5, 0.35, 0.05);          //Torso
    glPushMatrix();
		glTranslatef(0, 15, 0);
		glScalef(4, 0.4, 0.2);
		glutSolidCube(20);
    glPopMatrix();
}

void fence()
{
    glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 50);
        glVertex3f(0, 75, 0);
        glVertex3f(0, 50, 50);
        glVertex3f(0, 75, 75);
        glVertex3f(0, 50, 75);
    glEnd();
}


//--Function to compute the normal vector of a triangle with index tindx ----------
void normal(int tindx)
{
    float x1 = x[t1[tindx]], x2 = x[t2[tindx]], x3 = x[t3[tindx]];
    float y1 = y[t1[tindx]], y2 = y[t2[tindx]], y3 = y[t3[tindx]];
    float z1 = z[t1[tindx]], z2 = z[t2[tindx]], z3 = z[t3[tindx]];
    float nx, ny, nz;
    nx = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
    ny = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
    nz = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}


//----------draw a floor plane-------------------
void drawFloor()
{
    bool flag = false;

    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    for(int x = -400; x <= 400; x += 20)
    {
        for(int z = -400; z <= 400; z += 20)
        {
            if(flag) glColor3f(0.6, 1.0, 0.8);
            else glColor3f(0.8, 1.0, 0.6);
            glVertex3f(x, 0, z);
            glVertex3f(x, 0, z+20);
            glVertex3f(x+20, 0, z+20);
            glVertex3f(x+20, 0, z);
            flag = !flag;
        }
    }
    glEnd();
}

//--Display: ----------------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()
{
    float lpos[4] = {100., 100., 100., 1.0};  //light's position

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //GL_LINE = Wireframe;   GL_FILL = Solid
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, cam_hgt, 200, 0, 0, 0, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);   //set light position

    glRotatef(angle, 0.0, 1.0, 0.0);        //rotate the whole scene

    drawFloor();

    
	fence();



    glFlush();
}

//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   //Background colour

    glEnable(GL_LIGHTING);                  //Enable OpenGL states
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 50, 1000);  //The camera view volume
}

//------------ Special key event callback ---------------------------------
// To enable the use of left and right arrow keys to rotate the scene
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT) angle--;
    else if(key == GLUT_KEY_RIGHT) angle++;
    else if(key == GLUT_KEY_UP) cam_hgt++;
    else if(key == GLUT_KEY_DOWN) cam_hgt--;

    if(cam_hgt > 200) cam_hgt = 200;
    else if(cam_hgt < 10) cam_hgt = 10;

    glutPostRedisplay();
}





//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH);
   glutInitWindowSize (800, 800);
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("Cannon");
   initialize();
   
   glutDisplayFunc(display);
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}
