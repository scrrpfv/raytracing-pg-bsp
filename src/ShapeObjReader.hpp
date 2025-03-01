#ifndef OBJREADERHEADER
#define OBJREADERHEADER

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Vector.hpp"
#include "Point.hpp"
#include "Colormap.hpp"
#include "Shapes.hpp"

class ObjReader : public Shape
{
private:
    std::ifstream file;
    std::vector<Point> vertices;
    std::vector<Vector> normals;
    std::vector<Face> faces;
    std::vector<std::vector<Point>> facePoints;
    MaterialProperties curMaterial;
    colormap cmap;

public:
    ObjReader(std::string filename) : cmap(cmap)
    {
        file.open(filename);
        if (!file.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
            return;
        }

        std::string line, mtlfile, colorname, filename_mtl;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "mtllib")
            {
                iss >> filename_mtl;
                std::string filename_mtl_path = filename.replace(filename.length() - 3, 3, "mtl");
                cmap = colormap(filename_mtl_path);
            }
            else if (prefix == "usemtl")
            {
                iss >> colorname;
                curMaterial = cmap.getMaterialProperties(colorname);
            }
            else if (prefix == "v")
            {
                double x, y, z;
                iss >> x >> y >> z;
                vertices.emplace_back(x, y, z);
            }
            else if (prefix == "vn")
            {
                double x, y, z;
                iss >> x >> y >> z;
                normals.emplace_back(x, y, z);
            }
            else if (prefix == "f")
            {
                Face face;
                char slash;
                for (int i = 0; i < 3; ++i)
                {
                    int _;
                    iss >> face.verticeIndice[i] >> slash >> _ >> slash >> face.normalIndice[i];
                    face.ka = curMaterial.ka;
                    face.kd = curMaterial.kd;
                    face.ks = curMaterial.ks;
                    face.ke = curMaterial.ke;
                    face.ns = curMaterial.ns;
                    face.ni = curMaterial.ni;
                    face.d = curMaterial.d;
                    face.verticeIndice[i]--;
                    face.normalIndice[i]--;
                }
                faces.push_back(face);
            }
        }

        for (const auto &face : faces)
        {
            std::vector<Point> points = {
                vertices[face.verticeIndice[0]],
                vertices[face.verticeIndice[1]],
                vertices[face.verticeIndice[2]]};
            facePoints.push_back(points);
        }

        file.close();
    }

    // Implementações dos métodos de Shape
    double rayIntersect(const Ray &ray) override
    {
        // Implementação da interseção do raio com o objeto .obj
        return -1; // Retornar um valor adequado
    }

    double rayIntersect(Ray &ray) override
    {
        return -1; // Retornar um valor adequado
    }

    Vector getNormal(Ray &ray, const double t) override
    {
        return Vector(); // Implementação adequada
    }

    Vector getNormal(Point &point) override
    {
        return Vector(); // Implementação adequada
    }

    void applyTransform(Matrix &transformMatrix) override
    {
        // Aplicar transformação aos pontos do objeto
    }

    // Getters
    std::vector<std::vector<Point>> getFacePoints() { return facePoints; }
    std::vector<Face> getFaces() { return faces; }
    Vector getKd() { return curMaterial.kd; }
    Vector getKa() { return curMaterial.ka; }
    Vector getKe() { return curMaterial.ke; }
    double getNs() { return curMaterial.ns; }
    double getNi() { return curMaterial.ni; }
    Vector getKs() { return curMaterial.ks; }
    double getD() { return curMaterial.d; }
    std::vector<Point> getVertices() { return vertices; }
};

#endif
