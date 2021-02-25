#ifndef VERIFICAARCHIVOS_H_INCLUDED
#define VERIFICAARCHIVOS_H_INCLUDED
#endif // VERIFICAARCHIVOS_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
void verificarArchivos(void){
    FILE * vp, *pp, *sp;
    if((vp=fopen("Vendedor.dat", "ab"))==NULL){
        printf("\n Error en la apertura del archivo . Programa abortado (1)\n");
        exit (1);
    }
    else{
            fflush(stdin);
        printf("\n El archivo Vendedor .dat existe y/o se ha creado correctamente\n\n");
        fclose(vp);
    }
        if((pp= fopen("Polizas.dat", "ab"))==NULL){
        printf("\n Error en la apertura del archivo . Programa abortado(2)\n\n");
        exit (2);
    }
    else{
             fflush(stdin);
        printf("\n El archivo Poliza.dat existe y/o se ha creado correctamente \n\n");
        fclose(pp);
    }
        if((sp= fopen("Siniestros.dat", "ab"))==NULL){
        printf("\n Error en la apertura del archivo . Programa abortado(3)\n\n");
        exit (3);
    }
    else{
         fflush(stdin);
        printf("\n El archivo Siniestros.dat existe y/o se ha creado correctamente \n\n");
        fclose(sp);
        printf("\n----------------------------------------------------------------\n");
    }
}




