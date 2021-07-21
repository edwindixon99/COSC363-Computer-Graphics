//  ========================================================================
//  COSC363: Edwin Muesuem Assignment
//
//  FILE NAME: armyMen.cpp
//  ========================================================================

#include <GL/glut.h>
#include "armyMen.h"
using namespace std;


int theta = 0;

//--------------------------------------------------------------------------------




void drawHumanoidModel()
{
    glColor3f(1., 0.78, 0.06);      //Head
    glPushMatrix();
      glTranslatef(0, 7.7, 0);
      glutSolidCube(1.4);
    glPopMatrix();

    glColor3f(1., 0., 0.);          //Torso
    glPushMatrix();
      glTranslatef(0, 5.5, 0);
      glScalef(3, 3, 1.4);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(0., 0., 1.);          //Right leg
    glPushMatrix();
      glTranslatef(-0.8, 4, 0);
      glRotatef(-theta, 1, 0, 0);
      glTranslatef(0.8, -4, 0);
      glTranslatef(-0.8, 2.2, 0);
      glScalef(1, 4.4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(0., 0., 1.);          //Left leg
    glPushMatrix();
      glTranslatef(0.8, 4, 0);
      glRotatef(theta, 1, 0, 0);
      glTranslatef(-0.8, -4, 0);
      glTranslatef(0.8, 2.2, 0);
      glScalef(1, 4.4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(0., 0., 1.);          //Right arm
    glPushMatrix();
      glTranslatef(-2, 6.5, 0);
      glRotatef(theta, 1, 0, 0);
      glTranslatef(2, -6.5, 0);
      glTranslatef(-2, 5, 0);
      glScalef(1, 4, 1);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(0., 0., 1.);          //Left arm
    glPushMatrix();
      glTranslatef(2, 6.5, 0);
      glRotatef(-theta, 1, 0, 0);
      glTranslatef(-2, -6.5, 0);
      glTranslatef(2, 5, 0);
      glScalef(1, 4, 1);
      glutSolidCube(1);
    glPopMatrix();
}

//--------------------------------------------------------------------------------



void army()
{
    glPushMatrix();
      glTranslatef(2, 6, 5);
      glScalef(0.15, 0.15, 0.15);
      drawHumanoidModel();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(1, 6, 5);
      glScalef(0.15, 0.15, 0.15);
      drawHumanoidModel();
    glPopMatrix();


    glPushMatrix();
      glTranslatef(0, 6, 5);
      glScalef(0.15, 0.15, 0.15);
      drawHumanoidModel();
    glPopMatrix();



    glPushMatrix();
      glTranslatef(-1, 6, 5);
      glScalef(0.15, 0.15, 0.15);
      drawHumanoidModel();
    glPopMatrix();


    glPushMatrix();
      glTranslatef(-2, 6, 5);
      glScalef(0.15, 0.15, 0.15);
      drawHumanoidModel();
    glPopMatrix();


    glPushMatrix();
      glTranslatef(2, 6, 5);
      glScalef(0.15, 0.15, 0.15);
      drawHumanoidModel();
    glPopMatrix();

}

void army2()
{
    glPushMatrix();
      glTranslatef(0, 0, 0);
      army();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0, 0, 1);
      army();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0, 0, 2);
      army();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0, 0, 3);
      army();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0, 0, 4);
      army();
    glPopMatrix();
}

void army3()
{
    glPushMatrix();
      glTranslatef(0, 0, 0);
      army();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0, 0, 1);
      army();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0, 0, 2);
      army();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0, 0, 3);
      army();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0, 0, 4);
      army();
    glPopMatrix();
}


//--------------------------------------------------------------------------------



void armyTimer(int value)
{
    if (theta >= 30) {
        value = 0;
    } else if (theta <= -30) {
        value = 1;
    }
    if (value) {
        theta+=5;
    }
    if (!value){
        theta-=5;

    }

    glutPostRedisplay();
    glutTimerFunc(50, armyTimer, value);
}

//--------------------------------------------------------------------------------

