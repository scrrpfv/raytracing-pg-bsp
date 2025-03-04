#include <cmath>

#ifndef VECTORHEADER
#define VECTORHEADER
/*
Classe de vetores.

A saber que:
    - x = componente x
    - y = componente y
    - z = componente z

A classe precisa ser instanciada passando as componentes x, y e z
*/

class Vector
{
public:
    double x;
    double y;
    double z;
    // Construtores
    Vector() {}
    Vector(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // Implemente os métodos de vetores aqui

    Vector operator+(Vector outro)
    {
        return Vector(x + outro.x,
                      y + outro.y,
                      z + outro.z);
    }

    Vector operator-(Vector outro)
    {
        return Vector(x - outro.x,
                      y - outro.y,
                      z - outro.z);
    }

    Vector operator/(double scalar)
    {
        return Vector(x / scalar, y / scalar, z / scalar);
    }

    Vector elementWiseMultiplication(Vector outro)
    {
        return Vector(x * outro.x,
                      y * outro.y,
                      z * outro.z);
    }

    Vector cross(Vector outro)
    {
        return Vector(y * outro.z - z * outro.y,
                      z * outro.x - x * outro.z,
                      x * outro.y - y * outro.x);
    }

    double dot(Vector outro)
    {
        return x * outro.x + y * outro.y + z * outro.z;
    }

    double norm()
    {
        double n = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
        return n;
    }

    Vector normalize()
    {
        double n = norm();
        return Vector(this->x / n, this->y / n, this->z / n);
    }

    // Print do vetor no formato <x, y, z>
    void print()
    {
        std::cout << "<" << x << ", " << y << ", " << z << ">" << std::endl;
    }

    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
};

inline Vector operator*(const Vector &vector, const double scalar)
{
    return Vector(scalar * vector.getX(), scalar * vector.getY(), scalar * vector.getZ());
}

inline Vector operator*(const double scalar, const Vector &vector)
{
    return Vector(scalar * vector.getX(), scalar * vector.getY(), scalar * vector.getZ());
}

inline std::istream &operator>>(std::istream &is, Vector &t)
{
    is >> t.x >> t.y >> t.z;
    return is;
}

inline std::ostream &operator<<(std::ostream &os, const Vector &t)
{
    os << t.x << " " << t.y << " " << t.z;
    return os;
}

#endif