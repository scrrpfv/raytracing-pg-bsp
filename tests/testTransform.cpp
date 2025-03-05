#include <iostream>
#include "../src/Transform.hpp"
#include "../src/Shapes.hpp"
#include <cmath>

int testMatrixOps() {
    Matrix m;

    // Testando uma transformação de cada tipo
    Matrix combinedTransform = m
        .translate(1, 2, 3)     
        .rotateX(30)            
        .rotateY(45)            
        .rotateZ(60)            
        .scale(2, 0.5, 1.5)     
        .shear(0.5, 0.2, 0.1, 0.3, 0.4, 0.6) 
        .reflectYZ()           
        .reflectXY()
        .reflectXZ();

    std::cout << "Matriz de Transformação Combinada (Todos os tipos):\n";
    std::cout << combinedTransform << std::endl;

    
    Matrix translate = Matrix::translation(1,2,3);
    Matrix rotateX = Matrix::rotationX(30);
    Matrix rotateY = Matrix::rotationY(45);
    Matrix rotateZ = Matrix::rotationZ(60);
    Matrix scale = Matrix::scaleOp(2, 0.5, 1.5);
    Matrix shear = Matrix::shearOp(0.5, 0.2, 0.1, 0.3, 0.4, 0.6);
    Matrix reflectYZ = Matrix::reflectionYZ();
    Matrix reflectXY = Matrix::reflectionXY();
    Matrix reflectXZ = Matrix::reflectionXZ();

    Matrix test = m;
    test = translate * test;
    test = rotateX * test;
    test = rotateY * test;
    test = rotateZ * test;
    test = scale * test;
    test = shear * test;
    test = reflectYZ * test;
    test = reflectXY * test;
    test = reflectXZ * test;
    
    bool matricesAreEqual = true;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (std::abs(combinedTransform(i, j) - test(i,j)) > almostZero) {
                matricesAreEqual = false;
                std::cout<<combinedTransform(i,j)<<" "<<test(i,j)<<std::endl;
                break;
            }
        }
        if (!matricesAreEqual) break;
    }

    if (matricesAreEqual) {
        std::cout << "\nOs metodos de transformacao estão funcionando.\n";
    } else {
        std::cout << "\nErro: Os metodos de transformacao não estão funcionando corretamente.\n";
    }

    return 0;
}

int testSphereTransform() {
    // Objeto
    Sphere mySphere(Point(1, 1, 1), 1.0);
    std::cout << "Centro antes das transformações: " << mySphere.getPoint() << std::endl;

    // Transformações 
    Matrix translationMatrix = Matrix::translation(2, -1, 0);
    Matrix rotationXMatrix = Matrix::rotationX(45);
    Matrix rotationYMatrix = Matrix::rotationY(90);
    Matrix scaleMatrix = Matrix::scaleOp(1.5, 1.5, 1.5);
    Matrix reflectionXYMatrix = Matrix::reflectionXY();
    
    // Aplicando as transformações em sequência
    mySphere.applyTransform(translationMatrix);
    mySphere.applyTransform(rotationXMatrix);
    mySphere.applyTransform(rotationYMatrix);
    mySphere.applyTransform(scaleMatrix);
    mySphere.applyTransform(reflectionXYMatrix);

    // Verificação
    Matrix opMatrix = Matrix()
    .translate(2, -1, 0)
    .rotateX(45)
    .rotateY(90)
    .scale(1.5, 1.5, 1.5)
    .reflectXY();

    Point expectedCenter = opMatrix*Point(1,1,1);
    double expectedRadius = 1.5;

    std::cout << "Novo centro da esfera: " << mySphere.getPoint() << std::endl;
    std::cout << "Novo raio da esfera: " << mySphere.R << std::endl;

    std::cout<<expectedCenter<<std::endl;
    std::cout<<expectedRadius<<std::endl;

    // Comparação com tolerância
    if (std::abs(mySphere.getPoint().x - expectedCenter.x) < almostZero &&
        std::abs(mySphere.getPoint().y - expectedCenter.y) < almostZero &&
        std::abs(mySphere.getPoint().z - expectedCenter.z) < almostZero &&
        std::abs(mySphere.R - expectedRadius) < almostZero) {
        std::cout << "Teste da Esfera: Sucesso!\n";
    } else {
        std::cout << "Teste da Esfera: Falhou!\n";
    }

    return 0;
}

int testPlaneTransform() {
    // Objeto
    Plane myPlane(Vector(0, 1, 0), Point(0, 0, 0));
    std::cout << "P0 antes da transformacao: " << myPlane.P0 << std::endl;
    std::cout << "Normal antes da transformacao: " << std::endl;
    myPlane.normalVec.print();

    // Transformações
    Matrix translationMatrix = Matrix::translation(1, 2, 3);
    Matrix rotationYMatrix = Matrix::rotationY(45);
    Matrix shearMatrix = Matrix::shearOp(0.5, 0.2, 0.1, 0.3, 0.4, 0.6);
    Matrix reflectionXZMatrix = Matrix::reflectionXZ();

    // Aplicando as transformações
    myPlane.applyTransform(translationMatrix);
    myPlane.applyTransform(rotationYMatrix);
    myPlane.applyTransform(shearMatrix);
    myPlane.applyTransform(reflectionXZMatrix);

    // Verificação
    Matrix opMatrix = Matrix()
    .translate(1, 2, 3)
    .rotateY(45)
    .shear(0.5, 0.2, 0.1, 0.3, 0.4, 0.6)
    .reflectXZ();

    Point expectedP0 = opMatrix*Point(0,0,0);
    Vector expectedNormal = opMatrix*Vector(0,1,0);
    expectedNormal = expectedNormal.normalize();

    std::cout << "Novo P0 do plano: " << myPlane.P0 << std::endl;
    std::cout << "Nova normal do plano: " << std::endl;
    myPlane.normalVec.print();

    std::cout<<expectedP0<<std::endl;
    std::cout<<expectedNormal<<std::endl;

    // Comparação com tolerância
    if (std::abs(myPlane.P0.x - expectedP0.x) < almostZero &&
        std::abs(myPlane.P0.y - expectedP0.y) < almostZero &&
        std::abs(myPlane.P0.z - expectedP0.z) < almostZero &&
        std::abs(myPlane.normalVec.x - expectedNormal.x) < almostZero &&
        std::abs(myPlane.normalVec.y - expectedNormal.y) < almostZero &&
        std::abs(myPlane.normalVec.z - expectedNormal.z) < almostZero) {
        std::cout << "Teste do Plano: Sucesso!\n";
    } else {
        std::cout << "Teste do Plano: Falhou!\n";
    }


    return 0;
}

int testTriangleTransform() {
    // Objeto
    Triangle myTriangle(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0), Vector(0, 0, 1));
    std::cout << "P0 antes da transformacao: " << myTriangle.p0 << std::endl;
    std::cout << "P1 antes da transformacao: " << myTriangle.p1 << std::endl;
    std::cout << "P2 antes da transformacao: " << myTriangle.p2 << std::endl;
    std::cout << "Normal antes da transformacao: " << std::endl;
    myTriangle.normalVec.print();

    // Transformações 
    Matrix translationMatrix = Matrix::translation(1, 1, 1);
    Matrix rotationZMatrix = Matrix::rotationZ(90);
    Matrix scaleMatrix = Matrix::scaleOp(2, 2, 1);
    Matrix reflectionYZMatrix = Matrix::reflectionYZ();

    // Aplicando as transformações
    myTriangle.applyTransform(translationMatrix);
    myTriangle.applyTransform(rotationZMatrix);
    myTriangle.applyTransform(scaleMatrix);
    myTriangle.applyTransform(reflectionYZMatrix);

    // Verificação
    Matrix opMatrix = Matrix()
    .translate(1, 1, 1)
    .rotateZ(90)
    .scale(2, 2, 1)
    .reflectYZ();

    Point expectedP0 = opMatrix*Point(0,0,0);
    Point expectedP1 = opMatrix*Point(1,0,0);
    Point expectedP2 = opMatrix*Point(0,1,0);
    Vector expectedNormal = opMatrix*Vector(0,0,1);
    expectedNormal = expectedNormal.normalize();

    std::cout << "Novo p0 do triângulo: " << myTriangle.p0 << std::endl;
    std::cout << "Novo p1 do triângulo: " << myTriangle.p1 << std::endl;
    std::cout << "Novo p2 do triângulo: " << myTriangle.p2 << std::endl;
    std::cout << "Nova normal do triângulo: " << std::endl;
    myTriangle.normalVec.print();

    std::cout<<"valores esperados"<<std::endl;
    std::cout<<expectedP0<<std::endl;
    std::cout<<expectedP1<<std::endl;
    std::cout<<expectedP2<<std::endl;
    std::cout<<expectedNormal<<std::endl;


    // Comparação com tolerância
    if (std::abs(myTriangle.p0.x - expectedP0.x) < almostZero &&
        std::abs(myTriangle.p0.y - expectedP0.y) < almostZero &&
        std::abs(myTriangle.p0.z - expectedP0.z) < almostZero &&
        std::abs(myTriangle.p1.x - expectedP1.x) < almostZero &&
        std::abs(myTriangle.p1.y - expectedP1.y) < almostZero &&
        std::abs(myTriangle.p1.z - expectedP1.z) < almostZero &&
        std::abs(myTriangle.p2.x - expectedP2.x) < almostZero &&
        std::abs(myTriangle.p2.y - expectedP2.y) < almostZero &&
        std::abs(myTriangle.p2.z - expectedP2.z) < almostZero &&
        std::abs(myTriangle.normalVec.x - expectedNormal.x) < almostZero &&
        std::abs(myTriangle.normalVec.y - expectedNormal.y) < almostZero &&
        std::abs(myTriangle.normalVec.z - expectedNormal.z) < almostZero) {
        std::cout << "Teste do Triângulo: Sucesso!\n";
    } else {
        std::cout << "Teste do Triângulo: Falhou!\n";
    }

    return 0;
}

int testMatrixOps2() {
    Matrix m;

    // 1. Translação (tx=1, ty=2, tz=3)
    // 2. Rotação em X (45 graus)
    // 3. Escala (sx=2, sy=3, sz=4)
    Matrix combinedTransform = m.translate(1, 2, 3).rotateX(45).scale(2, 3, 4);

    std::cout << "Matriz de Transformação Combinada (Translação -> Rotação X -> Escala):\n";
    std::cout << combinedTransform << std::endl;

    // Matriz de Transformação Esperada
    Matrix expectedTransform(4,4);
    expectedTransform(0,0) = 2;
    expectedTransform(0,1) = 0;
    expectedTransform(0,2) = 0;
    expectedTransform(0,3) = 2;
    expectedTransform(1,0) = 0;
    expectedTransform(1,1) = 2.121321;
    expectedTransform(1,2) = -2.121321;
    expectedTransform(1,3) = -2.121321;
    expectedTransform(2,0) = 0;
    expectedTransform(2,1) = 2.828428;
    expectedTransform(2,2) = 2.828428;
    expectedTransform(2,3) = 14.14214;
    expectedTransform(3,0) = 0;
    expectedTransform(3,1) = 0;
    expectedTransform(3,2) = 0;
    expectedTransform(3,3) = 1;

    std::cout << "\nMatriz de Transformação Esperada:\n";
    std::cout << expectedTransform << std::endl;

    // Comparar as matrizes (com uma pequena tolerância)
    bool matricesAreEqual = true;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (std::abs(combinedTransform(i, j) - expectedTransform(i, j)) > 1E-3) {
                matricesAreEqual = false;
                break;
            }
        }
        if (!matricesAreEqual) break;
    }

    if (matricesAreEqual) {
        std::cout << "\nAs matrizes combinada e esperada são iguais (dentro da tolerância).\n";
    } else {
        std::cout << "\nErro: As matrizes combinada e esperada são diferentes!\n";
    }

    return 0;
}


int main(int argc, char const *argv[])
{
    testMatrixOps();
    std::cout<<std::endl;

    testSphereTransform();
    std::cout<<std::endl;

    testPlaneTransform();
    std::cout<<std::endl;

    testTriangleTransform();
    std::cout<<std::endl;

    testMatrixOps2();
    std::cout<<std::endl;

    return 0;
}