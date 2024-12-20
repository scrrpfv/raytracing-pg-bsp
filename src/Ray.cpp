#include <iostream>
#include <math.h>
#include "Point.cpp"
#include "Vector.cpp"

#ifndef RAYHEADER
#define RAYHEADER

class Ray {
public:
    point from;
    point to;
    Vector direction;

    Ray(point from, point to){
        from = from; 
        direction = (to-from).normalize();
    }

    point getPoint(double t) {
        return from + direction*t;
    }

    void print(){
        std::cout<<"-Ray-\nfrom: "<<std::endl; from.print();
        std::cout<<"\ndirection: "<<std::endl; direction.print();
    }
};


#endif