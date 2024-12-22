#include <tuple>

Vector rayCast(Ray ray)
{
    // std::cout << ray.to << " , " << ray.direction << std::endl;
    Vector color = Vector(1, 1, 1);
    Material *hit = nullptr;
    double intersectT = INFINITY;
    std::tie(hit, intersectT) = Material::nearest(ray);
    if (hit)
    {
        Point hitPoint = ray.getPoint(intersectT);
        Vector normal = hit->getShape()->getNormal(hitPoint);
        color = hit->shade(&hitPoint, -1 * ray.direction, &normal);

        // std::cout<<"Normal: "<<normal<<std::endl;
        // std::cout<<"Hit: " <<hitPoint<<std::endl;
        // std::cout<<"Cor: "<<color<<std::endl;
    }
    return color;
}

Vector rayTrace(Ray ray, int ttl)
{
    return rayCast(ray) * 255.0;
}
