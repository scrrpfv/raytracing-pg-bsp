#include <iostream>
#include <math.h>
#include "Point.cpp"
#include "Vector.cpp"
#include "Ray.cpp"

#ifndef SPHEREHEADER
#define SPHEREHEADER

class Sphere
{
public:
    point center;
    double R;
    Vector normColor;

    Sphere(point center, double radius, Vector rgb){
        center = center;
        R = radius;
        normColor = rgb; 
    }

    Vector getNormal(point P){
        return (P-center).normalize();
    }

    double rayIntersect(Ray ray){
        Vector diffVec = center - ray.from;

        double B = -2*diffVec.dotProduct(ray.direction);
        double C = diffVec.dotProduct(diffVec) - R*R;
        double delta = B*B - 4*C;

        if (delta<0) return -1;
        
        double t0 = (B + sqrt(delta))/2;
        double t1 = (B - sqrt(delta))/2;
    
        if (t0<0){
            if (t1<0) return -1;
            return t1;
        } 
        return t0;
    }

};


#endif