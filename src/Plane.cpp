#include <iostream>
#include <math.h>
#include "Point.cpp"
#include "Vector.cpp"
#include "Ray.cpp"


#ifndef PLANEHEADER
#define PLANEHEADER

class Plane
{
public:
    Vector normalVec;
    point P0;
    Vector normColor;

    Plane(Vector normal, point planePoint, int r, int g, int b){
        normalVec = normal.normalize();
        P0 = planePoint;
        normColor = Vector(r/255, g/255, b/255); 
    }

    /*
    plane: (I-P0)*normalVec = 0
    ray: I = from + t*direction
    equation:   t*(dot(ray.direction, normalVec)) + (ray.from - P0)*normalVec = 0
                t = ((P0-from).dotProduct(normalVec))/direction.dotProduct(normalVec)
    */
    double rayIntersect(Ray ray){
        Vector direction = ray.direction;
        point from = ray.from;

        double t = ((P0-from).dotProduct(normalVec))/direction.dotProduct(normalVec);

        return t;
    }
};

#endif
