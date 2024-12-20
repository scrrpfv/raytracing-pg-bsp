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
    point planeP;
    Vector normColor;

    Plane(Vector normal, point Point, int r, int g, int b){
        normalVec = normal.normalize();
        planeP = Point;
        normColor = Vector(r/255, g/255, b/255); 
    }

    double rayIntersect(Ray ray){
        Vector direction = ray.direction;
        point from = ray.from;

        double parameterT = ((planeP-from).dotProduct(normalVec))/direction.dotProduct(normalVec);

        return parameterT;
    }
};

#endif
