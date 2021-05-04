#ifndef ALU_H
#define ALU_H

#include <numero.h>
#include <QString>


class alu
{
public:

    alu();
    alu(float numA, float numB);

    /*funciones*/

    numero sumaIEE();
    numero productoIEE();
    int minimo(int t1, int t2);
    std::bitset<24> complemento2(std::bitset<24>);
    std::bitset<24> desplazarDerecha(std::bitset<24> p,int d, int bit);
    std::bitset<24> desplazarIzquierda(std::bitset<24> p,int d, int bit);
     std::bitset<48> desplazarIzquierda(std::bitset<48> p,int d, int bit);
    int calculaK(std::bitset<24> p);
    int calculaK(std::bitset<48> p);
    std::bitset<24> sumaUno(std::bitset<24> p);
    int acarreoUno(std::bitset<24> p);
    std::bitset<24> normalizaMantisa(std::bitset<24>mantisa);
    std::bitset<24> sumaBinaria(std::bitset<24> a,std::bitset<24> b);
    int  acarreoBinario(std::bitset<24> a,std::bitset<24> b);
    int esDenormal (numero num);
    std::bitset<23> mantisaToPartFrac(std::bitset<24> p);

    // metodos para convertir de binario a hexadecimal
    std::string cadenaConcatenadaBinaria(const std::string &cad1,const std::string &cad2,const std::string &cad3 );
    std::string hexadecimal(std::string cadena);
    std::string conversorBinarioHexadecimal(std::string binario);
    bool compruebaNumOpuetos();
     std::bitset<48> bitsetMultiply(std::bitset<24>& x, const std::bitset<24>& y, bool &carry);
    bool fullAdder(bool b1, bool b2, bool& carry);
    bool bitsetAdd(std::bitset<48>& x, const std::bitset<48>& y);
    bool bitsetAdd(std::bitset<24>& x, const std::bitset<24>& y);
    int compruebaDenormal(int);
    QString returnNum1(char);
    QString returnNum2(char);
    numero denormal();


private:

    numero numeroA;
    numero numeroB;
};

#endif // ALU_H
