#ifndef INICIO_H_INCLUDED
#define INICIO_H_INCLUDED
#endif // INICIO_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include "funciones.h"


void inicio(void){
int opcion=0, opcionV=0, opcionP=0,opcionS=0, IDV=0,auxID=0, NroP=0, indice;
FILE * vp, *pp, *sp;
palabra apeVen;
float SumS=0.0;
    printf("\n\n\n\t------------------INICIO-----------------\n");
    printf("\n\t\t Ingrese la opcion a ejecutar\n");
    printf("\n\t\t 1. Vendedores \n");
    printf("\n\t\t 2. Polizas \n");
    printf("\n\t\t 3. Siniestros \n");
    printf("\n\t\t 4. Fin del programa \n");

    scanf("%d",&opcion);
    system("cls");

    switch (opcion){
        case 1:
                printf("\n\t\t ---------------VENDEDORES----------------\n\n\n");
                printf("\n\t\t 1. Mostrar la lista de vendedores \n");
                printf("\n\t\t 2. Agregar vendedor nuevo \n");
                printf("\n\t\t 3. Verificar la existencia de un vendedor\n");
                printf("\n\t\t 4. Mostrar vendedores a premiar\n");
                printf("\n\t\t 5. Volver el inicio  \n");

                scanf("%d",&opcionV);
                switch(opcionV){
                    case 1: system("cls");
                            printf("\n Lista de vendedores\n");
                            vp= fopen("Vendedor.dat", "rb");
                            ListarInfoV(vp);
                            fclose(vp);
                            system("pause");
                            system("cls");
                            inicio();

                            break;
                    case 2: system("cls");
                            vp= fopen("Vendedor.dat", "ab");
                            CargarDatosV(vp);
                            fclose(vp);
                            system("pause");
                            system("cls");
                            inicio();
                            break;

                    case 3: system("cls");
                            printf("\n Ingrese el apellido del vendedor\n");
                            scanf("%s",&apeVen);

                            for (indice = 0; apeVen[indice] != '\0'; ++indice){
                                apeVen[indice] = toupper(apeVen[indice]);
                                }
                            auxID=ValidarVendedor(apeVen);
                            if(auxID== -1){
                                printf("\n\t El vendedor no existe\n");
                            }
                            else{
                                printf("\n El número de ID del Vendedor es: %d \n",auxID);
                                }
                            system("pause");
                            system("cls");
                            inicio();
                            break;

                    case 4: system("cls");

                            VendedorAPremiar();
                            system("pause");
                            system("cls");
                            inicio();
                            break;
                    case 5: system("cls");

                            break;
                    default: system("cls");
                            inicio();
                            break;
                }
                break;
         case 2:{
               printf("\n\t\t ----------------POLIZAS---------------\n\n\n");

                printf("\n\t\t 1. Mostrar la lista de polizas \n");
                printf("\n\t\t 2. Agregar una poliza nueva \n");
                printf("\n\t\t 3. Mostrar polizas ingresando apellido de vendedor \n");
                printf("\n\t\t 4. Volver al men%c \n",163);
                scanf("%d",&opcionP);
                switch(opcionP){
                    case 1: /*Lista de polizas*/
                            system("cls");
                            printf("\n Lista de polizas\n");
                            pp= fopen("Polizas.dat", "rb");
                            ListarInfoP(pp);
                            fclose(pp);
                            system("pause");
                            system("cls");

                            inicio();
                            break;
                    case 2: /*Carga de datos*/
                            pp= fopen("Polizas.dat", "ab");
                            CargarDatosP(pp);
                            fclose(pp);
                            printf("\n \n \n");
                            system("pause");
                            system("cls");
                            inicio();
                            break;
                    case 3:
                        printf("\n\nIngrese el apellido del vendedor\n");
                        scanf("%s",&apeVen);
                        for (indice = 0; apeVen[indice] != '\0'; ++indice){
                            apeVen[indice] = toupper(apeVen[indice]);
                        }
                            if(ValidarVendedor(apeVen)==-1){
                                printf("\n\n El vendedor ingresado es incorrecto \n");
                            }
                            else{
                                ListarPolizasVendedor(apeVen);}
                            printf("\n \n \n");
                            system("pause");
                            system("cls");
                            inicio();
                        break;

                    default: inicio();
                            break;
                }}
                break;
        case 3:
                printf ("\n\t\t ----------------SINIESTROS---------------\n\n\n");
                printf("\n\t\t 1. Mostrar la lista de siniestros\n");
                printf("\n\t\t 2. Agregar siniestro nuevo \n");
                printf("\n\t\t 3. Asegurado con mas dinero a pagar por siniestros \n");
                printf("\n\t\t 4. Siniestros por n%cmero de poliza \n",163);
                printf("\n\t\t 5. Volver al inicio \n");
                scanf("%d",&opcionS);
                system("cls");
                switch(opcionS){
                    case 1:printf("\n Lista de siniestros\n");
                            sp= fopen("Siniestros.dat", "rb");
                            ListarInfoS(sp);
                            printf("\n \n \n");
                            system("pause");
                            system("cls");
                            inicio();
                            break;
                    case 2:
                            sp= fopen("Siniestros.dat", "ab");
                            CargarDatosS(sp);
                            fclose(sp);
                            system("pause");
                            system("cls");
                            inicio();
                            break;
                    case 3: printf("\n\n Asegurado al que se le debe pagar mas dinero por siniestros\n");
                            AseguradoPiedra();
                            printf("\n \n \n");
                            system("pause");
                             printf("\n \n \n");
                            system("pause");
                            system("cls");
                            inicio();
                            break;
                    case 4: printf("\n\n ------------------ Siniestros por Poliza ------------------------- \n");
                            printf("\n\n Ingrese un numero de poliza\n");
                            scanf("\n %d", &NroP);

                                if(ValidarPoliza(NroP)==-1){
                                }
                                else{
                                    SumS=SumatoriaValorSin(NroP);
                                    printf("\n\n El total de Siniestros a pagar a la poliza %d es : %f",NroP, SumS);
                                }
                                printf("\n\n");
                                system("pause");
                                system("cls");
                                inicio();
                            break;
                    default: inicio();
                            break;
                }
                break;
        case 4:     RecorreArchivoVendedores();
                    system("cls");
                    printf("\n ********************* FIN DEL PROGRAMA********************************* \n");
                break;

        default: system("cls");
                 inicio();
                break;

}
}
