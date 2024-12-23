#include "Point.hpp"
#include "Ray.hpp"

const float almostZero = 1e-8f;

class Shape
{
public:
    // Funções virtuais puras para testar interseção com um raio e obter o vetor normal
    virtual double rayIntersect(const Ray &ray)
    {
        return {}; // Implementação default
    }

    virtual double rayIntersect(Ray &ray)
    {
        return {}; // Implementação default
    }

    virtual Vector getNormal(Ray &ray, const double t)
    {
        return {}; // Implementação default retorna vetor nulo
    }

    virtual Vector getNormal(Point &point)
    {
        return {}; // Implementação default retorna vetor nulo
    }

    virtual Point getPoint()
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
    Sphere(Point center, double radius) : center(center)
    {
        R = radius;
    }

    Point getPoint()
    {
        return center;
    }

    Vector getNormal(Ray &ray, const double t)
    {
        Point P = ray.getPoint(t);
        return (P - center).normalize();
    }

    double rayIntersect(Ray &ray)
    {
        Vector diffVec = ray.from - center;

        double B = -2 * diffVec.dot(ray.direction);
        double C = diffVec.dot(diffVec) - R * R;
        double delta = B * B - 4 * C;

        if (delta < almostZero)
            return -1;

        // std::cout << "Delta: " << delta << std::endl;

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

    Vector getNormal(Ray &ray, const double t)
    {
        Vector align = ray.from - P0;
        if (normalVec.dot(align) > almostZero)
            return normalVec;
        return normalVec * -1;
    }

    double rayIntersect(Ray &ray)
    {
        double aux = ray.direction.dot(normalVec);
        if (abs(aux) < almostZero)
            return -1;

        double t = ((P0 - ray.from).dot(normalVec)) / aux;
        if (t > almostZero)
            return t;
        return -1;
    }
};

#endif
