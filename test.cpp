#include <iostream>
#include "src/Transform.hpp"
#include "src/Shapes.hpp"

int main(int argc, char const *argv[])
{
    Matrix m;
    std::cout<<"M antes: \n"<<m<<std::endl;
    Matrix a = m.translate(1, 2, 3).reflectXY().rotateX(45).scale(2,2,2);
    Matrix b = Matrix::translation(1,2,3);
    Matrix c = m*b;
    std::cout<<"M depois: \n"<<m<<std::endl;
    std::cout<<"B: \n"<<b<<std::endl;
    std::cout<<"A: \n"<<a<<std::endl;
    std::cout<<"C: \n"<<c<<std::endl;
    return 0;
}
