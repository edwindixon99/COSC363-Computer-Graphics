/*==================================================================================
* COSC 363  Computer Graphics (2020)
* Department of Computer Science and Software Engineering, University of Canterbury.
*
* A basic ray tracer
* See Lab07.pdf, Lab08.pdf for details.
*===================================================================================
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "SceneObject.h"
#include "Ray.h"
#include <GL/freeglut.h>
#include "Plane.h"
#include "TextureBMP.h"

using namespace std;

const float WIDTH = 20.0;
const float HEIGHT = 20.0;
const float EDIST = 40.0;
const int NUMDIV = 1000;
const int MAX_STEPS = 5;
const float XMIN = -WIDTH * 0.5;
const float XMAX =  WIDTH * 0.5;
const float YMIN = -HEIGHT * 0.5;
const float YMAX =  HEIGHT * 0.5;
TextureBMP texture;
TextureBMP earth;

vector<SceneObject*> sceneObjects;



//---The most important function in a ray tracer! ----------------------------------
//   Computes the colour value obtained by tracing a ray and finding its
//     closest point of intersection with objects in the scene.
//----------------------------------------------------------------------------------
glm::vec3 trace(Ray ray, int step)
{
    glm::vec3 backgroundCol(0);                     //Background colour = (0,0,0)
    glm::vec3 lightPos(10, 40, -3);                 //Light's position
    glm::vec3 color(0);
    SceneObject* obj;
    SceneObject* otherobj;

    ray.closestPt(sceneObjects);                    //Compare the ray with all objects in the scene
    if(ray.index == -1) return backgroundCol;       //no intersection
    obj = sceneObjects[ray.index];                  //object on which the closest point of intersection is found

    if (ray.index == 0)
    {
     //Stripe pattern
     int stripeWidth = 5;
     int stripeHeight = 5;
     int iz = (ray.hit.z) / stripeWidth;
     int ix = (ray.hit.x) / stripeHeight;


    if (ray.hit.x < 0){
        iz ++;
    }
     int k = abs(iz % 2); //2 colors
     int j = abs(ix % 2); //2 colors




     if (j == k) {
         color = glm::vec3(1, 1, 0);
     }else {
         color = glm::vec3(0.59, 0.2, 1);
     }
     obj->setColor(color);

    //Add code for texture mapping here
    }

    if (ray.index == 1)
    {
        float texcoords = (ray.hit.x + 80)/(80+80);
        float texcoordt = (ray.hit.y + 15)/(80+15);
        if(texcoords > 0 && texcoords < 1 &&
        texcoordt > 0 && texcoordt < 1)
        {
        color=texture.getColorAt(texcoords, texcoordt);
        obj->setColor(color);
        }
    }

    if (ray.index == 2)
    {
        //~ float alpha = obj->normal(ray.hit).x, obj->normal(ray.hit).z;
        float delta = obj->normal(ray.hit).y;
        float texcoords = 0.5 + atan2(-obj->normal(ray.hit).x, -obj->normal(ray.hit).z) / (2 * 3.141592654);
        float texcoordt = 0.5 - asin(-delta) / 3.141592654;
        color=earth.getColorAt(texcoords, texcoordt);
        obj->setColor(color);
    }

    color = obj->lighting(lightPos, -ray.dir, ray.hit);                     //Object's colour

    glm::vec3 lightVec = lightPos - ray.hit;
    Ray shadowRay(ray.hit, lightVec);

    shadowRay.closestPt(sceneObjects);

    if ((shadowRay.index > -1) && (shadowRay.dist < glm::length(lightVec))) {
        otherobj = sceneObjects[shadowRay.index];
        if (otherobj->isTransparent() || otherobj->isRefractive()) {
            color = 0.4f*(0.5f*otherobj->getColor()) + 0.5f*(obj->getColor()); //0.4 = ambient scale factor
        } else {
            color = 0.2f*(obj->getColor()); //0.2 = ambient scale factor
        }


    }

    if (obj->isTransparent() && step< MAX_STEPS)
    {
        float transco = obj->getTransparencyCoeff();
        Ray refractedInRay(ray.hit, ray.dir);
        refractedInRay.closestPt(sceneObjects);

        Ray refractedOutRay(refractedInRay.hit, ray.dir);
        refractedOutRay.closestPt(sceneObjects);

        glm::vec3 refractedColor = trace(refractedOutRay, step + 1);
        color = color + (transco * refractedColor);
    }

    if (obj->isRefractive() && step< MAX_STEPS)
    {
        float refrac = obj->getRefractionCoeff();
        glm::vec3 normalVec = obj->normal(ray.hit);
        glm::vec3 refractedDir = glm::refract(ray.dir, normalVec, obj->getRefractiveIndex());
        Ray refractedInRay(ray.hit, refractedDir);
        refractedInRay.closestPt(sceneObjects);

        glm::vec3 m = obj->normal(refractedInRay.hit);
        glm::vec3 h = glm::refract(refractedDir, -m, 1.0f/obj->getRefractiveIndex());
        Ray refractedOutRay(refractedInRay.hit, h);
        refractedOutRay.closestPt(sceneObjects);

        glm::vec3 refractedColor = trace(refractedOutRay, step + 1);
        color = color + (refrac * refractedColor);
    }

    if (obj->isReflective() && step < MAX_STEPS)
    {
    float rho = obj->getReflectionCoeff();
    glm::vec3 normalVec = obj->normal(ray.hit);
    glm::vec3 reflectedDir = glm::reflect(ray.dir, normalVec);
    Ray reflectedRay(ray.hit, reflectedDir);
    glm::vec3 reflectedColor = trace(reflectedRay, step + 1);
    color = color + (rho * reflectedColor);
    }
    float z1 = -50;
    float z2 = -380;
    float t = (ray.hit.z - z1) / (z2 - z1);
    color = (1-t) * color + t * glm::vec3(0.8, 0.8, 0.8);
    return color;
}

//---The main display module -----------------------------------------------------------
// In a ray tracing application, it just displays the ray traced image by drawing
// each cell as a quad.
//---------------------------------------------------------------------------------------
void display()
{
    float xp, yp;  //grid point
    float cellX = (XMAX-XMIN)/NUMDIV;  //cell width
    float cellY = (YMAX-YMIN)/NUMDIV;  //cell height
    glm::vec3 eye(0., 0., 0.);
    float red = 0;
    float green = 0;
    float blue = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_QUADS);  //Each cell is a tiny quad.

    for(int i = 0; i < NUMDIV; i++) //Scan every cell of the image plane
    {
        xp = XMIN + i*cellX;
        for(int j = 0; j < NUMDIV; j++)
        {
            yp = YMIN + j*cellY;

            red=0;
            green = 0;
            blue =0;
            for (int k=0; k<2; k++) {
                for (int l=0;l<2;l++) {
                    glm::vec3 dir(xp+(k * 0.5 + 0.25)*cellX, yp+(l * 0.5 + 0.25)*cellY, -EDIST);  //direction of the primary ray

                    Ray ray = Ray(eye, dir);

                    glm::vec3 col = trace (ray, 1); //Trace the primary ray and get the colour value
                    red += col.r;
                    green += col.g;
                    blue += col.b;
                }
            }
            red = red /4;   green = green /4;   blue = blue/4;
            glColor3f(red, green, blue);
            glVertex2f(xp, yp);             //Draw each cell with its color value
            glVertex2f(xp+cellX, yp);
            glVertex2f(xp+cellX, yp+cellY);
            glVertex2f(xp, yp+cellY);
        }
    }



    glEnd();
    glFlush();
}


//---This function initializes the scene -------------------------------------------
//   Specifically, it creates scene objects (spheres, planes, cones, cylinders etc)
//     and add them to the list of scene objects.
//   It also initializes the OpenGL orthographc projection matrix for drawing the
//     the ray traced image.
//----------------------------------------------------------------------------------
void initialize()
{
    texture = TextureBMP("Optical.bmp");
    earth = TextureBMP("earth.bmp");
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(XMIN, XMAX, YMIN, YMAX);

    glClearColor(0, 0, 0, 1);


    Plane *plane = new Plane (glm::vec3(-80., -15, -40), //Point A
     glm::vec3(80., -15, -40), //Point B
     glm::vec3(80., -15, -300), //Point C
     glm::vec3(-80., -15, -300)); //Point D
    plane->setSpecularity(false);
    sceneObjects.push_back(plane);

    Plane *backplane = new Plane (glm::vec3(-80., -15, -300), //Point A
     glm::vec3(80., -15, -300), //Point B
     glm::vec3(80., 80, -370), //Point C
     glm::vec3(-80., 80, -370)); //Point D
    backplane->setSpecularity(false);
    sceneObjects.push_back(backplane);



    Sphere *texSphere = new Sphere(glm::vec3(-13.0, 9.0, -80.0), 4.5);
    texSphere->setColor(glm::vec3(0, 0, 1));   //Set colour to blue
    sceneObjects.push_back(texSphere);         //Add sphere to scene objects


    Plane *backplane2 = new Plane (glm::vec3(-130., -15, -370), //Point A
     glm::vec3(130., -15, -370), //Point B
     glm::vec3(130., 130, -370), //Point C
     glm::vec3(-130., 130, -370)); //Point D
     backplane2->setColor(glm::vec3(0.8, 0.8, 0.8));
    sceneObjects.push_back(backplane2);

    Sphere *sphere1 = new Sphere(glm::vec3(-5.0, 15.0, -105.0), 16.0);
    sphere1->setColor(glm::vec3(0, 0, 1));   //Set colour to blue
    sceneObjects.push_back(sphere1);         //Add sphere to scene objects
    sphere1->setSpecularity(true);

    sphere1->setShininess(5);
    sphere1->setReflectivity(true, 0.8);

    Sphere *sphere2 = new Sphere(glm::vec3(-5.0, -10.0, -70.0), 4.0);
    sphere2->setColor(glm::vec3(1.0, 0, 0.8));   //Set colour to blue
    sceneObjects.push_back(sphere2);         //Add sphere to scene objects
    sphere2->setTransparency(true);
    sphere2->setReflectivity(true, 0.2);

    Sphere *sphere3 = new Sphere(glm::vec3(13.0, 5.0, -90.0), 8.0);
    sphere3->setColor(glm::vec3(0, 0, 0));   //Set colour to blue
    sceneObjects.push_back(sphere3);         //Add sphere to scene objects
    sphere3->setRefractivity(true, 0.7,0.5);
    sphere3->setReflectivity(true, 0.3);

    Cylinder *cylinder1 = new Cylinder(glm::vec3(-9.0, -10.0, -100.0), 9.0, 3);
    cylinder1->setColor(glm::vec3(1.0, 0.0, 0.0));
    sceneObjects.push_back(cylinder1);
    cylinder1->setReflectivity(true, 0.8);

    Cone *cone1 = new Cone(glm::vec3(10.0, -6.0, -70.0), 2.0, 7);
    cone1->setColor(glm::vec3(1, 0, 0.6));
    sceneObjects.push_back(cone1);




    //~ // Pyramid
    float x1 = 0;   float x2 = 4;
    float y1 = -12; float y2 = -9;
    float z1 = -74; float z2 = -66;
    float ptopx =  (x2-x1)/2;   float ptopz =  (z2-z1)/2;
    glm::vec3 pyramidColor(0, 1, 0);

    Plane *plane1 = new Plane (glm::vec3(x1, y1, z1), glm::vec3(x1, y1, z2), glm::vec3(x2, y1, z2), glm::vec3(x2, y1, z1)); plane1->setSpecularity(false);plane1->setColor(pyramidColor);sceneObjects.push_back(plane1);
    Plane *plane2 = new Plane (glm::vec3(x1, y1, z1),glm::vec3(x2, y1, z1), glm::vec3(x1+ptopx, y2, z1+ptopz));plane2->setSpecularity(false);plane2->setColor(pyramidColor);sceneObjects.push_back(plane2);
    Plane *plane3 = new Plane (glm::vec3(x1+ptopx, y2, z1+ptopz),glm::vec3(x2, y1, z1), glm::vec3(x2, y1, z2));plane3->setSpecularity(false);plane3->setColor(pyramidColor);sceneObjects.push_back(plane3);
    Plane *plane4 = new Plane (glm::vec3(x2, y1, z2), glm::vec3(x1+ptopx, y2, z1+ptopz),glm::vec3(x1, y1, z2)); plane4->setSpecularity(false); plane4->setColor(pyramidColor); sceneObjects.push_back(plane4);
    Plane *plane5 = new Plane (glm::vec3(x1, y1, z2), glm::vec3(x1+ptopx, y2, z1+ptopz), glm::vec3(x1, y1, z1)); plane5->setSpecularity(false);plane5->setColor(pyramidColor);sceneObjects.push_back(plane5);
    //

}


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(4500, 20);
    glutCreateWindow("Raytracing");

    glutDisplayFunc(display);
    initialize();

    glutMainLoop();
    return 0;
}
