#ifndef VECTORHEADER
#define VECTORHEADER
#include <iostream>
#include <math.h>

/*
Classe de vetores.

A saber que:
    - x = componente x
    - y = componente y
    - z = componente z

A classe precisa ser instanciada passando as componentes x, y e z
*/

class vetor{
    private:
        double x;
        double y;
        double z;
    
    public:

    //Construtores
    vetor() {}
    vetor(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    //Implemente os métodos de vetores aqui
    
    vetor soma_vetor(vetor outro) {
        vetor soma;
        soma.x = this->x + outro.x;
        soma.y = this->y + outro.y;
        soma.z = this->z + outro.z;
        return soma;
    }

    vetor diferenca_vetor(vetor outro) {
        vetor diferenca;
        diferenca.x = this->x - outro.x;
        diferenca.y = this->y - outro.y;
        diferenca.z = this->z - outro.z;
        return diferenca;
    }

    vetor produto_vetor(vetor outro) {
        vetor produto;
        produto.x = this->x - outro.x;
        produto.y = this->y - outro.y;
        produto.z = this->z - outro.z;
        return produto;
    }

    double norma() {
        double n = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
        return n;
    }

    //Print do vetor no formato <x, y, z>
    void print(){
        std::cout << "<" << x << ", " << y << ", " << z << ">" << std::endl;
    }

    //Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
};

#endif