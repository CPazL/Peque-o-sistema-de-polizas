#ifndef POLIZAS_H_INCLUDED
#define POLIZAS_H_INCLUDED

#endif // POLIZAS_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include <ctype.h>
#include "Vendedores.h"

typedef char palabra[30];
typedef char stringpat[8];

struct Poliza{
    int NroPoliza;
    int IDVendedor;
    palabra Asegurado;
    palabra Marca;
    stringpat Patente;
    float ValorAsegurado;
};
palabra apelVen;
int auxIDV=0;
/*FUNCION QUE CARGA LOS DATOS DE LAS POLIZAS*/
void CargarDatosP(FILE* fp){
    struct Poliza datosPol;
    int indice;

                 fflush(stdin);
                 printf("\n Ingrese el apellido del vendedor \n");
                 scanf("\n %s", apelVen);
                for (indice = 0; apelVen[indice] != '\0'; ++indice){
                    apelVen[indice] = toupper(apelVen[indice]);
                }
                printf("\n El apellido ingresado es: %s", apelVen);
                 auxIDV=ValidarVendedor(apelVen);
                 if(auxIDV!=-1){
                    datosPol.IDVendedor=auxIDV;
                fseek(fp,sizeof(struct Poliza), SEEK_END);

                datosPol.NroPoliza=ftell(fp)/sizeof(struct Poliza);

                    printf("\n Ingrese el asegurado\n");
                    scanf("\n %s",datosPol.Asegurado);

                    for (indice = 0; datosPol.Asegurado[indice] != '\0'; ++indice){
                            datosPol.Asegurado[indice] = toupper(datosPol.Asegurado[indice]);
                    }
                    printf("\n Ingrese la Marca\n");
                    scanf("\n %s",datosPol.Marca);
                    for (indice = 0; datosPol.Marca[indice] != '\0'; ++indice){
                            datosPol.Marca[indice] = toupper(datosPol.Marca[indice]);
                    }
                    printf("\n Ingrese la patente\n");
                    scanf("\n %s",&datosPol.Patente);
                    for (indice = 0; datosPol.Patente[indice] != '\0'; ++indice){
                            datosPol.Patente[indice] = toupper(datosPol.Patente[indice]);
                    }

                    printf("\n Ingrese el valor del asegurado\n");
                    scanf("\n %f",&datosPol.ValorAsegurado);

                fwrite(&datosPol,sizeof(struct Poliza),1,fp);

                fseek(fp,sizeof(struct Poliza)-1,SEEK_CUR);

                fread(&datosPol, sizeof(struct Poliza),1,fp);
                printf("\n\t --------------------------Datos ingresados ------------------------------------\n");
                printf("\n\n\t Numero de poliza\t ID Vendedor\t Asegurado\t Marca\t Patente\t ValorAsegurado\n");

                printf("\n\t  ? %d \t %d \t %s \t %s \t %s \t %f",datosPol.NroPoliza, datosPol.IDVendedor, datosPol.Asegurado,datosPol.Marca, datosPol.Patente, datosPol.ValorAsegurado);
                printf("\n\t----------------------------------------------------------------------------------\n");
                printf("\n\n\t Fin del ingreso de datos\n");
}
else{
    printf("\n No se encontró el apellido del vendedor");

}
}

/*VALIDA LA CARGA DE SINIESTROS SOLO A PÓLIZAS VERFICIADAS COMO EXISTENTES*/
/*SI ENCUENTRA LA POLIZA DEVUELVE 1 CASO CONTRARIO DEVUELVE -1*/
int ValidarPoliza(int NroPoliza){

    FILE *fp;
    struct Poliza P;
    int BANDERA;
        if((fp=fopen("Polizas.dat","rb"))==NULL){
                printf("\n No se pudo abrir el archivo Polizas.dat (5)\n");
                return -1;
        }
         else{
                 fflush(stdin);
           fread(&P, sizeof(struct Poliza),1,fp);

            while(!feof(fp)){

        if(NroPoliza==P.NroPoliza){
               /* printf("\n NUMERO DE POLIZA \t ID VENDEDOR \n");
                printf("\n\t %d \t\t %d \n",P.NroPoliza, P.IDVendedor);*/
                BANDERA=1;
                    }
            fread(&P, sizeof(struct Poliza),1,fp);
                }
            fclose(fp);

           if(BANDERA==1){
            return 1;
           }
           else{
            return -1;
           }
        }
}

/*MUESTRA EL CONTENIDO DEL ARCHIVO POLIZAS*/
void ListarInfoP(FILE* fp){
struct Poliza datosPol;

        if(fp!=NULL){
           printf ("\n\t\t -----------------POLIZAS---------------\n\n\n");
            rewind(fp);
            fread(&datosPol, sizeof(struct Poliza),1,fp);
            printf("\n\n\t Numero de poliza\t ID Vendedor\t Asegurado\t Marca\t Patente\t ValorAsegurado\n");

            while(!feof(fp)){
                printf("\n\t  ? %d \t\t %d \t\t%s \t\t %s\t\t %s \t\t%f",datosPol.NroPoliza, datosPol.IDVendedor, datosPol.Asegurado,datosPol.Marca, datosPol.Patente, datosPol.ValorAsegurado);
                fread(&datosPol, sizeof(struct Poliza),1,fp);
            }
            printf("\n--------------------------------------------------------\n");
        }
            printf("\n\n");
    getch();
}
/*MUESTRA TODAS LAS PÓLIZAS Y TODOS LOS SINIESTROS DE UN VENDEDOR PASADO POR PARAMETRO*/
void ListarPolizasVendedor(char ApellidoVendedor[]){
   int IDVen;
   struct Poliza P;
   FILE *p;

    IDVen=ValidarVendedor(ApellidoVendedor);
    if(IDVen==-1){
        printf("\n No existe vendedor registrado con ese ID\n");
    }
    else{

        if((p=fopen("Polizas.dat","rb"))==NULL){
            printf("\n Error no se pudo encontrar el archivo Polizas.dat (8)\n");
        }
        printf ("\n\t\t ---------------POLIZAS DEL VENDEDOR---------------\n\n\n");
        printf("\n\n\t Numero de poliza\t ID Vendedor\t Asegurado\t Marca\t Patente\t ValorAsegurado\n");
        rewind(p);
        fread(&P, sizeof(struct Poliza),1,p);

    while(!feof(p)){
                if(IDVen==P.IDVendedor){
                    printf("\n\n\t\t %d \t %d \t %s \t %s \t %s \t %f \n", P.NroPoliza,P.IDVendedor,P.Asegurado, P.Marca,P.Patente, P.ValorAsegurado);
                }
                fread(&P, sizeof(struct Poliza),1,p);
            }
        printf("\n\t\t--------------------------------------------------------\n");
        rewind(p);
        fclose(p);
    }
        getch();
}
