#include "alu.h"
#include<iostream>
#include <tgmath.h>
#include <stdlib.h>
#define MAXIMO 254
#define MINIMO 1

    alu::alu(){}


             // ===================================-SUMA-===================================
    numero alu::sumaIEE(numero numeroA, numero numeroB)
    {
        //Alejadro

      // Aqui se almacenara el resultado d la suma


        /*EJEMPLO DE USO
         * Consulta del exponente en int del numero A ->> numeroA.getExp();
         * Consulta del exponente en en binario (bitset<8>) ->> numeroA.getExpBit();
         *
         * Creacion de una variable bitset ->> std::bitset<24> nombreVar(int numeroAConvertir);
         */

        if(numeroA.getExpo() > MAXIMO || numeroB.getExpo() > MAXIMO){

                   /*Numero infinito*/
                   std::cout << "NUMERO DETECTADO COMO INF" << std::endl;


                   numero inf;
                   inf.setInfinito(true);
                   return inf;

               }

        if(compruebaNumOpuestos(numeroA,numeroB)){

            numero numZero = numero(0);

            return numZero;

        }else if(compruebaCero(numeroA,numeroB)){

            numero Zero = numero(0);
            return Zero;

        }
        /*Rellenar*/
        int signoA = numeroA.getSing();
        int signoB = numeroB.getSing();
        std::bitset<8> exponenteA_Bit = numeroA.getExpoBit();
        std::bitset<8> exponenteB_Bit = numeroB.getExpoBit();
        int exponenteA = numeroA.getExpo();
        int exponenteB = numeroB.getExpo();
        int parteFracA = numeroA.getPartFrac();
        int parteFracB = numeroB.getPartFrac();
        std::bitset<24> mantisaA = numeroA.getMantisa();
        std::bitset<24> mantisaB = numeroB.getMantisa();
        std::bitset<24> mantisaSuma;
        std::bitset<24> mantisaSumaFinal;

        std::cout << exponenteA_Bit << std::endl;

        int exponente_Suma = 0;
        int c = 0;
        int k = 0;
        int i = 0;

        /*Paso 1*/
        int g = 0, r = 0, st = 0;
        int n = 24;
        bool Ope_Inter = false;
        bool Comple_P  = false;
        int signoSuma = 0;
        int d = 0;
        std::bitset<24> P;

        /*Paso 2*/      
        if(exponenteA<exponenteB){
            signoA = numeroB.getSing();
            signoB = numeroA.getSing();
            exponenteA_Bit = numeroB.getExpoBit();
            exponenteB_Bit = numeroA.getExpoBit();
            exponenteA = numeroB.getExpo();
            exponenteB = numeroA.getExpo();
            parteFracA = numeroB.getPartFrac();
            parteFracB = numeroA.getPartFrac();

            mantisaA = numeroB.getMantisa();
            mantisaB = numeroA.getMantisa();
        }

        /*Paso 3*/
        exponente_Suma = exponenteA;
        d=exponenteA-exponenteB;
        /*Paso 4*/
        if(signoA!=signoB){
            mantisaB = complemento2(mantisaB);
        }
        //MORLA

        /*Paso 5*/
        P=mantisaB;
         std::cout <<  "MantisaA -> "<<mantisaA.to_string() <<std::endl;
         std::cout <<  "MantisaB -> "<<mantisaB.to_string() <<std::endl;

        /*Paso 6*/

        if(d-1 < 24 && d-1 >= 0){
            g=P[d-1];
        }
        if(d-2 < 24 && d-2 >= 0){
            r=P[d-2];
        }
        if(d-3 < 24 && d-3 >= 0){
            for(i=d;i<(int)P.size()-3;i++){
                if(P[d-i]==1){
                    st=1;
                    break;
                }
            }
        }
        std::cout << "paso 7, p antes de desplazarse -> " << P.to_string() << std::endl;

        /*Paso 7*/
        if(signoA!=signoB){
            P = desplazarDerecha(P,d,1);

        }else{
            P = desplazarDerecha(P,d,0);


        }
        //CHEMA
        /*Paso 8 [Bien]*/
        std::cout << "paso 8, mantisaA-> " << mantisaA.to_string() << std::endl;
        std::cout << "paso 8, antes p-> " << P.to_string() << std::endl;
        //bool c;
        c = acarreoBinario(mantisaA,P);
        P = sumaBinaria(mantisaA,P);     

        std::cout << "paso 8, despues p-> " << P.to_string() << std::endl;
        /*Paso 9*/



        if(((signoA != signoB) && (P[n-1]) == 1) && (c == 0)){
            P = complemento2(P);
            Comple_P = true;
        }

        /*Paso 10*/
        if((signoA == signoB) && (c == 1)){

            if((g == r) && (r == st) && (st == 0)){
                st = 0;
            }

            r = P[0];
            P = desplazarDerecha(P,1,c);
            exponente_Suma = exponente_Suma + 1;

        }else{


        k = calculaK(P);
        std::cout <<  "k es "<<k <<std::endl;

            if(k == 0){
                if((r == st) && (st == 0)){
                    st = 0;
                }
                r = g;
            }else{
                r = 0;
                st = 0;
            }

        std::cout << "paso 10, antes p-> " << P.to_string() << std::endl;
        P = desplazarIzquierda(P,k,g);
        exponente_Suma = exponente_Suma - k;
        }
        std::cout << "paso 10, despues p-> " << P.to_string() << std::endl;

        /*Paso 11*/
        if((r == 1 && st == 1) || (r == 1 && st == 0 && P[0] == 1)){

            c = acarreoUno(P);
            P = sumaUno(P);         

            if(c == 1){
                P = desplazarDerecha(P,1,c);
                exponente_Suma = exponente_Suma + 1;
            }

        }
        mantisaSuma = P;

        /*Paso 12*/
        if(Ope_Inter == false && Comple_P == true){
            signoSuma = signoB;
        }else{
            signoSuma = signoA;
        }

        //CHECHU

        /*Paso 13*/
        //Suma = (SignoSuma) * MantisaSuma * 2Exp
        QString suma;

        suma.append(signoSuma);

        std::cout << suma.toStdString() <<std::endl;

        std::cout << "Exponente -> " << exponente_Suma <<std::endl;
        std::cout << signoSuma <<std::endl;



        std::cout << mantisaToPartFrac(mantisaSuma) <<std::endl;

        /*********************Seteo del resultado final y, devolucion del tipo numero***********************/

        std::cout << "Resultadooooooooooooo final" <<std::endl;

        numero resultado;

        resultado.setExpo(exponente_Suma);
        resultado.setExpoBit(exponente_Suma);

        resultado.setSing(signoSuma);
        resultado.setPartFrac(mantisaToPartFrac(mantisaSuma).to_ulong());
        resultado.setPartFracBit(mantisaToPartFrac(mantisaSuma).to_ulong());

        resultado.setNum(resultado.IEEtoFloat(exponente_Suma,signoSuma,mantisaToPartFrac(mantisaSuma).to_ulong()));

        return resultado;

    }

         // ===================================-MULTIPLICACION-===================================

    numero alu::productoIEE(numero numeroA, numero numeroB){
        std::bitset<23> partefraccionaria;
        int t = 0;
        int t1,t2;
        if((numeroA.getExpoBit().to_string().compare("00000000")==0 && numeroA.getPartFracBit().to_string().compare("00000000000000000000000")==0)||
           (numeroB.getExpoBit().to_string().compare("00000000")==0 && numeroB.getPartFracBit().to_string().compare("00000000000000000000000")==0)){

                if ((numeroA.getExpoBit().to_string().compare("11111111")==0 && numeroA.getPartFracBit().to_string().compare("00000000000000000000000")==0) ||
                    (numeroB.getExpoBit().to_string().compare("11111111")==0 && numeroB.getPartFracBit().to_string().compare("00000000000000000000000")==0)){

                    numero nan = numero("NaN");
                    return nan;
                }
                numero zero = numero(0);
                return zero;
        }

        std::bitset<24> A;
        for(int i = 0; i<23; i++){
            A[i]=numeroA.getPartFracBit()[i];
        }
        A[A.size()-1] = 1;

        std::bitset<24> B;
        for(int i = 0; i<23; i++){
            B[i]=numeroB.getPartFracBit()[i];
        }
        B[B.size()-1] = 1;

        int expA = numeroA.getExpoBit().to_ulong();
        int expB = numeroB.getExpoBit().to_ulong();
        int signA = numeroA.getSing();
        int signB = numeroB.getSing();

        const int mantSize = A.size();
        std::bitset<mantSize> P;

    // 1.
        //CHECHU
        int signSol = 0;

        if(signA != signB){
             signSol = 1;
        }
        std::cout<<"signo de la solucion: "<<signSol<<std::endl;
    // 2.
        int expSol = expA-127 + expB-127;
    // 3.
        //3.1
        bool c;
        std::bitset<48> prod;
        prod = productoSinSigno(A, B,c);
        //3.2
        //CHEMA
        if(!prod[47]){
            prod<<=1;
        } else {
            expSol++;
        }
        //3.3
        bool round = prod[23];
        //3.4
        int x = 23;
        bool sticky;
        while (x > 0){
            x--;
            sticky = sticky || prod[x];
        }

        //JOSE

        //3.5
        if((round && sticky) || (round && !sticky && prod[24])){
            std::bitset<prod.size()> one;
            one.set(0, 1);
            sumaAuxiliar(prod, one);
        }


        std::bitset<24> manSol;
        for(int i = 0; i<24; i++){
            manSol[i] = prod[i+24];
        }

        if(expSol>128){
                    expSol=128;
                    prod.reset();
                    numero infinito;
                    infinito.setInfinito(true);
                    infinito.setSing(signSol);
                    return infinito;
        }

        int expMinimo=-126;
         // comprobacion de desbordamientos
        if (expSol <-126){
            std::cout<<"resultado denormal"<<std::endl;
            t = expMinimo - expSol;


            if (t >= (int)manSol.size()){
                numero indeterminado;
                indeterminado.setIndeterminado(true);
                return indeterminado;

            } else {

                prod>>=t;
                expSol = expMinimo;
              }
            for (int i = 24; i <48;i++){
                partefraccionaria[i-24] = prod[i];
            }
            numero denormal;
            denormal.setSing(signSol);
            denormal.setExpoBit(expSol);
            denormal.setPartFracBit(partefraccionaria.to_ulong());
            return denormal;
        }

         // ANALISIS DE OPERANDOS DENORMALES
        if (esDenormal(numeroA) ==1 || esDenormal(numeroB)==1){
            std::cout<<"entramos en operandos denormales"<<std::endl;
            // CASO 1
            if (expSol <expMinimo){
                std::cout<<"estas dentro del caso 1 del analisis de operandos denormales"<<std::endl;
                std::cout<<"resultado denormal"<<std::endl;
                t = expMinimo - expSol;
                if (t >= (int)manSol.size()){
                    manSol>>=t;
                    std::cout<<"existe underflow"<<std::endl;
                } else {
                    prod<<=t;
                    std::cout<<"resultado deberia ser denormal"<<std::endl;
                    expSol = -126;
                }

            }

            // CASO 2
            if (expSol == -126){
                t1 = expSol - expMinimo;
                t2 = calculaK(prod);
                t = minimo(t1, t2);
                expSol = expSol-t;
                prod = desplazarIzquierda(prod,t,0);
            }
            for(int i = 0; i<24; i++){
                manSol[i] = prod[i+24];
            }
            for (int i = 0; i <23; i++){
                partefraccionaria[i] = manSol[i];
            }

                numero denormalizado;

                denormalizado.setSing(signSol);
                denormalizado.setPartFracBit(partefraccionaria.to_ulong());
                denormalizado.setExpoBit(0);
                denormalizado.setNum(denormalizado.IEEtoFloat(0,signSol,partefraccionaria.to_ulong()));


            return denormalizado;
        }

        // CASO 3

        if (expSol == -126){

            if(expSol>128){
                        expSol=128;
                        prod.reset();
                        numero infinito;
                        infinito.setInfinito(true);
                        infinito.setSing(signSol);
                        return infinito;
            }

            int expMinimo=-126;
             // comprobacion de desbordamientos
            if (expSol <-126){
                std::cout<<"resultado denormal"<<std::endl;
                t = expMinimo - expSol;


                if (t >= (int)manSol.size()){
                    numero indeterminado;
                    indeterminado.setIndeterminado(true);
                    return indeterminado;

                } else {

                    prod>>=t;
                    expSol = expMinimo;
                  }
                for (int i = 24; i <48;i++){
                    partefraccionaria[i-24] = prod[i];
                }
                numero denormal;
                denormal.setSing(signSol);
                denormal.setExpoBit(expSol);
                denormal.setPartFracBit(partefraccionaria.to_ulong());
                return denormal;
            }
        }


        // actualizo mantisa solucion
        for(int i = 0; i<24; i++){
            manSol[i] = prod[i+24];
        }



        std::cout<<"signo de solucion : "<<signSol<<std::endl;
        std::cout<<"exponente de solucion : "<<expSol<<std::endl;
        std::cout<<"mantisa de solucion : "<<manSol<<std::endl;
        std::cout<<"Longitud de solucion : "<<manSol.size()<<std::endl;


        for (int i = 0; i <23; i++){
            partefraccionaria[i] = manSol[i];
        }
        numero resultado;

        float numero1 = numeroA.getNum();
        float numero2 = numeroB.getNum();

        resultado.setSing(signSol);

        resultado.setPartFracBit(partefraccionaria.to_ulong());

        /**/
        resultado.setPartFrac(partefraccionaria.to_ulong());
        resultado.setExpo(expSol+127);
        /**/

        resultado.setExpoBit(expSol+127);

        resultado.setNum(resultado.IEEtoFloat(expSol+127,signSol,partefraccionaria.to_ulong()));
        float resultadoprov = resultado.IEEtoFloat(expSol+127,signSol,partefraccionaria.to_ulong());

        std::cout<<"numero 1: "<<numero1<<std::endl;
        std::cout<<"numero 2: "<<numero2<<std::endl;
        std::cout<<"resultado: "<<resultadoprov<<std::endl;

        return resultado;
    }


    // ===================================-DIVISION-===================================

    numero alu::divisionIEE(numero numeroA, numero numeroB){

        numero numberA = numeroA;
        numero numberB = numeroB;
        numero numberR;
        //Caso especial infinito entre infinito

                if((numeroA.getExpoBit().to_string().compare("11111111")==0 && numeroA.getPartFracBit().to_string().compare("00000000000000000000000")==0) &&
                        (numeroB.getExpoBit().to_string().compare("11111111")==0 && numeroB.getPartFracBit().to_string().compare("00000000000000000000000")==0)){
                    numberR.setIndeterminado(true);
                    return numberR;
                }


            //Paso 1: Escalado de los numeros
            std::bitset<24> aproxA(std::string("1").append(numberA.getPartFracBit().bitset::to_string()));
            std::cout<<"MantisaA: "<<aproxA<<std::endl;

            std::bitset<24> aproxB(std::string("1").append(numberB.getPartFracBit().bitset::to_string()));
            std::cout<<"MantisaB: "<<aproxB<<std::endl;

            float escaladoA = 0.0;
            float escaladoB = 0.0;

            int power = 0;

            /*CHEMA*/

            for(int i = 23; i>= 0; i--){
              if((int)aproxA[i] == 1){
                escaladoA+=(float)pow(2.0, power);
              }
              if((int)aproxB[i] == 1){
                escaladoB+=(float)pow(2.0, power);
              }
              power--;
            }

            std::cout<<"AproximadoA: "<<escaladoA<<std::endl;
            std::cout<<"AproximadoB: "<<escaladoB<<std::endl;

            //Paso 2: Aproximacion del inverso de B

            double inversoB;


            if(escaladoB >= 1 && escaladoB < 1.25){
                inversoB = 1.0;
            }else{
                inversoB = 0.8;
            }

            std::cout<<"InversoB:"<<inversoB<<std::endl;


            //CHECHU
            //Metodo de goldsmitch

            numero escaladoIEEA(escaladoA);

            numero escaladoIEEB(escaladoB);

            numero inversoIEEB(inversoB);

            numero auxX = alu::productoIEE(escaladoIEEA, inversoIEEB);
            numero xSiguiente(auxX.getNum());

            numero auxY = alu::productoIEE(inversoIEEB, escaladoIEEB);
            numero y(auxY.getNum());

            numero dos(2);

            numero precision(0);

            numero r = numero();
            numero x;

            float resultado;

            //hay que iterar hasta precision de 10^-4 xi y xi+1
            do{
                x = xSiguiente;

                //r = 2 + (- yi);
                //Cambiamos el signo para la resta
                if(y.getSing() == 0){
                    y.setSing(1);
                }else{
                    y.setSing(0);
                }

                r = alu::sumaIEE(dos, y);

                //Volvemos a cambiar el signo para restablecerlo a su estado original
                if(y.getSing() == 0){
                    y.setSing(1);
                }else{
                    y.setSing(0);
                }
                //yi+1 = yi * r;
                y = alu::productoIEE(y, r);
                //xi+1 = xi * r;
                xSiguiente = alu::productoIEE(x, r);

                //Calculo precision

                /*Cambiamos el signo de x para que sea una resta,
                *no hace falta restablecerlo ya que en la siguiente iteracion
                *se vuelve a reasignar y fuera del bucle no tiene ningun uso
                */

                if(x.getSing() == 0){
                    x.setSing(1);
                }else{
                    x.setSing(0);
                }
                precision = alu::sumaIEE(xSiguiente, x);

                resultado = abs(precision.getNum());

            }while(resultado > 0.0001f);

            numberR.setPartFrac(xSiguiente.getPartFrac());
            numberR.setPartFracBit(xSiguiente.getPartFrac());

            //MORLA

            //Paso 3: Calculo del signo de la division
            if(numberA.getSing() == 0 && numberB.getSing() == 0){
                numberR.setSing(0);
            }else if(numberA.getSing() == 0 && numberB.getSing() == 1){
                numberR.setSing(1);
            }else if(numberA.getSing() == 1 && numberB.getSing() == 0){
                numberR.setSing(1);
            }else{
                numberR.setSing(0);
            }

            //Paso 4: Calculo del exponente de la division (falta pasar todas las operaciones sobre numero y alu)

            //ExpA - ExpB
            numero expoB(numeroB.getExpo());
            if(expoB.getSing() == 0){
                expoB.setSing(1);
            }else{
                expoB.setSing(0);
            }
            numero expoA(numeroA.getExpo());
            numero op1 = alu::sumaIEE(expoA, expoB);

            //resultado + EXP(A * 1/B)
            numero expoProd(xSiguiente.getExpo());
            numero op2 = alu::sumaIEE(op1, expoProd);

            numberR.setExpo(op2.getNum());
            numberR.setExpoBit(op2.getNum());
            std::cout<<"exponente numero A: "<<numeroA.getExpo()<<std::endl;
            std::cout<<"exponente numero B: "<<numeroB.getExpo()<<std::endl;
            std::cout<<"exponente numero Resultado: "<<numberR.getExpo()<<std::endl;

          /* if (numeroA.getExpo() + numeroB.getExpo() >255){
               std::cout<<"entras en infinito de alu.cpp"<<std::endl;
               numberR.setInfinito(true);
               return numberR;
           }*/

           if ((numeroA.getExpo()<126 && numeroB.getExpo()>126)||(numeroA.getExpo()>126 && numeroB.getExpo()<126)){
                  std::cout<<"entras en infinito de alu.cpp"<<std::endl;
                  numberR.setInfinito(true);
                  return numberR;
              }

            numberR.setNum(numberR.IEEtoFloat(numberR.getExpo(),numberR.getSing(),numberR.getPartFrac()));


            std::cout<<"Resultado division:"<<std::endl;
            std::cout<<"Signo: "<<numberR.getSing()<<std::endl;
            std::cout<<"Exponente: "<<numberR.getExpoBit()<<std::endl;
            std::cout<<"Parte Fraccionaria: "<<numberR.getPartFracBit()<<std::endl;

    return numberR;
    }


/*=======================-Metodos auxiliares utilizados en el codigo-=================*/

    int alu::esDenormal (numero num){


        if(num.getExpoBit().to_string().compare("00000000") == 0 && num.getPartFracBit().to_string().compare("00000000000000000000000") != 0)
        {
            return 1;
        }
            else
        {
            return -1;
        }
    }



    std::bitset<24> alu::complemento2(std::bitset<24> p)
    {
        std::bitset<24>resultado;
        /*Rellenar metodo*/

        p.flip();

        resultado = sumaUno(p);

        return resultado;

    }

    std::bitset<24> alu::desplazarDerecha(std::bitset<24> p, int d, int bit)
    {

        for(int j = 0; j < d; j++){
                for(int i = 0; i < (int) (p.size() - 1); i++)
                    p.set(i, p[i+1]);
                p.set((int) (p.size() - 1) , bit);
            }

            return p;

    }

    std::bitset<24> alu::desplazarIzquierda(std::bitset<24> p, int d, int bit)
    {

        //std::cout << "p antes izquierda-> " << p.to_string() << std::endl;

        for(int i = 0; i < d; i++){
                for(int i = (int) (p.size() - 1); i >= 0; i--){
                    p.set(i, p[i-1]);
                }
                p.set(0 , bit);
            }
        //std::cout << "p despues izquierda-> " << p.to_string() << std::endl;

            return p;
    }
    std::bitset<48> alu::desplazarIzquierda(std::bitset<48> p, int d, int bit)
    {

        //std::cout << "p antes izquierda-> " << p.to_string() << std::endl;

        for(int i = 0; i < d; i++){
                for(int i = (int) (p.size() - 1); i >= 0; i--){
                    p.set(i, p[i-1]);
                }
                p.set(0 , bit);
            }
        //std::cout << "p despues izquierda-> " << p.to_string() << std::endl;

            return p;
    }

    int alu::calculaK(std::bitset<24> p)
    {
        int i = (int)p.size()-1,k = 0;
                while (!p[i]) {
                    k++;
                    i--;
                }
    return k;
    }

    int alu::calculaK(std::bitset<48> p)
    {
        int i = (int)p.size()-1,k = 0;
                while (!p[i]) {
                    k++;
                    i--;
                }
    return k;
    }


    std::bitset<24> alu::sumaUno(std::bitset<24> p)
    {
        std::bitset<24> uno (1);
        return sumaBinaria(p,uno);

    }

    int alu::acarreoUno(std::bitset<24> p)
    {
        std::bitset<24> uno (1);
        return acarreoBinario(p,uno);

    }

    std::bitset<24> alu::normalizaMantisa(std::bitset<24> mantisa)
    {

        /*Rellenar metodo*/
        while(mantisa[23]!=1){
            mantisa = desplazarIzquierda(mantisa,1,0);
        }

        return mantisa;
    }

    std::bitset<24> alu::sumaBinaria(std::bitset<24> a,std::bitset<24> b){
        std::bitset<24> acarreo = 0;
        std::bitset<24> sm1 = 0;
          std::bitset<24>resultado = 0;
          std::bitset<24>uno(1);
          for (int j = 0; j < (int)a.size();j++)
            {
              sm1 = (((a >> j) & uno) ^ ((b >> j) & uno)) ^ acarreo;
              resultado =resultado | sm1 << j;
              acarreo = (((a >> j) & uno) & ((b >> j) & uno)) | (((a >> j) & uno) ^ ((b >> j) & uno)) & acarreo;

          }
          return resultado;
    }

    int alu::acarreoBinario(std::bitset<24> a,std::bitset<24> b){
        int acarreoResultante = 0;
        std::bitset<24> acarreo = 0;
        std::bitset<24> sm1 = 0;
          std::bitset<24>resultado = 0;
          std::bitset<24>uno(1);
          for (int j = 0; j < (int)a.size();j++)
            {
              sm1 = (((a >> j) & uno) ^ ((b >> j) & uno)) ^ acarreo;
              resultado =resultado | sm1 << j;
              acarreo = (((a >> j) & uno) & ((b >> j) & uno)) | (((a >> j) & uno) ^ ((b >> j) & uno)) & acarreo;

          }

          acarreoResultante = acarreo[0];
          return acarreoResultante;
    }

    std::bitset<23> alu::mantisaToPartFrac(std::bitset<24> p){

        std::bitset<23> partFrac;

        for(int i = 0; i < (int)partFrac.size();i++){
            partFrac[i] = p[i];
        }
        return partFrac;
    }

    /******************************************************************************/

std::string alu::hexadecimal(std::string cadena){
        //pasa cada 4 dígitos de binario a uno en hexadecimal
            if(cadena=="0000"){
                return "0";
            }else if(cadena=="0001"){
                return "1";
            }else if(cadena=="0010"){
                return "2";
            }else if(cadena=="0011"){
                return "3";
            }else if(cadena=="0100"){
                return "4";
            }else if(cadena=="0101"){
                return "5";
            }else if(cadena=="0110"){
                return "6";
            }else if(cadena=="0111"){
                return "7";
            }else if(cadena=="1000"){
                return "8";
            }else if(cadena=="1001"){
                return "9";
            }else if(cadena=="1010"){
                return "A";
            }else if(cadena=="1011"){
                return "B";
            }else if(cadena=="1100"){
                return "C";
            }else if(cadena=="1101"){
                return "D";
            }else if(cadena=="1110"){
                return "E";
            }else if(cadena=="1111"){
                return "F";
            }
               return 0;
        }

    std::string alu::conversorBinarioHexadecimal(std::string binario){
        //coges el numero en binario
            std::string b = binario+"";
            std::string sol = "";//solucion
            //separa el numero de 4en4 dígitos
            int numeroSeparaciones = binario.length()/4;
            if(binario.length()%4>0){//si el numero no es exacto añade una separacion
                numeroSeparaciones++;
            }
            for (int var = binario.length(); var < numeroSeparaciones*4; ++var) {//si el numero no es esacto añade 0 a la derecha
                b="0"+b;
            }
            for (int var = 0; var < numeroSeparaciones; ++var) {//coge los digitos binarios de 4 en 4 y llamando al metodo anterior, los pasa a hexadecimal
                sol+=hexadecimal(b.substr((var*4),4));
            }
            return sol;
        }

    std::string alu::cadenaConcatenadaBinaria(const std::string &cad1,const std::string &cad2,const std::string &cad3 ){
        return cad1 + cad2 + cad3;
    }

    bool alu::compruebaNumOpuestos(numero numeroA, numero numeroB){

        if((numeroA.getSing() != numeroB.getSing()) && (numeroA.getExpoBit() == numeroB.getExpoBit()) && numeroA.getPartFracBit() == numeroB.getPartFracBit()){

            return true;
        }else{
            return false;
        }
    }

    int alu::minimo(int t1, int t2){

       if (t1 < t2){
           return t1;
       } else {
           return t2;
       }
    }

    //Acarreo Suma
    bool alu::acarreo(bool a, bool b, bool& c){
        bool sum = (a ^ b) ^ c;
        c = (a && b) || (a && c) || (b && c);
        return sum;
    }
    //metodos nuevos
         //Multiplicacion
         std::bitset<48> alu::productoSinSigno(std::bitset<24>& a, const std::bitset<24>& b, bool &c){

             std::bitset<24> P;
             std::bitset<48> result;
             for ( int i = 0; i<24;i++){
                 if(a[0]) c = sumaAuxiliar(P, b);
                 a >>= 1;
                 a[23] = P[0];
                 P >>= 1;
                 P[23] = c;
                 c >>= 1;

             }

             for(int i = 0; i<24; i++){
                 result[i]=a[i];
                 result[i+24]= P[i];
             }
             return result;      //sobran los 2 primeros
         }

    // diversas sumas

    bool alu::sumaAuxiliar(std::bitset<48>& a, const std::bitset<48>& b){
        bool c = false;
        for (int i = 0; i < 24; i++){
            a[i] = acarreo(a[i], b[i], c);
        }
        return c;
    }


    bool alu::sumaAuxiliar(std::bitset<24>& a, const std::bitset<24>& b){
        bool c = false;
        for (int i = 0; i < 24; i++){
            a[i] = acarreo(a[i], b[i], c);
        }
        return c;
    }

    bool alu::compruebaCero(numero numeroA, numero numeroB){

        return (numeroA.getNum() == 0 && numeroB.getNum() == 0);
    }
