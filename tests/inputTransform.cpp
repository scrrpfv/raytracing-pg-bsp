#include <iostream>
#include <tuple>
#include <vector>
#include <math.h>
#include <cmath>
#include "../src/Shapes.hpp"
#include "../src/Scene.hpp"
#include "../src/Material.hpp"
#include "../src/Camera.hpp"
#include "../src/Point.hpp"
#include "../src/Ray.hpp"
#include "../src/Vector.hpp"
#include "../src/MaterialObjReader.hpp"

using namespace std;

int main()
{

    Matrix t = Matrix::translation(50, 50, -50);
    Matrix rz90 = Matrix::rotationZ(90);

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

            Sphere *mySphere = new Sphere(center, radius);
            // mySphere->applyTransform(t);

            objects.emplace_back(mySphere, o, Vector(ka, ka, ka), Vector(kd, kd, kd), Vector(ks, ks, ks), Vector(kr, kr, kr), kt, roughness, ior);
        }
        else if (input == 'p')
        {
            Vector n, o;
            Point p0;
            double kd, ks, ka, kr, kt, ior;
            int roughness;
            cin >> p0 >> n >> o >> kd >> ks >> ka >> kr >> kt >> roughness >> ior;
            // Aplicar transformação no plano
            Plane *myPlane = new Plane(n, p0);

            Matrix r = Matrix().translate(-1 * p0).rotateZ(45).translate(p0);
            myPlane->applyTransform(r);

            objects.emplace_back(myPlane, o, Vector(ka, ka, ka), Vector(kd, kd, kd), Vector(ks, ks, ks), Vector(kr, kr, kr), kt, roughness, ior);
        }
        else if (input == 'o')
        {
            string filename, rest;
            cin >> filename >> rest;

            ObjReader objReader = ObjReader(filename);
            Matrix transform = Matrix().scale(0.5, 0.5, 0.5).rotateZ(90);
            objReader.applyTransform(transform);
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