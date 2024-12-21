#include <tuple>
#include "Scene.hpp"
class Material
{
    Shape *shape;
    Vector color;
    double ka, kd, ks;
    int eta;
    double ior;

public:
    double kr, kt;

    Material(Shape *shape, Vector color, double ka, double kd, double ks, double kr, double kt, int eta, double ior) : shape(shape), ka(ka), kd(kd), ks(ks), kr(kr), kt(kt), eta(eta), ior(ior)
    {
        color = color / 255.0;
    }

    Shape *getShape() const
    {
        return shape;
    }

    Vector shade(Point *point, Vector view, Vector *normal);

    static std::tuple<Material *, double> nearest(Ray ray);
};

std::vector<Material> objects;

Vector Material::shade(Point *point, Vector view, Vector *normal)
{
    Vector resColor = color.elementWiseMultiplication(ambientLight) * ka;

    for (Light light : lights)
    {
        Vector lightDirection = light.position - *point;
        Vector r = (*normal) * 2.0 * normal->dot(lightDirection) - lightDirection;

        double t;
        Material *shadow;
        std::tie(shadow, t) = Material::nearest(Ray(*point, light.position));

        if (shadow == nullptr || lightDirection.norm() > t)
        {
            double dotdiff = lightDirection.dot(*normal);
            if (dotdiff > 0)
            {
                for (int i = 0; i < 3; i++)
                {
                    resColor = color * kd * dotdiff * light.intensity;
                }
            }

            double dotspec = r.dot(view);
            if (dotspec > 0)
            {
                resColor = resColor * ks * pow(dotspec, eta) * light.intensity;
            }
        }
    }
    return resColor;
}

std::tuple<Material *, double> Material::nearest(Ray ray)
{
    Material *hit = nullptr;
    double intersectT = INFINITY;

    for (Material material : objects)
    {
        // std::cout << material.getShape()->getPoint() << std::endl;
        double t = material.getShape()->rayIntersect(ray);

        if (t > 0 && t < intersectT)
        {
            intersectT = t;
            hit = &material;
        }
    }
    if (intersectT != INFINITY)
    {
        std::cout << "Hit " << intersectT << std::endl;
        return std::make_tuple(hit, intersectT);
    }
    return std::make_tuple(nullptr, INFINITY);
}