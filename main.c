/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Jhenny Cervera Vargas(20182841)
 *
 * Created on 2 de mayo de 2020, 19:43
 */

#include <stdio.h>
#include <stdlib.h>
#include "FuncAaux.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    
    int dd, mm, aa, mm1, dd1,aa1, fecha, fechaLim;
    scanf("%d %d %d", &dd, &mm, &aa);
    if(mm<6){
        mm1=12-(abs(dd-6))+1;
        aa1=aa-1;
    }
    if (mm==6){
        mm1==12;
        aa1=aa-1;
    }
    else{
        mm1=mm-6;
    }
    dd1=dd;      
    aa1=aa;
    fecha=mm*100+ dd + aa*10000;
    fechaLim=mm1*100 + dd1+ aa1*10000;
    int dni[1000],tel[1000], riesgo[1000],carga[1000], cantPer;
    double sumIngresos[1000]={0}, LinCredA[1000], LinCredB[1000];
    
    ProcesarPersonas(dni,tel,carga,&cantPer);
    ProcesarRiesgoFinan(dni,cantPer, riesgo);
    AcumularIngresos(dni,fecha,fechaLim,cantPer,sumIngresos);
    CalcularLineaCred(dni, carga, cantPer, sumIngresos, LinCredA, LinCredB,riesgo);
    ImprimirRep1(dni,tel,LinCredA, LinCredB, dd, mm, aa, cantPer);
    ImprimirRep2(dd, mm, aa,LinCredA,LinCredB,cantPer );
    
    return (EXIT_SUCCESS);
}

