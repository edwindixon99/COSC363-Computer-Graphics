/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The sphere class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#include "Cylinder.h"
#include <math.h>
#include <cmath>

/**
* Sphere's intersection method.  The input is a ray.
*/
float Cylinder::intersect(glm::vec3 p0, glm::vec3 dir)
{
    float a = (pow(dir.x, 2) + pow(dir.z, 2));
    float b = 2 * (dir.x *(p0.x - center.x) + dir.z * (p0.z - center.z));
    float c = pow((p0.x - center.x), 2) + pow((p0.z-center.z), 2) - pow(radius, 2);
    float delta = pow(b, 2) - 4 * a * c;


    if(delta < 0.0) return -1.0;

    float t2 = (-b + sqrt(delta))/(2 * a);
    float t1 = (-b - sqrt(delta))/(2 * a);



    if ((p0.y + t1 * dir.y) > (center.y + height)) {
        if ((p0.y + t2 * dir.y) > (center.y + height)) {
            return -1;
        } else {
            return (center.y + height - p0.y)/ dir.y;
        }
        return -1;
    }

    return t1;

}

/**
* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the sphere.
*/
glm::vec3 Cylinder::normal(glm::vec3 p)
{
    glm::vec3 n = glm::vec3(p.x - center.x , 0, p.z - center.z) ;

    if (p.y >= center.y + height) n = glm::vec3 (0.0, 1.0, 0.0);

    n = glm::normalize(n);
    return n;
}



