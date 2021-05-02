#include "alu.h"
#include<iostream>

    alu::alu(){
    }

    alu::alu(float numA, float numB)
    {
        /*Creacion de dos numeros Objeto*/
    numeroA = numero(numA);
    numeroB = numero(numB);

    }

    numero alu::sumaIEE()
    {
      // Aqui se almacenara el resultado d la suma


        /*EJEMPLO DE USO
         * Consulta del exponente en int del numero A ->> numeroA.getExp();
         * Consulta del exponente en en binario (bitset<8>) ->> numeroA.getExpBit();
         *
         * Creacion de una variable bitset ->> std::bitset<24> nombreVar(int numeroAConvertir);
         */

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
        /*Paso 5*/
        P=mantisaB;
         std::cout <<  "MantisaB ->"<<P.to_string() <<std::endl;

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

        /*Paso 7*/
        if(signoA!=signoB){
            P = desplazarDerecha(P,d,1);
        }else{
            P = desplazarDerecha(P,d,0);
        }

        /*Paso 8 [Bien]*/
        std::cout << "paso 8, mantisaA-> " << mantisaA.to_string() << std::endl;
        std::cout << "paso 8, antes p-> " << P.to_string() << std::endl;

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

        /*Paso 13*/
        //Suma = (SignoSuma) * MantisaSuma * 2Exp
        QString suma;

        suma.append(signoSuma);//append(exponente_Suma); //append(QString::fromStdString(normalizaMantisa(mantisaSuma).to_string()));

        std::cout << suma.toStdString() <<std::endl;

        std::cout << "Exponente -> " << exponente_Suma <<std::endl;
        std::cout << signoSuma <<std::endl;



        std::cout << mantisaToPartFrac(mantisaSuma) <<std::endl;

        /********************************************/

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

        for(int i = 0; i < d; i++){
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

    int alu::calculaK(std::bitset<24> p)
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

    QString alu::returnNum1(char s){

        switch(s){

        case 's': return QString::number(numeroA.getSing());
            break;
        case 'e': return QString::fromStdString(numeroA.getExpoBit().to_string());
            break;
        case 'f': return QString::fromStdString(numeroA.getPartFracBit().to_string());
            break;
        }
    }

    QString alu::returnNum2(char s){

        switch(s){

        case 's': return QString::number(numeroB.getSing());
            break;
        case 'e': return QString::fromStdString(numeroB.getExpoBit().to_string());
            break;
        case 'f': return QString::fromStdString(numeroB.getPartFracBit().to_string());
            break;
        }
    }

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



