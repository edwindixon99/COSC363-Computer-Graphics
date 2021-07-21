/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The sphere class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#include "Pyramid.h"
#include "Plane.h"
#include "SceneObject.h"
#include <math.h>


vector<SceneObject*> sceneObjects;
/**
* Sphere's intersection method.  The input is a ray. 
*/
void Pyramid(float scale, float x, float y, float z)
{
	float x1 = (x-2) * scale;
	float x2 = (x+2) * scale;
	float y1 = (y-2) * scale;
	float y2 = (y+2) * scale;
	float z1 = (z-2) * scale;
	float z2 = (z+2) * scale;
	Plane *plane1 = new Plane (glm::vec3(x1, y1, z2), //Point A
	 glm::vec3(x2, y1, z2), //Point B
	 glm::vec3(x2, y1, z1), //Point C
	 glm::vec3(x1, y1, z1)); //Point D
	plane1->setSpecularity(false);
	sceneObjects.push_back(plane1);
	 
	Plane *plane2 = new Plane (glm::vec3(x1, y1, z1), //Point A
	 glm::vec3(x2, y1, z1), //Point B
	 glm::vec3(x2/2, y2, z1), //Point C
	plane2->setSpecularity(false);
	sceneObjects.push_back(plane2);
	
	Plane *plane3 = new Plane (glm::vec3(x2, y1, x1), //Point A
	 glm::vec3(x2, y1, z2), //Point B
	 glm::vec3(x2/2, y2, z1), //Point C
	plane3->setSpecularity(false);
	sceneObjects.push_back(plane3);
	
	Plane *plane4 = new Plane (glm::vec3(x2, y1, x2), //Point A
	 glm::vec3(x1, y1, z2), //Point B
	 glm::vec3(x2/2, y2, z1), //Point C
	plane4->setSpecularity(false);
	sceneObjects.push_back(plane4);
	
	Plane *plane5 = new Plane (glm::vec3(x1, y1, x2), //Point A
	 glm::vec3(x1, y1, z1), //Point B
	 glm::vec3(x2/2, y2, z1), //Point C
	plane5->setSpecularity(false);
	sceneObjects.push_back(plane5);
}

