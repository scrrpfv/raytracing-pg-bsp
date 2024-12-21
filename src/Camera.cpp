#include <iostream>
#include <math.h>
#include <vector>
#include "Point.cpp"
#include "Vector.cpp"
#include "Ray.cpp"
#include "Sphere.cpp"
#include "Plane.cpp"

#ifndef CAMERAHEADER
#define CAMERAHEADER

class Camera
{
public:
    point C;
    point M;
    Vector Vup, U, V, W;
    double d; 
    int vres, hres;

    Camera(point CenterCam, point Aim, Vector Vup, double d, int vres, int hres)
    {
        C = CenterCam;
        M = M;
        Vup = Vup;
        d = d;
        vres = vres;
        hres = hres;
    }
    ~Camera();
};



#endif