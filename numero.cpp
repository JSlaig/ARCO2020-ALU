#include "numero.h"

    numero::numero(){

    }
    numero::numero(float num)
    {

        floatToIEE(num);

    }
    numero::numero(std::string nan){
        numIEE.nan = true;
       // numIEE.infinito = nan;

        floatToIEE(0);
    }

    /*Funciones restantes*/
    void numero::setInfinito(bool otro){
        numIEE.infinito = otro;
    }
    bool numero::getInfinito(){
        return numIEE.infinito;
    }

    bool numero::getIndeterminado(){
        return numIEE.indeterminado;
    }
    void numero::setIndeterminado(bool otro){
        numIEE.indeterminado = otro;
    }

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
    float numero::IEEtoFloat (unsigned int exponente, unsigned int signo, unsigned int parteFracc){

        numero_type.bitfield.expo = exponente;
        numero_type.bitfield.sign = signo;
        numero_type.bitfield.partFrac = parteFracc;

        return numero_type.numero;
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
    std::bitset<24> numero::getMantisa(bool denormal){

        for(int i = 0;i < 23;i++){
            numIEE.mantisaBit.set(i,numIEE.partFracBit[i]);
        //numIEE.mantisaBit[i] = numIEE.partFracBit[i];
        }

        numIEE.mantisaBit.set(23,1);

        return numIEE.mantisaBit;
    }
    void numero::setMantisa(std::bitset<24> mantisa){
        numIEE.mantisaBit = mantisa;
    }

    void numero::setNum(float num){
       numIEE.numero = num;
    }

    float numero::getNum(){
        return numIEE.numero;
    }

    bool numero::getNan(){
        return numIEE.nan;
    }


