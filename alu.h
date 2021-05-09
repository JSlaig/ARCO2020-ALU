#ifndef ALU_H
#define ALU_H

#include <numero.h>
#include <QString>



class alu
{
public:

    alu();
    /*funciones*/

    numero sumaIEE(numero numA, numero numB);
    numero productoIEE(numero numA, numero numB);
    numero divisionIEE(numero numA, numero numB);

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
    bool compruebaNumOpuestos(numero numeroA, numero numeroB);

     std::bitset<48> productoSinSigno(std::bitset<24>& a, const std::bitset<24>& b, bool &c);
    bool acarreo(bool a, bool b, bool& c);
    bool sumaAuxiliar(std::bitset<48>& a, const std::bitset<48>& b);
    bool sumaAuxiliar(std::bitset<24>& a, const std::bitset<24>& b);
    int compruebaDenormal(int);

    bool compruebaCero(numero numeroA, numero numeroB);
    numero denormal();


private:

    //numero numeroA;
    //numero numeroB;
};

#endif // ALU_H
