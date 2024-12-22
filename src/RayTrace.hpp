#include <tuple>

Vector rayCast(Ray ray)
{
    //std::cout << ray.to << " , " << ray.direction << std::endl;
    Vector color = Vector(0, 0, 0);
    Material *hit = nullptr;
    double intersectT = INFINITY;
    std::tie(hit, intersectT) = Material::nearest(ray);
    //std::cout<<hit<<std::endl;

    if (hit != nullptr)
    {
        //std::cout << "Hit" << std::endl;
        Point hitPoint = ray.getPoint(intersectT);
        Vector normal = hit->getShape()->getNormal(hitPoint);
        color = hit->shade(&hitPoint, ray.from - Point(0, 0, 0), &normal);
    }
    return color;
}

Vector rayTrace(Ray ray, int ttl)
{
    return rayCast(ray);
}
