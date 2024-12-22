#include <tuple>

Vector rayCast(Ray ray)
{
    //std::cout << ray.to << " , " << ray.direction << std::endl;
    Vector color = Vector(0, 0, 125);
    Material *hit = nullptr;
    double intersectT = INFINITY;
    std::tie(hit, intersectT) = Material::nearest(ray);
    //std::cout<<hit<<std::endl;
    //std::cout << "Hit Material Color in rayCast: " << hit->color << std::endl;
    
    if (hit)
    {
        //std::cout << "Hit" << std::endl;
        Point hitPoint = ray.getPoint(intersectT);
        Vector normal = hit->getShape()->getNormal(hitPoint);
        color = hit->shade(&hitPoint, -1*ray.direction, &normal);
        
        // std::cout<<"Normal: "<<normal<<std::endl;
        // std::cout<<"Hit: " <<hitPoint<<std::endl;
        //std::cout<<"Cor: "<<color<<std::endl;

    }
    return color;
}

Vector rayTrace(Ray ray, int ttl)
{
    return rayCast(ray);
}
