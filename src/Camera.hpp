#include <iostream>
#include <math.h>
#include <vector>
#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

#ifndef CAMERAHEADER
#define CAMERAHEADER

class Camera
{
public:
    Point C;
    Point M;
    Vector Vup, U, V, W;
    double d;
    int vres, hres;

    Camera(Point CenterCam, Point Aim, Vector Vup, double d, int vres, int hres)
    {
        C = CenterCam;
        M = Aim;
        Vup = Vup;
        d = d;
        vres = vres;
        hres = hres;
    }
    ~Camera();
};

#endif