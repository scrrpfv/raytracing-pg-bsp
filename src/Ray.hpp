#ifndef RAYHEADER
#define RAYHEADER

class Ray
{
public:
    Point from;
    Point to;
    Vector direction;

    Ray refract(Vector normal, double ior)
    {
        double cosI = -1 * direction.dot(normal);
        Vector refractedNormalComponent = normal;
        double n = ior;
        if (cosI < 0)
        {
            refractedNormalComponent = -1 * normal;
            n = 1 / ior;
            cosI *= -1;
        }

        double delta = 1.0 - (1.0 - cosI * cosI) / (n * n);
        if (delta < 0)
        {
            throw -1;
        }
        Vector refractedDirection = direction / n + refractedNormalComponent * (cosI / n - sqrt(delta));
        return Ray(from, from + refractedDirection);
    }

    Ray(Point from, Point to) : from(from), to(to)
    {
        direction = (to - from).normalize();
    }

    Point getPoint(double t)
    {
        return from + direction * t;
    }

    void print()
    {
        std::cout << "-Ray-\nfrom: " << std::endl;
        from.print();
        std::cout << "\ndirection: " << std::endl;
        direction.print();
    }
};

#endif