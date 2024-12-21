#include <iostream>
#include <tuple>
#include <vector>
#include <math.h>
#include <cmath>
// #include "src/ObjReader.cpp"
#include "src/Shapes.hpp"
#include "src/Material.hpp"
#include "src/Camera.hpp"
#include "src/Point.hpp"
#include "src/Ray.hpp"
#include "src/Vector.hpp"

using namespace std;

int main()
{

    Camera *camera = nullptr;
    int vres, hres;
    double f;
    int ttl;
    while (cin)
    {
        char input;
        cin >> input;

        if (input == 'c')
        {
            Point c, m;
            Vector up;
            cin >> hres >> vres >> f >> up >> c >> m >> ttl;
            camera = new Camera(c, m, up, vres, hres);
        }
        else if (input == 's')
        {
            Vector o;
            Point center;
            double radius;
            double kd, ks, ka, kr, kt, ior;
            int eta;
            cin >> center >> radius >> o >> kd >> ks >> ka >> kr >> kt >> eta >> ior;
            objects.emplace_back(new Sphere(center, radius), o, ka, kd, ks, kr, kt, eta, ior);
        }
        else if (input == 'p')
        {
            Vector p0, o;
            Point n;
            double kd, ks, ka, kr, kt, ior;
            int eta;
            cin >> p0 >> n >> o >> kd >> ks >> ka >> kr >> kt >> eta >> ior;
            objects.emplace_back(new Plane(p0, n), o, ka, kd, ks, kr, kt, eta, ior);
        }
        else if (input == 'l')
        {
            Point pos;
            Vector color;
            double intensity;

            cin >> pos >> intensity >> color;
            Light light = Light(pos, color, intensity / 255.0);

            lights.push_back(light);
        }
        else if (input == 'a')
        {
            cin >> ambientLight;
            ambientLight = ambientLight * (1 / 255.0);
        }
        else if (input == 'e')
        {
            break;
        }
    }
    camera->render(f, ttl);

    return 0;
}