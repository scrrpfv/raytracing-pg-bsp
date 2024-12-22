#include <tuple>

Vector rayCast(Ray ray)
{
    Vector color = ambientLight;
    Material *hit = nullptr;
    double intersectT = INFINITY;
    std::tie(hit, intersectT) = Material::nearest(ray);
    if (hit)
    {
        Point hitPoint = ray.getPoint(intersectT);
        Vector normal = hit->getShape()->getNormal(hitPoint);
        color = hit->shade(&hitPoint, -1 * ray.direction, &normal);
    }
    return color;
}

Vector rayTrace(Ray ray, int ttl)
{
    return rayCast(ray) * 255.0;
}
