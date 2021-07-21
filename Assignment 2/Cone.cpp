/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The sphere class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#include "Cone.h"
#include <math.h>
#include <cmath>

/**
* Sphere's intersection method.  The input is a ray.
*/
float Cone::intersect(glm::vec3 p0, glm::vec3 dir)
{
    float r = radius;
    float h = height;
    float a = pow(dir.x, 2) + pow(dir.z, 2) - pow((r/h), 2) * pow(dir.y, 2);
    float b = 2 * (dir.x *(p0.x - center.x) + dir.z * (p0.z - center.z) + pow((r/h), 2) * dir.y *(h - p0.y + center.y));
    float c = pow((p0.x - center.x), 2) + pow((p0.z-center.z), 2) - pow((r/h), 2) * pow((h - p0.y + center.y), 2);
    float delta = pow(b, 2) - 4 * a * c;

    if(delta < 0.0) return -1.0;

    float t2 = (-b + sqrt(delta))/(2 * a);
    float t1 = (-b - sqrt(delta))/(2 * a);

    if ((p0.y + t1 * dir.y) > (center.y + height)) {
        return -1;
    }
    if ((p0.y + t1 * dir.y) < (center.y)) {
        return -1;
    }

    if(fabs(t1) < 0.001 )
    {
        if (t2 > 0) return t2;
        else t1 = -1.0;
    }
    if(fabs(t2) < 0.001 ) t2 = -1.0;

    return (t1 < t2)? t1: t2;

}

/**
* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the sphere.
*/
glm::vec3 Cone::normal(glm::vec3 p)
{
    float theta = atan(radius/height);
    float alpha = atan(((p.x - center.x)/(p.z - center.z)));
    glm::vec3 n = glm::vec3(sin(alpha)*cos(theta), sin(theta), cos(alpha)*cos(theta));
    return n;
}



