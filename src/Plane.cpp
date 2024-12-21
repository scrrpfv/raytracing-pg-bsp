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

    Plane(Vector normal, point planePoint, int rgb[3]){
        normalVec = normal.normalize();
        P0 = planePoint;
        normColor = Vector(rgb[0], rgb[1], rgb[2]); 
    }
    
    Vector getNormal(){
        return normalVec;
    }
    
    /*
    Recebe e modifica t caso haja interseção com o raio
    retorna true se houve intersecao e se t>0
    */
    double rayIntersect(Ray ray){
        double aux = ray.direction.dotProduct(normalVec);
        if (abs(aux) == 0) return -1;

        double t = ((P0-ray.from).dotProduct(normalVec))/aux;
        if (t>0) return t;
        return -1;
    }
};

#endif
