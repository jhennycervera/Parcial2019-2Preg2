/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncAaux.h
 * Author: Admin
 *
 * Created on 3 de mayo de 2020, 9:56
 */

#ifndef FUNCAAUX_H
#define FUNCAAUX_H

void ProcesarPersonas(int*,int *,int*,int*);
void ProcesarRiesgoFinan(int* ,int ,int *);
int BuscarPer(int ,int *,int );
void AcumularIngresos(int *,int ,int ,int ,double*);
void CalcularLineaCred(int *, int*,int ,double* ,double*  ,double*,int *);
double Calcf1A(int );
double Calcf2A(int );
double Calcf2B(int );
double Calcf1B(int );
void ImprimirRep1(int *,int* ,double *, double *, int ,
                        int ,int , int );
void  ImprLin(FILE*,int ,char );
 void  ImprimirRep2(int , int , int ,double *,double *,int  );


#endif /* FUNCAAUX_H */

