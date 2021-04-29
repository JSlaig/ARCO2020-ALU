#ifndef NUMERO_H
#define NUMERO_H
#include <bitset>


class numero
{
public:
    numero();
    numero(float num);

    /*Getters y setters*/

    void setNum(float num);
    //===========================
    unsigned int getPartFrac();
    std::bitset<23> getPartFracBit();
    void setPartFrac(unsigned int num);
    void setPartFracBit(std::bitset<23> numero);

    //===========================
    unsigned int getExpo();
    std::bitset<8> getExpoBit();
    void setExpo(unsigned int);
    void setExpoBit(std::bitset<8> exp);

    //===========================
    unsigned int getSing();
    void setSing(unsigned int);

    //===========================
    std::bitset<24> getMantisa();
    void setMantisa(std::bitset<24> mantisa);


    /*Funciones restantes*/
    void floatToIEE(float num);



private:


    union Code {

        struct{
            unsigned int partFrac : 23;
            unsigned int expo : 8;
            unsigned int sign : 1;
        }bitfield;

        float numero;
        unsigned int numerox;
    }bitfield;

    struct numIEE{

        unsigned int partFrac : 23;
        unsigned int expo : 8;
        unsigned int sign : 1;

        float numero;

        std::bitset<23>partFracBit;
        std::bitset<24>mantisaBit;
        std::bitset<8>expoBit;


    }numIEE;



};

#endif // NUMERO_H
