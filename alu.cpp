#include "alu.h"
#include <bitset>
#include <iostream>
#include <QString>
#include <cmath>


    Alu::Alu(){

    }

    Alu::Alu(float numRealA,float numRealB){
    numIEE1.numReal = numRealA;
    numIEE2.numReal = numRealB;
    //transformIEE();
    floattoIEE(numRealA);
    //floattoIEE(numRealB);




    prueba = std::bitset<4>(10);


    mantisaA = std::bitset<24>(numIEE1.numReal);
    mantisaB = std::bitset<24>(numIEE2.numReal);
    complemento2(mantisaA);

    }


    void Alu::transformIEE(){
    /*Deteccion del signo*/
    if(numIEE1.numReal > 0)
        numIEE1.signo = 0;
    else
        numIEE1.signo = 1;
    std::bitset<5> pruebaBin(5);

    //std::bitset<24> mantisa(numIEE1.numReal);
    //std::cout << "Mantisa: " << mantisa << std::endl;
    /*Calculo del desplazamiento*/
    //numIEE1.desplazamiento = desplazamientoNum(mantisa);

    /*Transformacion del exponente*/
    std::bitset<8> exponente(127 + numIEE1.desplazamiento);

    /*Desplazo la mantisa*/
    //transformMantisa(mantisa,numIEE1.desplazamiento);

    /*Calculo de la parte fraccionaria*/
    //transformaPFraccionaria(mantisa);

    //std::bitset<24> mantisa(numIEE1.numReal);

    std::cout << "signo " << numIEE1.signo << std::endl;
    std::cout << "exponente " << exponente << std::endl;
    std::cout << "pFraccionaria " << numIEE1.signo << std::endl;
    std::cout << "Desplazamiento " << numIEE1.desplazamiento << std::endl;

    //std::cout << "Prueba de binario " << pruebaBin << std::endl;
    }

    int Alu::desplazamientoNum(std::bitset<24> mantisa){

        int desplazamiento = 0;
//        std::cout << "Mantisa: " << mantisa << std::endl;
//        std::cout << "Mantisa: " << mantisa[0] << std::endl;
//        std::cout << "Mantisa: " << mantisa[1] << std::endl;
//        std::cout << "Mantisa: " << mantisa[2] << std::endl;
//        std::cout << "Mantisa: " << mantisa[3] << std::endl;
//        std::cout << "Mantisa: " << mantisa[5] << std::endl;
//        std::cout << "Mantisa: " << mantisa[6] << std::endl;

        for(int i = (int)mantisa.size(); i > 0 ;i--){
            if(mantisa[i] == true){
               break;
            }else{
                desplazamiento++;
            }
        }
        std::cout << "Desplazamiento metodo " << desplazamiento << std::endl;

        return (mantisa.size() - desplazamiento);
    }

    void Alu::transformMantisa(std::bitset<24> mantisa,int desplazamiento){

        for(int i = 0; i < desplazamiento;i++){

            for(int j = 0; i < (int)mantisa.size() - 1;i++){
                mantisa.set(j,mantisa[j+1]);
            }

           mantisa.set((int) (mantisa.size() - 1) , 0);
        }


    }

    void Alu::transformaPFraccionaria(std::bitset<24> mantisa){

        //std::bitset<23> pFranccionaria;

        for(int i = 0 ; i < (int)pFranccionaria.size();i++){
          pFranccionaria.set(i,mantisa[i+1]);
        }

    }

    void Alu::floattoIEE (float num){

        union Code a;

        a.numero = num;
        numIEE1.signo = a.bitfield.sign;
        numIEE1.exponente =a.bitfield.expo;
        numIEE1.pFranccionaria = a.bitfield.partFrac;

        exponente = std::bitset<8>(numIEE1.exponente);
        pFranccionaria = std::bitset<23>(numIEE1.pFranccionaria);


        std::cout << "signo " << numIEE1.signo << std::endl;
        std::cout << "Exponente " << exponente << std::endl;
        std::cout << "parte fraccionaria " << pFranccionaria << std::endl;

    }
    QString Alu::getSigno(){
        return QString::number(numIEE1.signo);
    }
    QString Alu::getExp(){
        return QString::fromStdString(exponente.to_string());
    }
    QString Alu::getPFrac(){
        return QString::fromStdString(pFranccionaria.to_string());
    }








    /***************************************************************************************************************************/

    void Alu::sumaIEE(){

        /*Paso 1*/

        int g = 0,r = 0,st = 0;
        int signoSuma = 0;
        unsigned int n;
        int exponenteSuma = 0;
        int d = 0;
        int k = 0;
        std::bitset<24> p;
        bool operandos_intercambiados = false;
        bool complemento_p = false;

        /*Paso 2*/
        if(numIEE1.exponente > numIEE2.exponente){

        }

        /*Paso 3*/
        else{
            exponenteSuma = numIEE1.exponente;
            d = (numIEE1.exponente - numIEE2.exponente);
        }

        /*Paso 4*/
        if(numIEE1.signo != numIEE2.signo){
            mantisaB = complemento2(mantisaB);
        }

        /*Paso 5*/
        p = mantisaB;

        /*Paso 6*/
        if(d != 0){
            g = p[d-1];

            if(d > 1){
                r = p[d-2];
            }
            /********FALTA EL STICKY******/
        }

        /*Paso 7*/
        if(numIEE1.signo != numIEE2.signo){
            p = desplazarDerecha(p,d,true);
        }else{
            p= desplazarDerecha(p,d,false);
        }

        /*Paso 8*/
        for(int i = (int)mantisaA.size()-1;i >= 0;i--){
           if((mantisaA[i] && p[i]) == false){

               if(c == 1){
                   p[i] = true;
                   c = 0;
               }else
                    p[i] = false;

           }else{
               if(mantisaA[i] != p[i]){
                   if(c == 1){
                       p[i] = false;
                       c = 0;
                   }else
                        p[i] = true;
               }
               else{
                   p[i] = false;
                   c = 1;
               }
           }
        }

        /*Paso 9*/
        if((numIEE1.signo != numIEE2.signo) && p[(int)p.size()-2] == true && c == 0){
            p = complemento2(p);
            complemento_p = true;
        }

        /*Paso 10*/
        if((numIEE1.signo == numIEE2.signo) && c == 1){

            if(g == r == st == 0){
                st = 0;
            }else{
                st = 1;
            }

            r = p[0];

            p = desplazarDerecha(p,1,c);

            exponenteSuma = exponenteSuma +1;

        }else{
            k = calculaK(p);
            if(k == 0){
                if(r == st == 0){
                    st = 0;
                }else{
                    st = 1;
                }
               r = g;
            }else{
                r = 0;
                st = 0;
                p = desplazarIzquierda(p,k,g);
                exponenteSuma = exponenteSuma - k;
            }
        }

        /*Paso 11*/
       if((r == 1 && st == 1) || (r == 1 && st == 0 && p[0] == 1)){

            p = sumaUno(p);

            if(c == 1){
                p = desplazarDerecha(p,1,c);
                exponenteSuma = exponenteSuma + 1;
                }
            }

         mantisaSuma = p;

        /*Paso 12*/
        if(operandos_intercambiados == false && complemento_p == true){
            signoSuma = numIEE2.signo;
        }else{
            signoSuma = numIEE1.signo;
        }

        /*Paso 13*/
        //std::bitset<24> suma = (signoSuma * mantisaSuma * pow(,2exponenteSuma));
        std::bitset<8>exponenteSumaBin(exponenteSuma);
    }


    std::bitset<24> Alu::complemento2(std::bitset<24> mantisaA2){
        std::cout << "mantisa antes"<< mantisaA2.to_string() << std::endl;

        mantisaA2.flip();
        mantisaA2 = sumaUno(mantisaA2);

        std::cout << "mantisa despues"<< mantisaA2.to_string() << std::endl;
    return mantisaA2;

    }

    std::bitset<24> Alu::desplazarDerecha(std::bitset<24> p,int d, int bit){

    for(int j = 0; j < d;j++){

            for(int i = (int)p.size(); i > 1;i--){
                p.set(i,p[i-1]);
            }

            p.set(0,bit);
       }
    return p;
    }

    std::bitset<24> Alu::desplazarIzquierda(std::bitset<24> p,int d, int bit){
        for(int j = 0;j < d;j++){

            for(int i = 0; i < (int)p.size()-1;i++){
                p.set(i,p[i+1]);
            }
           p.set((int)p.size()-1,bit);
        }
        return p;
    }

    int Alu::calculaK(std::bitset<24> p){
        int k = 0;

        for(int i = 0;i < (int)p.size();i++){
            if(p[i] != true){
                k++;
            }else{
                break;
            }
        }
        return k;
    }

    std::bitset<24> Alu::sumaUno(std::bitset<24> p){

        for(int i = (int)mantisaA.size()-1;i >= 0;i--){

           if((p) == false){

               if(c == 1){
                   p[i] = true;
                   c = 0;
               }else
                    p[i] = false;

           }else{
               if(mantisaA[i] != p[i]){
                   if(c == 1){
                       p[i] = false;
                       c = 0;
                   }else
                        p[i] = true;
               }
               else{
                   p[i] = false;
                   c = 1;
               }
           }
        }

        return p;
    }

    /*std::bitset<23> Alu::normalizaMantisa(std::bitset<24>mantisa){

        int desplazamiento = 0;

        for(int i = 0; i < (int)mantisa.size();i++){
            if(mantisa[i] == true){
                break;
            }else{
                desplazamiento++;
            }
        }

        return
    }*/


























