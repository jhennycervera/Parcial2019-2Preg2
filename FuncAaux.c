/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <stdio.h>
#include <stdlib.h>
#define MAX_LIN 80
#define MAX_BARRA 50
#include "FuncAaux.h"

void ProcesarPersonas(int*dni,int *tel,int*carga,int*cantPer){
    FILE*archPer;
    archPer=fopen("personas.txt","r");
    if(archPer==NULL){
        printf("ERROR: No se pudo abrir el archivo personas.txt\n");
        exit (1);
    }
    
    *cantPer=0;
    int dniA, telA, cargoA;
    while(1){
        fscanf(archPer,"%d %d %d", &dniA, &telA, &cargoA);
        if(feof(archPer)) break;
        dni[*cantPer]=dniA;
        tel[*cantPer]=telA;
        carga[*cantPer]=cargoA;
        (*cantPer)++; //ponerle parentesis siempre
    }
    
    fclose(archPer);
}


void ProcesarRiesgoFinan(int* dni,int cantPer,int *riesgo){
    
    FILE*archRiesgo;
    archRiesgo=fopen("riesgoFinanciero.txt","r");
    if(archRiesgo==NULL){
        printf("ERROR: No se pudo abrir el archivo riesgoFinanciero.txt\n");
        exit(1);
    }
    int dniA, riesg, pos;
    while(1){
      fscanf(archRiesgo,"%d %d", &dniA, &riesg);
      if(feof(archRiesgo)) break;
      pos=BuscarPer(dniA,dni, cantPer);
      if(pos!=-1){
          riesgo[pos]=riesg;
      }  
    }
    fclose(archRiesgo);
}   
    
int BuscarPer(int dniA,int *dni,int cantPer){
    
    for(int i=0; i<cantPer; i++){
        if(dniA==dni[i]) return i;
    }
    return -1;
}

void AcumularIngresos(int *dni,int fecha,int fechaLim,int cantPer,double* sumIngresos){
    FILE*archRiesgo;
    archRiesgo=fopen("registroIngresos.txt","r");
    if(archRiesgo==NULL){
        printf("ERROR: No se pudo abrir el archivo registroIngresos.txt\n");
        exit(1);
    }
    int dniA, dd, mm, aa, fechaA, pos;
    double ingre;
    while(1){
        fscanf(archRiesgo,"%d %lf %d/%d/%d",&dniA,&ingre, &dd,&mm, &aa );
        if(feof(archRiesgo)) break;
        fechaA=dd+mm*100+aa*10000;
        if(fechaA>fechaLim && fechaA<fecha){
            pos=BuscarPer(dniA,dni,cantPer);
            if(pos!=-1) sumIngresos[pos]+=ingre;
        }
    }
    fclose(archRiesgo);
    
}

void CalcularLineaCred(int *dni, int*carga,int cantPer,double* sumIngresos,
                           double*  LinCredA,double*LinCredB,int *riesgo){
    
    double f1A, f1B, f2A, f2B;
    for(int i=0; i<cantPer;i++){
        f1A=Calcf1A(carga[i]);
        f2A=Calcf2A(riesgo[i]);
        f1B=Calcf1B(carga[i]);
        f2B=Calcf2B(riesgo[i]);
        LinCredA[i]=(4*sumIngresos[i])/14 * (f1A/(double)3) * f2A;
        LinCredB[i]=(4*sumIngresos[i])/14 * (f1B/(double)3) * f2B;
    }
}

double Calcf1A(int carga){
    switch(carga){
        
            case 0: 
                return 3.0;
                break;
            case 1:  
                return 2.5;
                break;
            case 2: 
                return 2.0;
                break;
            case 3: 
                return 1.5;
                break;
           default :
                  return 1.0;
                  break;
    }               
}

double Calcf2A(int riesgo){
    if(riesgo>=1 && riesgo<=4) return 1.0;
    else if(riesgo>=5) return 0.1;
}

double Calcf1B(int carga){
    if(carga==0) return 4.0;
    else return 1.0;
}

double Calcf2B(int riesgo){
    if(riesgo>=1 && riesgo<=2) return 1.0;
    if(riesgo>=3 && riesgo<=4) return 0.6;
    if(riesgo>=5 && riesgo<= 6) return 0.2;
    else return 0.1;
}

void ImprimirRep1(int *dni,int* tel,double *LinCredA, double *LinCredB, int dd,
                        int mm,int aa, int cantPer){
    FILE*archRep1;
    archRep1=fopen("Rep1.txt","w");
    if(archRep1==NULL){
        printf("ERROR: No se pudo abrir el archivo Rep1.txt\n");
        exit(1);
    }
    fprintf(archRep1, "LINEA DE CREDITO\n");
    fprintf(archRep1, "Fecha de Referencia: %02d/%02d/%02d\n",dd, mm, aa);
    ImprLin(archRep1,MAX_LIN, '=');
    fprintf(archRep1, "DNI        Telefono        Banco A          Banco B\n");
    ImprLin(archRep1,MAX_LIN, '=');
    
    for(int i=0; i<cantPer; i++){
        fprintf(archRep1, "%08d %10d %13.2lf %13.2lf\n", dni[i], tel[i], LinCredA[i], LinCredB[i]);
    }
    
    fclose(archRep1);
}

void  ImprLin(FILE*archRep1,int cant,char c){
    for(int i=0; i<cant; i++){
        fprintf(archRep1, "%c", c);
    }
    fprintf(archRep1, "\n");
}

 void  ImprimirRep2(int dd, int mm, int aa,double *LinCredA,double *LinCredB,int cantPer ){
        
    FILE*archRep2;
    archRep2=fopen("Rep2.txt","w");
    if(archRep2==NULL){
        printf("ERROR: No se pudo abrir el archivo Rep2.txt\n");
        exit(1);
    }
    fprintf(archRep2,"               DISTRIBUCION DE FRECUENCIAS\n");
    fprintf(archRep2,"             LINEAS DE CREDITO SEGUN LOS BANCOS\n");
    fprintf(archRep2,"\n");
    fprintf(archRep2,"Fecha de referencia: %02d/%02d/%02d\n", dd, mm, aa);
    ImprLin(archRep2,MAX_LIN, '=');
    
    int indA, indB, cantRangA[1000]={0},cantRangB[1000]={0}, cantMaxA=0,cantMaxB=0, cantCarA, cantCarB;
    //calculando indice y llenando numPersonas de acuerdo al indice 
    for(int i=0; i<cantPer; i++){
        indA=(int)LinCredA[i]/50;
        indB=(int)LinCredB[i]/50;
        if(indA>20) cantRangA[20]++; //solo se acumulan en 20 rangos, pues mayor de 100 000 a inf es el ultimo
        if(indB>20) cantRangB[20]++; 
        else{
            cantRangA[indA]++;
            cantRangB[indB]++;
        }
    }
    
    //hallando la cantmax de personas en los rangos
    for(int i=0; i<20; i++){
        if(cantRangA[i]>cantMaxA){
            cantMaxA=cantRangA[i];
        }
        if(cantRangB[i]>cantMaxB) cantMaxB=cantRangB[i];
    }
    
    for(int i=0; i<20; i++){
        //regla de tres para calcular la cant de caracteres que representa el cantPer en el rango 
        cantCarA=cantRangA[i]*MAX_BARRA/cantMaxA;
        cantCarB=cantRangB[i]*MAX_BARRA/cantMaxB;
        
        fprintf(archRep2,"%6d     |",(i+1)*50 );
        ImprLin(archRep2,cantCarA, '#');
        fprintf(archRep2,"%11c|",' ');
        ImprLin(archRep2,cantCarB, '&');
    }
    ImprLin(archRep2,MAX_LIN, '=');
    fprintf(archRep2, "Leyenda\n");
    fprintf(archRep2, "####: Corresponde al banco A\n");
    fprintf(archRep2, "&&&&: Corresponde al banco B\n");
    fclose(archRep2);
    }