#ifndef RAYHEADER
#define RAYHEADER

class Ray
{
public:
    Point from;
    Point to;
    Vector direction;

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