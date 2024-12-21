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
    double d;
    int vres, hres;

    Camera(Point CenterCam, Point Aim, Vector Vup, double d, int vres, int hres)
    {
        camPosition = CenterCam;
        target = Aim;

        Vup = Vup;
        W = (target - camPosition).normalize();
        U = (Vup.cross(W)).normalize(); // aponta para esquerda
        V = W.cross(U);

        d = d;
        vres = vres;
        hres = hres;
    }

    void render(double f, int ttl)
    {
        std::ofstream ppm;
        ppm.open("render.txt");
        Point topleftPixel = camPosition + W * f + (V * (vres - 1) + (U * (hres - 1))) * squareSide / 2.0;
        ppm << "P3" << std::endl;
        ppm << hres << ' ' << vres << std::endl;
        ppm << 255 << std::endl;
        int k = 0;
        for (int i = 0; i < vres; i++)
        {
            for (int j = 0; j < hres; j++)
            {
                Point pixelPosition = topleftPixel + ((U * j - V * i) * -1 * squareSide);
                Vector pixelColor = rayTrace(Ray(camPosition, pixelPosition), ttl);
                int r = pixelColor.getX(), g = pixelColor.getY(), b = pixelColor.getZ();
                ppm << pixelColor;
            }
        }
    }

    // void render(double f, int ttl)
    // {
    //     Point topleftPixel = camPosition + W * f + (V * (vres - 1) + (U * (hres - 1))) * squareSide / 2.0;

    //     std::cout << "P3" << std::endl;
    //     std::cout << hres << ' ' << vres << std::endl;
    //     std::cout << 255 << std::endl;
    //     int k = 0;
    //     for (int i = 0; i < vres; i++)
    //     {
    //         for (int j = 0; j < hres; j++)
    //         {
    //             Point pixelPosition = topleftPixel + ((U * j - V * i) * -1 * squareSide);
    //             Vector pixelColor = rayTrace(Ray(camPosition, pixelPosition), ttl);
    //             int r = pixelColor.getX(), g = pixelColor.getY(), b = pixelColor.getZ();
    //             pixelColor.print();
    //         }
    //     }
    // }

    ~Camera() {
        // std::cout << "Camera destroyed" << std::endl;
    };
};

#endif