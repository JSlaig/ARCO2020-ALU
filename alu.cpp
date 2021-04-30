#include "alu.h"

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
        numero resultado; // Aqui se almacenara el resultado d la suma


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

        int exponente_Suma = 0;

        int i = 0;
        /*Paso 1*/
        int g = 0, r = 0, st = 0;
        int n = 24;
        bool Ope_Inter = false;
        bool Comple_P  = false;
        int d;
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
        /*Paso 6*/

        if(d-1 < 24 && d-1 >= 0){
            g=P[d-1];
        }
        if(d-2 < 24 && d-2 >= 0){
            g=P[d-2];
        }
        if(d-3 < 24 && d-3 >= 0){
            for(i=d;i<P.size()-3;i++){
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
        /*Paso 8*/

        /*Paso 9*/

        /*Paso 10*/

        /*Paso 11*/

        /*Paso 12*/

        /*Paso 13*/
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
        int indice = p.size()-1;
        p = p >>d;
        for (int i = 0; i < d;i++){
            p[indice-i] = bit;
        }
        return p;

    }

    std::bitset<24> alu::desplazarIzquierda(std::bitset<24> p, int d, int bit)
    {

                p = p <<d;
                for (int i = 0; i < d;i++){
                    p[i] = bit;
                }
                return p;

    }

    int alu::calculaK(std::bitset<24> p)
    {
        int k=0;
        int contador = p.size()-1;
        while (p[contador] == 0 && contador >-1){
            k++;
            contador --;

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

    std::bitset<23> alu::normalizaMantisa(std::bitset<24> mantisa)
    {
        /*Rellenar metodo*/
        while(mantisa[23]!=1){
            desplazarIzquierda(mantisa,1,0);
        }

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


