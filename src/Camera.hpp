#include "RayTrace.hpp"
#include <fstream>

#ifndef CAMERAHEADER
#define CAMERAHEADER

class Camera
{
private:
    double pixelSide;
    Vector unitUp;
    Vector unitLeft;

public:
    Point camPosition;
    Point target;
    Vector Vup, U, V, W;

    int vres, hres;

    Camera(Point CenterCam, Point Aim, Vector Vup, int vres, int hres) : vres(vres), hres(hres), Vup(Vup)
    {
        camPosition = CenterCam;
        target = Aim;
        W = (target - camPosition).normalize();
        U = (Vup.cross(W)).normalize(); // aponta para esquerda
        V = W.cross(U);                 // aponta para cima
        pixelSide = 1.0 / hres;
        unitUp = V * pixelSide;
        unitLeft = U * pixelSide;
    }

    void render(double f, int ttl)
    {
        std::ofstream ppm;
        ppm.open("render.ppm");
        std::cout << "Rendering..." << std::endl;

        Point topleftPixel = camPosition + W * (f / 2) + (V * (vres - 1) + U * (hres - 1)) * pixelSide / 2.0;
        ppm << "P3" << std::endl;
        ppm << hres << ' ' << vres << std::endl;
        ppm << 255 << std::endl;
        int k = 0;
        for (int i = 0; i < vres; i++)
        {
            for (int j = 0; j < hres; j++)
            {
                Point pixelPosition = topleftPixel - unitUp * i - unitLeft * j;
                Vector pixelColor = rayTrace(Ray(camPosition, pixelPosition), ttl);
                ppm << pixelColor << std::endl;
            }
        }
        ppm.close();
    }
    ~Camera() {
        // std::cout << "Camera destroyed" << std::endl;
    };
};

#endif