#include <tuple>

struct RayCastResult
{
    Material *hit;
    Vector color;
    Ray reflectedRay;

    RayCastResult(Material *hit, Vector color, Ray reflectedRay) : hit(hit), color(color), reflectedRay(reflectedRay) {}
};

RayCastResult rayCast(Ray ray)
{
    Vector color = ambientLight;
    Material *hit = nullptr;
    double intersectT = INFINITY;
    Point hitPoint;
    Vector normal;
    std::tie(hit, intersectT) = Material::nearest(ray);
    if (hit)
    {
        hitPoint = ray.getPoint(intersectT);
        normal = hit->getShape()->getNormal(ray, intersectT);
        color = hit->shade(&hitPoint, -1 * ray.direction, &normal);
    }
    return RayCastResult(hit, color, Ray(hitPoint, hitPoint + (ray.direction - 2 * normal * normal.dot(ray.direction)).normalize()));
}

Vector rayTrace(Ray ray, int ttl)
{
    Vector color;
    RayCastResult cast = rayCast(ray);
    if (cast.hit && (cast.reflectedRay.from.distance(ray.from) > almostZero))
    {
        color = cast.color;

        if (ttl > 0)
        {
            try
            {
                if (cast.hit->kt > almostZero)
                {
                    Ray refractedRay = ray.refract(cast.hit->getShape()->getNormal(ray, 0), cast.hit->ior);
                    color = color + rayTrace(refractedRay, ttl - 1) * cast.hit->kt;
                }
                if (cast.hit->kr.getX() > almostZero || cast.hit->kr.getY() > almostZero || cast.hit->kr.getZ() > almostZero)
                {
                    Vector reflectedColor = rayTrace(cast.reflectedRay, ttl - 1);
                    color = color + reflectedColor.elementWiseMultiplication(cast.hit->kr);
                }
            }
            catch (int e)
            {
                color = color + rayTrace(cast.reflectedRay, ttl - 1);
            }
        }
        return color;
    }
    return cast.color;
}
