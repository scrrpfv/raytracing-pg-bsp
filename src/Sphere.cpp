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

    Sphere(point center, double radius, int r, int g, int b){
        center = center;
        R = radius;
        normColor = Vector(r/255, g/255, b/255); 
    }

    Vector normalVec(point P){
        return (P-center).normalize();
    }

    /*
    center = (c0,c1,c2)
    direction = (d0,d1,d2) (vetor unitario -> norma=1)
    from = (x,y,z)
    equation: (d0^2 + d1^2 + d2^2)*t^2 + 2*(x-c0 + y-c1 + z-c2)*t + (x-c0)^2+(y-c1)^2+(z-c2)^2-R^2 = 0
    equation:  1*t^2 + 2*B*t + C = 0
    */
    double rayIntersect(Ray ray){
        double c0 = center.getX(), c1 = center.getY(), c2 = center.getZ();
        double x = ray.from.getX(), y = ray.from.getY(), z = ray.from.getZ();
        
        double b = 2*(x-c0 + y-c1 + z-c2);
        double c = pow((x-c0),2) + pow((y-c1),2) + pow((z-c2),2) + R*R;
        double delta = b*b - 4*c;
        if (delta<0) return -1;
        
        double t0 = (-b + sqrt(delta))/2;
        double t1 = (-b - sqrt(delta))/2;
        if (t0<=t1) return t0;
        return t1;
    }


};


#endif