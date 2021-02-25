#ifndef VENDEDORES_H_INCLUDED
#define VENDEDORES_H_INCLUDED

#endif // VENDEDORES_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include <ctype.h>

typedef char palabra[30];
typedef char stringpat[8];

struct Vendedor{
    int IDVendedor;
    palabra ApellidoVendedor;
    float TasaRendimiento;
};
/*Función que valida la carga de polizas solo a vendedores verificados como existentes*/
/*Si se encuentra la poliza devuelve 1, caso contrario devuelve -1*/
int ValidarVendedor(char apellidoProductor[]){
    FILE *fp;
    struct Vendedor ven;

        if((fp=fopen("Vendedor.dat","rb"))==NULL){
            printf(" \n No se pudo abrir el archivo Vendedores.dat (4)\n");
        }
        else{
            fread(&ven, sizeof(struct Vendedor),1,fp);

            while(!feof(fp)){
                if(strcmp(apellidoProductor,ven.ApellidoVendedor)==0){
                    return ven.IDVendedor;
                    }
                fread(&ven, sizeof(struct Vendedor),1,fp);
                }
            rewind(fp);
            fclose(fp);

            return -1;
           }
}
void CargarDatosV(FILE* fp){
    struct Vendedor datosVen;
    palabra apellidov;
    int aux=0, indice;
    if(fp!=NULL){
                fflush(stdin);
                fseek(fp,sizeof(struct Vendedor), SEEK_END);

                datosVen.IDVendedor=ftell(fp)/sizeof(struct Vendedor);

                printf("\n\n\n\t\t Ingrese el apellido del vendedor\n");
                printf("\n\n\n\t\t ?");
                scanf("\t\t  %s", apellidov);
                for (indice = 0; apellidov[indice] != '\0'; ++indice){
                    apellidov[indice] = toupper(apellidov[indice]);
                }
            aux=ValidarVendedor(apellidov);

            if(aux==-1){
                strcpy(datosVen.ApellidoVendedor,apellidov);
                datosVen.TasaRendimiento=0.0;

                fwrite(&datosVen, sizeof(struct Vendedor),1,fp);

                printf("\n\t\t Se ha cargado correctamente\n");
                fseek(fp,sizeof(struct Vendedor)-1,SEEK_CUR);
                fread(&datosVen, sizeof(struct Vendedor),1,fp);

            printf("\n\t ---------------Datos ingresados ----------------\n");
            printf("\n\t ID Vendedor\t Apellido\t Tasa de Rendimiento\n");
            printf("\n\t   ? %d \t %s \t %f ", datosVen.IDVendedor, datosVen.ApellidoVendedor, datosVen.TasaRendimiento);

            printf("\n\n\t Fin de carga\n");
            printf("\n--------------------------------------------------------\n");
            }
            else{
                printf("\n El apellido de ese vendedor ya existe \n");
            }
        printf("\n\n");
}}


/*MUESTRA EL CONTENIDO DEL ARCHIVO VENDEDORES.DAT*/
void ListarInfoV(FILE* fp){

struct Vendedor datosVen;
               fflush(stdin);
        printf("\n\t\t ---------------VENDEDORES----------------\n\n\n");
        printf("\n\n\t ID Vendedor\t Apellido\t Tasa de Rendimiento\n");

        fread(&datosVen, sizeof(struct Vendedor),1,fp);

            while(!feof(fp)){
                printf("\n\t   ? %d  \t %s  \t\t\t %f ", datosVen.IDVendedor, datosVen.ApellidoVendedor, datosVen.TasaRendimiento);
                fread(&datosVen, sizeof(struct Vendedor),1,fp);
            }
            printf("\n\n");
}
/*MUESTRA LOS VENDEDORES QUE HAN TENIDO UN PORCENTAJE DE RENDIMIENTO SUPERIOR AL 5% EN LA TASA DE RENDIMIENTO*/


void VendedorAPremiar(void){
    FILE *pv;
    struct Vendedor V;
        if((pv=fopen("Vendedor.dat","rb"))==NULL){
            printf("\n\n\t No se encontro el archivo Vendedor.dat (10) \n");
        }
        else{
        rewind(pv);
        printf("\n\n\t-------------VENDEDORES PREMIADOS----------------\n");
        printf("\n\n\t ID Vendedor\t Apellido\t Tasa de Rendimiento\n");
        fread(&V, sizeof(struct Vendedor),1,pv);

        while(!feof(pv)){
            if(V.TasaRendimiento>0.05){
                printf("\n\n\t %d \t\t %s \t\t %f \n", V.IDVendedor, V.ApellidoVendedor, V.TasaRendimiento);
            }
            fread(&V, sizeof(struct Vendedor),1,pv);
        }
    fclose(pv);
    printf("\n\n\n\n");
 }
}
