#include "RayTrace.hpp"
#include <fstream>

#ifndef CAMERAHEADER
#define CAMERAHEADER

const double squareSide = 0.1;

class Camera
{
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
        V = W.cross(U);
    }

    void render(double f, int ttl)
    {
        std::ofstream ppm;
        ppm.open("render.txt");
        std::cout << "Rendering at cam " << camPosition << " and AIM " << target << std::endl;
        std::cout << "Rendering..." << std::endl;

        Point topleftPixel = camPosition + W * f + (V * (vres - 1) - (U * (hres - 1))) * squareSide / 2.0;

        std::cout << "Top left pixel: " << topleftPixel << std::endl;
        ppm << "P3" << std::endl;
        ppm << hres << ' ' << vres << std::endl;
        ppm << 255 << std::endl;
        int k = 0;
        for (int i = 0; i < vres; i++)
        {
            for (int j = 0; j < hres; j++)
            {
                Point pixelPosition = topleftPixel - ((U * j - V * i) * -1 * squareSide);
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