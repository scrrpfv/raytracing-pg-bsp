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
    direction = <d0,d1,d2> (vetor unitario -> norma=1)
    from = (x,y,z)
    diffVec = from - center = <x-c0, y-c1, z-c2> = <u0, u1, u2>
    equation: (d0^2 + d1^2 + d2^2)*t^2 + 2*(x-c0 + y-c1 + z-c2)*t + (x-c0)^2+(y-c1)^2+(z-c2)^2-R^2 = 0
    equation:  1*t^2 + 2*(u0+u1+u2)*t + norm(diffVec)^2-R^2 = 0
    */
    double rayIntersect(Ray ray){
        Vector diffVec = ray.from - center;

        double b = 2*(diffVec.getX() + diffVec.getY() + diffVec.getZ());
        double c = pow(diffVec.norm(), 2) - R*R;
        double delta = b*b - 4*c;

        if (delta<0) return -1;
        
        double t0 = (-b + sqrt(delta))/2;
        double t1 = (-b - sqrt(delta))/2;

        if (t0<=t1) return t0;
        return t1;
    }


};


#endif