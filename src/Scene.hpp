#ifndef LIGHTHEADER
#define LIGHTHEADER
struct Light
{
    Point position;
    Vector color;
    double intensity;

    Light(Point position, Vector color, double intensity)
    {
        position = position;
        color = color;
        intensity = intensity;
    }
};

Vector ambientLight = Vector(255, 255, 255);
std::vector<Light> lights;
#endif
