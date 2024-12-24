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
    RayCastResult cast = rayCast(ray);
    if (cast.hit && ttl != 0)
    {
        if (cast.hit->kr > almostZero)
        {
            Vector reflectedColor = rayTrace(cast.reflectedRay, ttl - 1);
            return cast.color + reflectedColor * cast.hit->kr;
        }
        if (cast.hit->kt > almostZero)
        {
            try
            {
                Ray refractedRay = ray.refract(cast.hit->getShape()->getNormal(ray, 0), cast.hit->ior);
                Vector refractedColor = rayTrace(refractedRay, ttl - 1);
                // Vector refractedColor = rayTrace(Ray(cast.reflectedRay.from, cast.reflectedRay.from + ray.direction), ttl - 1);
                return cast.color + refractedColor * cast.hit->kt;
            }
            catch (int e)
            {
                return cast.color;
            }
        }
    }

    return cast.color;
}
