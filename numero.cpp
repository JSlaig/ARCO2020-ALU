#include "numero.h"

    numero::numero(){

    }
    numero::numero(float num)
    {

    floatToIEE(num);

    }


    /*Funciones restantes*/
    void numero::floatToIEE(float num){

        setNum(num);

        union Code a;
        a.numero = num;
        setSing(a.bitfield.sign);
        setPartFrac(a.bitfield.partFrac);
        setExpo(a.bitfield.expo);
        //==
        setPartFracBit(getPartFrac());
        setExpoBit(getExpo());

    }

    /*Getters y setters*/

    unsigned int numero::getPartFrac(){
        return numIEE.partFrac;
    }
    std::bitset<23> numero::getPartFracBit(){
        return numIEE.partFracBit;
    }
    void numero::setPartFrac(unsigned int num){
        numIEE.partFrac = num;
    }
    void numero::setPartFracBit(unsigned int pFrac){
        std::bitset<23> numero(pFrac);

        numIEE.partFracBit = numero;
    }

    //===========================
    unsigned int numero::getExpo(){
        return numIEE.expo;
    }
    std::bitset<8> numero::getExpoBit(){
        return numIEE.expoBit;
    }
    void numero::setExpo(unsigned int exp){
        numIEE.expo = exp;
    }
    void numero::setExpoBit(unsigned int exP){
        std::bitset<8> exp(exP);
        numIEE.expoBit = exp;
    }

    //===========================
    unsigned int numero::getSing(){
        return numIEE.sign;
    }
    void numero::setSing(unsigned int sign){
        numIEE.sign = sign;
    }

    //===========================
    std::bitset<24> numero::getMantisa(){
        return numIEE.mantisaBit;
    }
    void numero::setMantisa(std::bitset<24> mantisa){
        numIEE.mantisaBit = mantisa;
    }

    void numero::setNum(float num){
       numIEE.numero = num;
    }
