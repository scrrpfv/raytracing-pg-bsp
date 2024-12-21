#include "Point.hpp"
#include "Ray.hpp"

class Shape
{
public:
    // Funções virtuais puras para testar interseção com um raio, aplicar uma matriz de transformação e obter o vetor normal
    virtual double rayIntersect(const Ray &ray)
    {
        return {}; // Implementação default
    }

    virtual Vector getNormal(const Point &point)
    {
        return {}; // Implementação default retorna vetor nulo
    }
};

#ifndef SPHEREHEADER
#define SPHEREHEADER

class Sphere : public Shape
{
public:
    Point center;
    double R;
    Sphere(Point center, double radius)
    {
        center = center;
        R = radius;
    }

    Vector getNormal(Point P)
    {
        return (P - center).normalize();
    }

    double rayIntersect(Ray ray)
    {
        Vector diffVec = center - ray.from;

        double B = -2 * diffVec.dot(ray.direction);
        double C = diffVec.dot(diffVec) - R * R;
        double delta = B * B - 4 * C;

        if (delta < 0)
            return -1;

        double t0 = (B + sqrt(delta)) / 2;
        double t1 = (B - sqrt(delta)) / 2;

        if (t1 > 0)
            return t1;
        if (t0 > 0)
            return t0;

        return -1;
    }
};

#endif

#ifndef PLANEHEADER
#define PLANEHEADER

class Plane : public Shape
{
public:
    Vector normalVec;
    Point P0;

    Plane(Vector normal, Point planePoint)
    {
        normalVec = normal.normalize();
        P0 = planePoint;
    }

    Vector getNormal()
    {
        return normalVec;
    }

    /*
    Recebe e modifica t caso haja interseção com o raio
    retorna true se houve intersecao e se t>0
    */
    double rayIntersect(Ray ray)
    {
        double aux = ray.direction.dot(normalVec);
        if (abs(aux) == 0)
            return -1;

        double t = ((P0 - ray.from).dot(normalVec)) / aux;
        if (t > 0)
            return t;
        return -1;
    }
};

#endif
