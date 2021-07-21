//  ========================================================================
//  COSC363: Edwin Muesuem Assignment
//
//  FILE NAME: Cannon.cpp
//  ========================================================================

#include <iostream>
#include <GL/glut.h>
#include <fstream>
#include <climits>
#include "cannon.h"

using namespace std;

float *x, *y, *z;       //vertex coordinate arrays
int *t1, *t2, *t3;      //triangles
int nvrt, ntri;         //total number of vertices and triangles

//--------------------------------------------------------------------------------
void loadMeshFile(const char* fname)
{
    ifstream fp_in;
    int num, ne;

    fp_in.open(fname, ios::in);
    if(!fp_in.is_open())
    {
        cout << "Error opening mesh file" << endl;
        exit(1);
    }

    fp_in.ignore(INT_MAX, '\n');                //ignore first line
    fp_in >> nvrt >> ntri >> ne;                // read number of vertices, polygons, edges

    x = new float[nvrt];                        //create arrays
    y = new float[nvrt];
    z = new float[nvrt];

    t1 = new int[ntri];
    t2 = new int[ntri];
    t3 = new int[ntri];

    for(int i=0; i < nvrt; i++)                         //read vertex list
        fp_in >> x[i] >> y[i] >> z[i];

    for(int i=0; i < ntri; i++)                         //read polygon list
    {
        fp_in >> num >> t1[i] >> t2[i] >> t3[i];
        if(num != 3)
        {
            cout << "ERROR: Polygon with index " << i  << " is not a triangle." << endl;  //not a triangle!!
            exit(1);
        }
    }

    fp_in.close();
    cout << " File successfully read." << endl;
}


void normal(int indx)
{
    float x1 = x[t1[indx]], x2 = x[t2[indx]], x3 = x[t3[indx]];
    float y1 = y[t1[indx]], y2 = y[t2[indx]], y3 = y[t3[indx]];
    float z1 = z[t1[indx]], z2 = z[t2[indx]], z3 = z[t3[indx]];
    float nx, ny, nz;
    nx = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
    ny = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
    nz = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}



//--------------------------------------------------------------------------------

void drawCannon()
{
    glColor3f(0.4, 0.5, 0.4);

    //Construct the object model here using triangles read from OFF file
    glBegin(GL_TRIANGLES);
        for(int tindx = 0; tindx < ntri; tindx++)
        {
           normal(tindx);
           glVertex3d(x[t1[tindx]], y[t1[tindx]], z[t1[tindx]]);
           glVertex3d(x[t2[tindx]], y[t2[tindx]], z[t2[tindx]]);
           glVertex3d(x[t3[tindx]], y[t3[tindx]], z[t3[tindx]]);
        }
    glEnd();
}

void canonAndStand()
{
	//~ glEnable(GL_LIGHTING);
	glPushMatrix();
		glColor3f(0.4, 0.5, 0.4);
        glTranslatef(-20,30,0);
        glRotatef(30,0,0,1);
        glTranslatef(20,-30,0);
        drawCannon();
    glPopMatrix();


        //--start here

    glPushMatrix();
        glTranslatef(-10,5,17);
        glScalef(80,10,6);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-10,5,-17);
        glScalef(80,10,6);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-20,25,17);
        glScalef(40,30,6);
        glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(-20,25,-17);
        glScalef(40,30,6);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(38.88,64,0);
        glutSolidSphere(5, 36, 18);
    glPopMatrix();
	 
	 //~ glDisable(GL_LIGHTING);
}

