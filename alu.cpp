#include "alu.h"

    alu::alu(){
    }

    alu::alu(float numA, float numB)
    {
        /*Creacion de dos numeros Objeto*/
    numeroA = numero(numA);
    numeroB = numero(numB);

    }

    void alu::sumaIEE()
    {

        /*EJEMPLO DE USO
         * Consulta del exponente en int del numero A ->> numeroA.getExp();
         * Consulta del exponente en en binario (bitset<8>) ->> numeroA.getExpBit();
         *
         * Creacion de una variable bitset ->> std::bitset<24> nombreVar(int numeroAConvertir);
         *

        /*Rellenar*/

        /*Paso 1*/

        /*Paso 2*/

        /*Paso 3*/

        /*Paso 4*/

        /*Paso 5*/

        /*Paso 6*/

        /*Paso 7*/

        /*Paso 8*/

        /*Paso 9*/

        /*Paso 10*/

        /*Paso 11*/

        /*Paso 12*/

        /*Paso 13*/
    }

    std::bitset<24> alu::complemento2(std::bitset<24>)
    {
        /*Rellenar metodo*/
    }

    std::bitset<24> alu::desplazarDerecha(std::bitset<24> p, int d, int bit)
    {   int indice = p.size()-1;
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

    std::bitset<24> alu::sumaUno(std::bitset<24>)
    {
        /*Rellenar metodo*/

    }

    std::bitset<23> alu::normalizaMantisa(std::bitset<24> mantisa)
    {
        /*Rellenar metodo*/

    }
