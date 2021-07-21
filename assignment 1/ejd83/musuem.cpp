//  ========================================================================
//  COSC363: Computer Graphics (2020); CSSE  University of Canterbury.
//
//  FILE NAME: Yard.cpp
//  See Lab03.pdf for details.
//  ========================================================================

#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "loadTGA.h"
#include "cannon.h"
#include "armyMen.h"
#include "models.h"
#include <fstream>
#include <climits>
#include <math.h>
#include <GL/freeglut.h>
using namespace std;

GLuint txId[9];   //Texture ids
float angle=0, look_x, look_z=-1, eye_x, eye_z=25;  //Camera parameters
float moving = 0.1;
float moving2 = -2.14;
GLUquadric *q;
float gx = -10;
float gy = 25;
float gz = 40;
float shadowMat[16] = { gy,0,0,0, -gx,0,-gz,-1,
0,0,gy,0, 0,0,0,gy };
float black[3] = {0, 0, 0};
float white[3] = {1, 1, 1};
//--------------------------------------------------------------------------------
void loadTexture()
{
    glGenTextures(9, txId);     // Create 3 texture ids

    glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture
    loadTGA("Wall.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[2]);  //Use this texture
    loadTGA("grass.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    
    
	glBindTexture(GL_TEXTURE_2D, txId[3]);  //Use this texture
    loadTGA("nx.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    
    glBindTexture(GL_TEXTURE_2D, txId[4]);  //Use this texture
    loadTGA("pz.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    
    
    glBindTexture(GL_TEXTURE_2D, txId[5]);  //Use this texture
    loadTGA("px.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    
    glBindTexture(GL_TEXTURE_2D, txId[6]);  //Use this texture
    loadTGA("nz.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, txId[7]);  //Use this texture
    loadTGA("py.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, txId[8]);  //Use this texture
    loadTGA("wood.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
}

//--------------------------------------------------------------------------------
void special(int key, int x, int y)
{
	if(key == GLUT_KEY_LEFT) {
		angle -= 0.1;  //Change direction
	} else if(key == GLUT_KEY_RIGHT) {
		 angle += 0.1;
	} else if(key == GLUT_KEY_DOWN)
	{  //Move backward
		eye_x -= 0.1*sin(angle);
		eye_z += 0.1*cos(angle);
	}
	else if(key == GLUT_KEY_UP)
	{ //Move forward
		eye_x += 0.1*sin(angle);
		eye_z -= 0.1*cos(angle);
	}

	look_x = eye_x + 100*sin(angle);
	look_z = eye_z - 100*cos(angle);
	
	if (eye_z > 52) {
	eye_z = 52;
	}
	if (eye_z < -20) {
		eye_z = -20;
	}
	if (eye_x > 32) {
		eye_x = 32;
	}
	if (eye_x < -32) { 
		eye_x = -32;
	}
	glutPostRedisplay();
}


void skybox()
{
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
    
    
    ////////////////////// LEFT WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-32, 32, 32);
    glTexCoord2f(1.0, 0.0); glVertex3f(-32, 32, -32);
    glTexCoord2f(1.0, 1.0); glVertex3f(-32, 0, -32);
    glTexCoord2f(0.0, 1.0); glVertex3f(-32, 0, 32);
	glEnd();
	
	////////////////////// FRONT WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[6]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(32, 32, 32);
    glTexCoord2f(1.0, 0.0); glVertex3f(-32, 32, 32);
    glTexCoord2f(1.0, 1.0); glVertex3f(-32, 0, 32);
    glTexCoord2f(0.0, 1.0); glVertex3f(32, 0, 32);
    glEnd();
    
    
    ////////////////////// RIGHT WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(32, 32, 32);
    glTexCoord2f(1.0, 0.0); glVertex3f(32, 32, -32);
    glTexCoord2f(1.0, 1.0); glVertex3f(32, 0, -32);
    glTexCoord2f(0.0, 1.0); glVertex3f(32, 0, 32);
	glEnd();
	
	
    ////////////////////// BACK WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, txId[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(32, 32, -32);
    glTexCoord2f(1.0, 0.0); glVertex3f(-32, 32, -32);
    glTexCoord2f(1.0, 1.0); glVertex3f(-32, 0, -32);
    glTexCoord2f(0.0, 1.0); glVertex3f(32, 0, -32);
    glEnd();
    
	
	////////////////////// TOP WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, txId[7]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-32, 32, -32);
    glTexCoord2f(1.0, 0.0); glVertex3f(32, 32, -32);
    glTexCoord2f(1.0, 1.0); glVertex3f(32, 32, 32);
    glTexCoord2f(0.0, 1.0); glVertex3f(-32, 32, 32);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);
}

//--------------------------------------------------------------------------------
void lighting()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//~ glEnable(GL_LIGHT1);
	float light_pos[] = {gx, gy, gz, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	
	//~ //glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	float gray[3] = {0.2, 0.2, 0.2};
	//~ float cyan[3] = {0, 1, 1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, gray);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, gray);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,10.0);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);
	
}



void initialise()
{
	loadMeshFile("Cannon.off");
    loadTexture();
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0., 1., 1., 1.);    //Background colour
    glDisable(GL_TEXTURE_2D);
    
    
    
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//--------------------------------------------------------------------------------

void walls()
{	
    glBindTexture(GL_TEXTURE_2D, txId[0]);  //replace with a texture
	glEnable(GL_NORMALIZE);
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glBegin(GL_QUADS);

    ////////////////////// FRONT WALL LEFT ///////////////////////
	glNormal3f(0, 0, 1);
    glTexCoord2f(0.0, 0.0); glVertex3f(-15, 0, 15);
    glTexCoord2f(12.0, 0.0); glVertex3f(-2.5, 0, 15);
    glTexCoord2f(12.0, 2.0); glVertex3f(-2.5, 2, 15);
    glTexCoord2f(0.0, 2.0); glVertex3f(-15, 2, 15);
    
    
    ////////////////////// FRONT WALL RIGHT ///////////////////////
	glNormal3f(0, 0, 1);
    glTexCoord2f(0.0, 2.0); glVertex3f(2.5, 2, 15);
    glTexCoord2f(12.0, 2.0); glVertex3f(15, 2, 15);
    glTexCoord2f(12.0, 0.0); glVertex3f(15, 0, 15);
    glTexCoord2f(0.0, 0.0); glVertex3f(2.5, 0, 15);


    ////////////////////// BACK WALL ///////////////////////
	glNormal3f(0, 0, 1);
    glTexCoord2f(0.0, 2.0); glVertex3f(-15, 2, -5);
    glTexCoord2f(12.0, 2.0); glVertex3f(15, 2, -5);
    glTexCoord2f(12.0, 0.0); glVertex3f(15, 0, -5);
    glTexCoord2f(0.0, 0.0); glVertex3f(-15, 0, -5);
    
    
    ////////////////////// LEFT WALL ///////////////////////
    glNormal3f(1, 0, 0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-15, 0, -5);
    glTexCoord2f(12.0, 0.0); glVertex3f(-15, 0, 15);
    glTexCoord2f(12.0, 2.0); glVertex3f(-15, 2, 15);
    glTexCoord2f(0.0, 2.0); glVertex3f(-15, 2, -5);


    ////////////////////// RIGHT WALL ///////////////////////
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0.0, 0.0); glVertex3f(15, 0, -5);
    glTexCoord2f(12.0, 0.0); glVertex3f(15, 0, 15);
    glTexCoord2f(12.0, 2.0); glVertex3f(15, 2, 15);
    glTexCoord2f(0.0, 2.0); glVertex3f(15, 2, -5);

    glEnd();
    glDisable(GL_NORMALIZE);
}
//--------------------------------------------------------------------------------

void muesuemFloor()
{
	glEnable(GL_BLEND);
    glColor4f(0.7, 0.7, 0.7, 1.0);  //The floor is gray in colour
    glNormal3f(0.0, 1.0, 0.0);

    //The floor is made up of several tiny squares on a 200x200 grid. Each square has a unit size.
    glBegin(GL_QUADS);
    for(float i = -15; i < 15; i+= 0.1)
    {
        for(float j = -5; j < 15; j+= 0.1)
        {
            glVertex3f(i, -0.0003, j);
            glVertex3f(i, -0.0003, j+0.1);
            glVertex3f(i+0.1, -0.0003, j+0.1);
            glVertex3f(i+0.1, -0.0003, j);
        }
    }
    glEnd();
    glDisable(GL_BLEND);
}

//--------------------------------------------------------------------------------

void floor()
{
	glColor4f(0, 1, 0, 1.0);
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[2]);  //replace with a texture

    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 128.0);    glVertex3f(-100, -0.01, -100);
        glTexCoord2f(0.0, 0.0);     glVertex3f(-100, -0.01, 100);
        glTexCoord2f(128.0, 0.0);    glVertex3f(100, -0.01, 100);
        glTexCoord2f(128.0, 128.0);   glVertex3f(100, -0.01, -100);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}


void tableLeg()
{	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, black);
	glNormal3f(0.0, 1.0, 0.0);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glPushMatrix(); //Draw Shadow Object
		glMultMatrixf(shadowMat);
	/* Object Transformations */
		glScalef(0.375,.4,0.375);
        glTranslatef(0, 0.5, 0);
		glColor4f(0.2, 0.2, 0.2, 0.5);
		glutSolidCube(1);
	glPopMatrix();
	glDisable(GL_BLEND);
	
	glEnable(GL_LIGHTING);
    glColor3f(0.984, 0.784, 0.557);
    glPushMatrix();
		glScalef(0.375,.4,0.375);
        glTranslatef(0, 0.5, 0);
        glutSolidCube(1);
    glPopMatrix();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
}

void tableTop()
{
	glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    
	glPushMatrix(); //Draw Shadow Object
		glMultMatrixf(shadowMat);
	/* Object Transformations */
	    glTranslatef(0, 0.4, 0);
	    glScalef(3,1,3);
        glScalef(1, 0.02, 1);
		glColor4f(0.2, 0.2, 0.2, 0.5);
		glutSolidCube(1);
	glPopMatrix();
	
	glEnable(GL_COLOR_MATERIAL);
	
	glDisable(GL_BLEND);
	
    glPushMatrix();
        glTranslatef(0, 0.4, 0);
        glScalef(3,0.02,3);
        glColor3f(0.984, 0.784, 0.557);
        glutSolidCube(1);
    glPopMatrix();
    
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, txId[8]);  //replace with a texture
    glNormal3f(0, 1, 0);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1);    glVertex3f(-1.5, 0.415, -1.5);
        glTexCoord2f(0.0, 0.0);     glVertex3f(-1.5, 0.415, 1.5);
        glTexCoord2f(1, 0.0);    glVertex3f(1.5, 0.415, 1.5);
        glTexCoord2f(1, 1);   glVertex3f(1.5, 0.415, -1.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
}

void table()
{
    tableTop();
	float legDist = 1.3;
    glPushMatrix();
        glTranslatef(legDist, 0, legDist);
        tableLeg();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-legDist, 0, -legDist);
        tableLeg();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-legDist, 0, legDist);
        tableLeg();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(legDist, 0, -legDist);
        tableLeg();
    glPopMatrix();
}

//--------------------------------------------------------------------------------
void tableRow()
{
    glPushMatrix();
        glTranslatef(-7, 0, 0);
        table();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 0, 0);
        table();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(7, 0, 0);
        table();
    glPopMatrix();
}



void musuemBuilding()
{
	muesuemFloor();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glPushMatrix(); //Draw Shadow Object
		glMultMatrixf(shadowMat);
	/* Object Transformations */
		glColor4f(0.2, 0.2, 0.2, 0.3);
		walls();
	glPopMatrix();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1, 1, 0, 1.0);  //The floor is gray in colour
	
	walls();
	
	glDisable(GL_TEXTURE_2D);
}

void armyDisplay()
{
	glPushMatrix();
      glTranslatef(0.75, -0.5, moving);
      glScalef(0.15, 0.15, 0.15);
      army2();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, -0.5, -moving -2.15);
        glScalef(0.15, 0.15, 0.15);
        army2();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-.75, -0.5, moving);
        glScalef(0.15, 0.15, 0.15);
        army2();
    glPopMatrix();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45., 1., 1., 100.);
		
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye_x, 1, eye_z,  look_x, 1, look_z,   0, 1, 0);
    
    lighting();
	
	glPushMatrix();
		glTranslatef(eye_x, -25.0, eye_z);
		glScalef(2.2, 2.2, 2.2);
		skybox();
	glPopMatrix();
	
    floor();
    musuemBuilding();
	glEnable(GL_LIGHTING);
	
	armyDisplay();
	
	glEnable(GL_LIGHTING);
	
    tableRow();

    glPushMatrix();
      glTranslatef(0, 0, 8);
      tableRow();
    glPopMatrix();

	
	glPushMatrix();
		glColor3f(0, 0, 0.0);
		glTranslatef(0, 0.45, 8);
		glScalef(0.01, 0.01, 0.01);
		canonAndStand();
    glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-7, 1, 0);
		glScalef(0.1, 0.1, 0.1);
		astroExhibit();
    glPopMatrix();
    
    glPushMatrix();
		glTranslatef(7, 3.25, 0);
		glScalef(0.1, 0.1, 0.1);
        rocketDisplay();
    glPopMatrix();
    
    
	glPushMatrix();
		glColor4f(1, 0.5, 0.0, 1);
		glTranslatef(-5.5, 0, 7.5);
		glScalef(0.1, 0.1, 0.1);
        fishs();
    glPopMatrix();
    
    glPushMatrix();
		glTranslatef(7, 0.4, 8);
		glScalef(0.03, 0.03, 0.03);
        ballExhibit();
    glPopMatrix();
    
    fishDisplay();
   
    glutSwapBuffers();
}

void myTimer1(int value)
{
    if (moving >= 0.08) {
        value = 0;
    } else if (moving <= -2.15) {
        value = 1;
    }
    if (value) {
        moving +=0.01;
    }
    if (!value){
        moving -=0.01;
    }

    glutPostRedisplay();
    glutTimerFunc(50, myTimer1, value);
}
//--------------------------------------------------------------------------------


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
   glutInitWindowSize (600, 600);
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("The Musuem");
   initialise();

   glutDisplayFunc(display);
   glutSpecialFunc(special);
   glutTimerFunc(50, armyTimer, 0);
   glutTimerFunc(50, myTimer1, 1);
   glutTimerFunc(50, astroTimer, 0);
   glutTimerFunc(50, flameTimer, 0);
   glutTimerFunc(50, ballTimer, 0);
   
   glutKeyboardFunc(rocketheight);
   

   glutMainLoop();
   return 0;
}
