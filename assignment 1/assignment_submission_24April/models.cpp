
#include <GL/glut.h>
#include "models.h"

using namespace std;

float thetam = 0;
float color = 0;
float height = 0;
float drop = 90;
int value1 = 1;
float velocity = 1.1;


//	PLANETS
//--------------------------------------------------------------------------------
void moon()
{
	glPushMatrix();
		glColor3f(0.7, 0.7, 0.7);
		glRotatef(thetam*0.2, 0, 1, 0);
		glTranslatef(0,0,1);
        glutSolidSphere(0.125, 36, 18);
    glPopMatrix();
}

void planet(int moony)
{
    glutSolidSphere(0.5, 36, 18);
    if (moony == 1) {
		moon();
	}
}

void jupiter()
{
	GLUquadric *q;
	q = gluNewQuadric();
	//gluDisk(q, 10, 100, 10, 10);
	
	
	glPushMatrix();
		glColor4f(1, 0.5, 0., 1);
		glRotatef(90, 0, 1, 0);
		glRotatef(100, 1, 0, 0);
		gluDisk(q, 3.2, 5, 40, 10);
		//glutSolidSphere(2, 36, 18);
    glPopMatrix();
    
    gluQuadricDrawStyle(q, GLU_FILL);
	glPushMatrix();
		glColor4f(1, 0.2, 0, 1);
		glScalef(3, 3, 3);
		planet(1);
	glPopMatrix();
}

void planets()
{
	//merc    
    glPushMatrix();
		glColor3f(1, 0.5, 0.2);
		glRotatef(thetam*1.8, 0, 1, 0);
		glTranslatef(0,0,6);
        planet(0);
    glPopMatrix();
    
    glPushMatrix();
		glColor3f(0, 0.5, 1);
		glRotatef(thetam*1.3, 0, 1, 0);
		glTranslatef(0,0,-8);
        planet(0);
    glPopMatrix();
	
	glPushMatrix();
		glColor3f(0, 0, 1);
		glRotatef(thetam, 0, 1, 0);
		glTranslatef(0,0,-10);
        planet(1);
    glPopMatrix();
    
    glPushMatrix();
		glColor3f(1, 0, 0);
		glRotatef(thetam*0.7, 0, 1, 0);
		glTranslatef(0,0,12);
        planet(1);
    glPopMatrix();
    
    
    glPushMatrix();
		glColor3f(0, 0, 1);
		glRotatef(thetam*0.4, 0, 1, 0);
		glTranslatef(0,0,20);
        jupiter();
    glPopMatrix();
    
	
}

void sun()
{
	glPushMatrix();
		glColor3f(1, 1, 0);
        glutSolidSphere(5, 36, 18);
    glPopMatrix();
}

void astroExhibit()
{	
	glPushMatrix();
		planets();
	glPopMatrix();
		
	sun();
	
}

void astroTimer(int value)
{       
    thetam+=2;

    glutPostRedisplay();
    glutTimerFunc(50, astroTimer, value);
}

//--------------------------------------------------------------------------------


void flame()
{
	glPushMatrix();
		glColor3f(1, 0.5+color, 0);
		glRotatef(180, 0, 1, 0);
        glutSolidCone(1, 2.5, 10, 10);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(1, 1-2*color, 0);
		glTranslatef(1,0,0);
		glRotatef(180, 0, 1, 0);
        glutSolidCone(1, 2.5, 10, 10);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(1, 1-2*color, 0);
		glTranslatef(-1,0,0);
		glRotatef(180, 0, 1, 0);
        glutSolidCone(1, 2.5, 10, 10);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(1, 0+color, 0);
		glTranslatef(0,-1,0);
		glRotatef(180, 0, 1, 0);
        glutSolidCone(1, 2.5, 10, 10);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(1, 0+color, 0);
		glTranslatef(0,1,0);
		glRotatef(180, 0, 1, 0);
        glutSolidCone(1, 2.5, 10, 10);
	glPopMatrix();
}

void flames()
{
	glDisable(GL_LIGHTING);
	
    glPushMatrix();
		glTranslatef(0,0,-1);
        flame();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(1,0,0);
        flame();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-1,0,0);
        flame();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0,-1,0);
        flame();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0,1,0);
        flame();
	glPopMatrix();
	
	glEnable(GL_LIGHTING);
}

void rocket()
{
    glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
        glutSolidCone(2, 5, 10, 10);
    glPopMatrix();
    
    GLUquadric *q;
	q = gluNewQuadric();
	
	glPushMatrix();
		glColor3f(0.9, 0.9, 0.9);
		glTranslatef(0,0,-20);
        gluCylinder(q, 2, 2, 20, 10, 3);
    glPopMatrix();
    
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glTranslatef(0,0,-22);
        gluCylinder(q, 4, 2, 4, 16, 10);
    glPopMatrix();

    glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glTranslatef(0,0,-22);
        gluDisk(q, 0, 4, 10, 4);
    glPopMatrix();
    
    if (height > 0) {
		glPushMatrix();
			glTranslatef(0,0,-21.5);
			flames();
		glPopMatrix();
	}
    
	gluQuadricDrawStyle(q, GLU_FILL);
    
}

void flameTimer(int value)
{       
    if (color >= 0.5) {
        value = 0;
    } else if (color <= 0) {
        value = 1;
    }
    if (value) {
        color+=0.05;
    }
    if (!value){
        color-=0.05;

    }
	
    glutPostRedisplay();
    glutTimerFunc(50, flameTimer, value);
}

void rocketheight(unsigned char key, int x, int y)
{
    if(key == 'w') height += 0.5;  //Change direction
    else if(key == 's' && height > 0) height -= 0.5;
    
    
    glutPostRedisplay();
}

void rocketDisplay()
{
	glEnable(GL_BLEND);
	glPushMatrix();
		glTranslatef(0,height,0);
		glRotatef(90, 0, 1, 0);
		glRotatef(270, 1, 0, 0);
        rocket();
    glPopMatrix();
    
    glPushMatrix();
		glColor4f(1, 0.8, 0.8, 0.5);
		glTranslatef(0,-25,0);
		glScalef(1,0.9,1);
        glutSolidCube(7);
    glPopMatrix();
	glDisable(GL_BLEND);
}

void fishDisplay()
{   
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	
	glColor4f(0, 0, 1, 0.5);
	glBegin(GL_QUADS);
	
	
    glVertex3f(-8.5, 0.4, 9.5);
    glVertex3f(-5.5, 0.4, 9.5);
    glVertex3f(-5.5, 1.7, 9.5);
    glVertex3f(-8.5, 1.7, 9.5);
    
    glVertex3f(-8.5, 0.4, 9.5);
    glVertex3f(-8.5, 0.4, 6.5);
    glVertex3f(-8.5, 1.7, 6.5);
    glVertex3f(-8.5, 1.7, 9.5);
	
	glVertex3f(-8.5, 0.4, 6.5);
    glVertex3f(-5.5, 0.4, 6.5);
    glVertex3f(-5.5, 1.7, 6.5);
    glVertex3f(-8.5, 1.7, 6.5);
    
    glVertex3f(-5.5, 0.4, 9.5);
    glVertex3f(-5.5, 0.4, 6.5);
    glVertex3f(-5.5, 1.7, 6.5);
    glVertex3f(-5.5, 1.7, 9.5);
    
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);


}

void fish()
{
	glDisable(GL_LIGHTING);
    
    GLUquadric *q;
	q = gluNewQuadric();
	
	glPushMatrix();
		glTranslatef(0,0,0);
        gluCylinder(q, 2, 4, 6, 10, 3);
    glPopMatrix();
    
	glPushMatrix();
		glTranslatef(0,0,-4);
        gluCylinder(q, 4, 2, 4, 16, 10);
    glPopMatrix();
	
	
	glPushMatrix();
		glTranslatef(0,0,6);
		glRotatef(180, 0, 0, 1);
        gluCylinder(q, 4, 2, 4, 16, 10);
    glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0,-4);
        gluDisk(q, 0, 4, 10, 4);
    glPopMatrix();
    
    glPushMatrix();
		glTranslatef(0,0,10);
        gluDisk(q, 0, 2, 10, 4);
    glPopMatrix();
    
	gluQuadricDrawStyle(q, GLU_FILL);
	glEnable(GL_LIGHTING);
    
}


void fishs()
{
    glPushMatrix();
        glTranslatef(-26,42,0);
        glScalef(0.4, 1, 1);
        glTranslatef(20,-30,0);
        fish();
    glPopMatrix();
    
    glPushMatrix();
        //glNormal3f(1, 1, 0);
        glTranslatef(-20,42,0);
        glScalef(0.4, 1, 1);
        glTranslatef(20,-30,0);
        fish();
    glPopMatrix();
    
    glPushMatrix();
        //glNormal3f(1, 0.5, 0);
        glTranslatef(-14,42,0);
        glScalef(0.4, 1, 1);
        glTranslatef(20,-30,0);
        fish();
    glPopMatrix();
}


void ball()
{
	glColor4f(0, 0, 0, 1);
	glPushMatrix();
		glTranslatef(-6.5,drop,0);
        glutSolidSphere(4, 36, 18);
    glPopMatrix();
    
}

void lift()
{
	glColor3f(0.5, 0.5, 0.1);
	glPushMatrix();
		glTranslatef(6, 45, 0);
		glScalef(1, 22, 1);
        glutSolidCube(4);
    glPopMatrix();
    
    if (drop <= 6) {
		value1 = 1;
	} else if (drop >= 90) {
		value1 = 0;
	}
	if (value1) {
    glPushMatrix();
		glTranslatef(-4, drop-2.5, 0);
		glScalef(7, 0.5, 7);
        glutSolidCube(3);
    glPopMatrix();
	}
    
}

void ballTimer(int value)
{
    if (drop >= 90) {
        value = 0;
        velocity = 0;
    } else if (drop <= 6) {
        value = 1;
    }
    if (value) {
        drop+=2;
        velocity = 0;
    }
    if (!value){
		velocity += 1; 
        drop-=velocity;

    }

    glutPostRedisplay();
    glutTimerFunc(50, ballTimer, value);
}



void ballExhibit()
{
    glPushMatrix();
        glTranslatef(0,2,0);
        //glRotatef(30,0,0,1);
        ball();
    glPopMatrix();
    
	lift();
}

