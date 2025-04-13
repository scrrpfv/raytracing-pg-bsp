#include <iostream>
#include <tuple>
#include <vector>
#include <math.h>
#include <cmath>
#include "src/Shapes.hpp"
#include "src/Scene.hpp"
#include "src/Material.hpp"
#include "src/Camera.hpp"
#include "src/Point.hpp"
#include "src/Ray.hpp"
#include "src/Vector.hpp"
#include "src/MaterialObjReader.hpp"

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
            int roughness;
            cin >> center >> radius >> o >> kd >> ks >> ka >> kr >> kt >> roughness >> ior;
            objects.emplace_back(new Sphere(center, radius), o, Vector(ka, ka, ka), Vector(kd, kd, kd), Vector(ks, ks, ks), Vector(kr, kr, kr), kt, roughness, ior);
        }
        else if (input == 'p')
        {
            Vector n, o;
            Point p0;
            double kd, ks, ka, kr, kt, ior;
            int roughness;
            cin >> p0 >> n >> o >> kd >> ks >> ka >> kr >> kt >> roughness >> ior;
            objects.emplace_back(new Plane(n, p0), o, Vector(ka, ka, ka), Vector(kd, kd, kd), Vector(ks, ks, ks), Vector(kr, kr, kr), kt, roughness, ior);
        }
        else if (input == 'o')
        {
            string filename, rest;
            cin >> filename >> rest;

            ObjReader objReader = ObjReader(filename);
            objReader.attachMaterials(objects);
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
        else if (input == 't') {
            Point p1, p2, p3;
            Vector color;
            double intensity;
            int t;
            
            cin >> p1 >> p2 >> p3>> intensity >> color >> t;
            if (t < 1) {
                Point pos = (p2 + p3) / 2;
                Light light = Light(p1, color, intensity / 255.0);
                lights.push_back(light);
            } else {
                Vector u = (p2 - p1)/t;
                Vector v = (p3 - p1)/t;
                intensity = intensity / ((t + 1) * (t + 1));
                for (int i = 0; i <= t; i++) {
                    for (int j = 0; j <= t; j++) {
                        Point pos = p1 + u * i + v * j;
                        Light light = Light(pos, color, intensity / 255.0);
                        lights.push_back(light);
                    }
                }
            }
        }
        else if (input == 'a')
        {
            cin >> ambientLight;
            ambientLight = ambientLight / 255.0;
        }
        else if (input == 'e')
        {
            break;
        }
    }
    camera->render(f, ttl);

    return 0;
}