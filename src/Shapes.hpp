#include "Point.hpp"
#include "Ray.hpp"
#include "Transform.hpp"

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

    // TODO implementar para cada forma
    virtual void applyTransform(Matrix &transformMatrix)
    {
        return;
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
        Vector normalVec = (P - center).normalize();
        if ((ray.from - center).norm() < R)
            return normalVec;
        return normalVec * -1;
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

        if (t1 > almostZero)
            return t1;
        if (t0 > almostZero)
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

#ifndef TRIANGLEHEADER
#define TRIANGLEHEADER

class Triangle : public Shape
{
public:
    Point p0, p1, p2;
    Vector normalVec;
    Triangle(Point p0, Point p1, Point p2, Vector normalVec) : p0(p0), p1(p1), p2(p2), normalVec(normalVec) {}

    Point getPoint()
    {
        return p0;
    }

    Vector getNormal(Ray &ray, const double t)
    {
        return normalVec;
    }

    double rayIntersect(Ray &ray)
    {

        Plane triangPlane = Plane(normalVec, p0);
        double t = triangPlane.rayIntersect(ray);

        if (t < almostZero)
            return -1;

        Point P = ray.getPoint(t);
        Vector edge0 = p1 - p0;
        Vector edge1 = p2 - p0;
        Vector C = P - p0;

        double dot00 = edge0.dot(edge0);
        double dot01 = edge0.dot(edge1);
        double dot11 = edge1.dot(edge1);
        double dotC0 = C.dot(edge0);
        double dotC1 = C.dot(edge1);

        double denom = dot00 * dot11 - dot01 * dot01;

        if (denom == 0)
            return -1;

        double beta = (dotC0 * dot11 - dotC1 * dot01) / denom;
        double gamma = (dotC1 * dot00 - dotC0 * dot01) / denom;
        double alpha = 1.0 - beta - gamma;

        if (alpha < almostZero || beta < almostZero || gamma < almostZero)
            return -1;

        return t;
    }
};

#endif