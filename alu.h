#ifndef ALU_H
#define ALU_H
#include <bitset>
#include <QString>

class Alu
{
public:

    Alu();
    Alu(float numRealA,float numRealB);
    void transformIEE();
    void transformMantisa(std::bitset<24> mantisa,int desplazamiento);
    int desplazamientoNum(std::bitset<24> mantisa);
    void transformaPFraccionaria(std::bitset<24> mantisa);
    void floattoIEE(float num);
    QString getExp();
    QString getPFrac();
    QString getSigno();
    void sumaIEE();
    std::bitset<24> complemento2(std::bitset<24> mantisaA2);
    std::bitset<24> desplazarDerecha(std::bitset<24> p,int d, int bit);
    std::bitset<24> desplazarIzquierda(std::bitset<24> p,int d, int bit);
    int calculaK(std::bitset<24> p);
    std::bitset<24> sumaUno(std::bitset<24> p);
    std::bitset<23> normalizaMantisa(std::bitset<24>mantisa);
    //std::bitset<24> sumaMantisas(std::bitset<24> mantisaA,std::bitset<24> mantisaB);


private:


    struct numIEE{

        float numReal;
        unsigned int signo: 1;
        unsigned int exponente : 8;
        unsigned int pFranccionaria: 23;

        int desplazamiento;
        std::string mantisaString;

    }numIEE1,numIEE2;

    std::bitset<23> pFranccionaria;
    std::bitset<4> prueba;
    std::bitset<8> exponente;
    std::bitset<24> mantisaA;
    std::bitset<24> mantisaB;
    std::bitset<24> mantisaSuma;

    int c = 0;

    union Code {

        struct{

            unsigned int partFrac : 23;
            unsigned int expo : 8;
            unsigned int sign : 1;

        }bitfield;

        int numero;
    };

};

#endif // ALU_H
