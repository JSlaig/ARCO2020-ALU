#ifndef ALU_H
#define ALU_H

#include <numero.h>


class alu
{
public:

    alu();
    alu(float numA, float numB);

    /*funciones*/

    void sumaIEE();
    std::bitset<24> complemento2(std::bitset<24>);
    std::bitset<24> desplazarDerecha(std::bitset<24> p,int d, int bit);
    std::bitset<24> desplazarIzquierda(std::bitset<24> p,int d, int bit);
    int calculaK(std::bitset<24> p);
    std::bitset<24> sumaUno(std::bitset<24>);
    std::bitset<23> normalizaMantisa(std::bitset<24>mantisa);


private:

    numero numeroA;
    numero numeroB;
};

#endif // ALU_H
