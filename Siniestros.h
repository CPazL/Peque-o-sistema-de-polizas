#ifndef SINIESTROS_H_INCLUDED
#define SINIESTROS_H_INCLUDED


#endif // SINIESTROS_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include <ctype.h>
#include "Polizas.h"


struct Siniestro{
    int IDSiniestro;
    int NroPoliza;
    float ValorSiniestro;
};

void ListarInfoS(FILE* fp){
    struct Siniestro  datosSin;

        if(fp!=NULL){
        printf("\n\t\t ----------------SINIESTROS---------------\n\n\n");
            fread(&datosSin, sizeof(struct Siniestro),1,fp);
            printf("\n\n\t ID Siniestro\t N%cmero de Poliza\t Valor del siniestro\n",163);

            while(!feof(fp)){

                printf("\n\n\t %d \t\t %d \t\t %f \n", datosSin.IDSiniestro, datosSin.NroPoliza, datosSin.ValorSiniestro);
                fread(&datosSin, sizeof(struct Siniestro),1,fp);
            }
            printf("\n--------------------------------------------------------\n");
        rewind(fp);

        }
}
void CargarDatosS(FILE* fp){
    struct Siniestro datosSin;

                if(fp!=NULL){

                    printf("\n ----------------INGRESO DE SINIESTRO--------------\n");

                    fseek(fp,sizeof(struct Siniestro), SEEK_END);
                    datosSin.IDSiniestro=ftell(fp)/sizeof(struct Siniestro);
                    printf("\n Id de sisniestro asignado\n",datosSin.IDSiniestro);
                    printf("\n\t Ingrese el numero de poliza\n");
                    scanf("\n\t %d", &datosSin.NroPoliza);

                    if(ValidarPoliza(datosSin.NroPoliza)==-1){
                        printf("\n La poliza ingresada no es correcta");
                    }
                    else{
                        printf("\n\t Ingrese el valor del siniestro \n ");
                        scanf("\n\t %f", &datosSin.ValorSiniestro);

                        fwrite(&datosSin, sizeof(struct Siniestro),1,fp);
                        printf("\n\n Se ha cargado correctamente el siniestro \n");

                        fseek(fp,sizeof(struct Siniestro)-1,SEEK_CUR);
                        fread(&datosSin, sizeof(struct Siniestro),1,fp);

                        printf("\n----------------------Datos de Siniestro ingresado----------------------------------\n");
                        printf("\n\n\t ID Siniestro\t N%cmero de Poliza\t Valor del siniestro\n",163);
                        printf("\n\n\t %d \t\t %d \t\t %f \n", datosSin.IDSiniestro, datosSin.NroPoliza, datosSin.ValorSiniestro);

                        printf("\n--------------------------------------------------------\n");
                    }
        }
        else{
            printf("\n\t Error, no se ha encontrado el archivo\n");
        }
    }
/*Sumatoria de todos los Siniestros de una poliza recibida*/
float SumatoriaValorSin(int NroPoliza){
    FILE *sp;
    struct Siniestro S;
    float Acumulador = 0.0;

    if((sp= fopen("Siniestros.dat", "rb"))==NULL){
        printf("\n Error en la apertura del archivo . Programa abortado\n");
    }
    else{
            rewind(sp);
            fread(&S, sizeof(struct Siniestro),1,sp);
            while(!feof(sp)){
                if(S.NroPoliza==NroPoliza){
                        Acumulador=Acumulador+S.ValorSiniestro;
                }
            fread(&S, sizeof(struct Siniestro),1,sp);
            }
            fclose(sp);
            return Acumulador;
        }
    printf("\n\n");
}

/*MUESTRA TODA LA INFORMACIÓN DISPONIBLE DEL ASEGURAO AL QUE MÁS DINERO SE LE DEBIÓ PAGAR POR SINIESTROS DURANTE
EL EJERCICIO ANUAL*/
void AseguradoPiedra(void){
    FILE *PP;
    struct Poliza p, MAseg;
    float mayorPago=0.0, PagoAsegurado=0.0;

        if((PP=fopen("Polizas.dat","rb"))==NULL){
            printf("\n\n\t No se encontro el archivo Polizas.dat (10) \n");
        }
        else{
        fread(&p,sizeof(struct Poliza),1,PP);
        PagoAsegurado=SumatoriaValorSin(p.NroPoliza);

            while(!feof(PP)){
                if(PagoAsegurado>mayorPago){
                    MAseg=p;
                    mayorPago=PagoAsegurado;
                }
                fread(&p, sizeof(struct Poliza),1,PP);
                PagoAsegurado=SumatoriaValorSin(p.NroPoliza);
            }

        printf("\n\n\t Numero de poliza\t ID Vendedor\t Asegurado\t Marca\t Patente\t ValorAsegurado\n");
        printf("\n\n\t %s \t %d \t %d \t %s \t %s \n\n", MAseg.Asegurado,MAseg.NroPoliza, MAseg.IDVendedor,MAseg.Marca, MAseg.Patente);
        printf("\n Total pagado: %f \n", mayorPago);
        printf("\n--------------------------------------------------------------------------------\n");
        fclose(PP);
        }
}

/*FUNCION QUE CALCULA LOS PORCENTAJES DE RENDIMIENTOS DE LAS POLIZAS VENDIDAS POR CADA PRODUCTOR ANTES DE INFORMAR
SE DEBE TRABAJR CON LOS 3 ARCHIVOS ABIERTOS Y ENTRECRUZAR LOS DATOS*/
float CalcularTasaRendimiento(int IDVendedor){
       FILE *pp;
       struct Poliza P;
       float SumPoli=0.0, SumSinies=0.0, tasa_rendimiento=0.0, Total_CapAsegurado=0;

    if((pp= fopen("Polizas.dat", "rb"))==NULL){
        printf("\n Error en la apertura del archivo . Programa abortado(6)\n");
        exit (2);
    }
    else{
        fread(&P, sizeof(struct Poliza),1,pp);
        while(!feof(pp)){
            if(P.IDVendedor==IDVendedor){
                        SumPoli= SumPoli+P.ValorAsegurado;
                        SumSinies= SumSinies+SumatoriaValorSin(P.NroPoliza);
                        }
            Total_CapAsegurado = Total_CapAsegurado+P.ValorAsegurado;
            fread(&P, sizeof(struct Poliza),1,pp);
        }
            tasa_rendimiento=((SumPoli-SumSinies)*100)/Total_CapAsegurado;
            fclose(pp);
            return tasa_rendimiento;
        }
}
/*FUNCION AUXILIAR: RECORRE CADA ESTRUCTURA*/
void EscribeArchivoModificar( struct Vendedor x){
   FILE* ep;
    struct Vendedor aux;
    int pos=0, indice;
    if((ep=fopen("Vendedor.dat","rb+"))==NULL){
        printf("\n No se pudo abrir el archivo Vendedor.dat (15)");
    }
    else{
            rewind(ep);
            if(!feof(ep)){
                aux.IDVendedor= x.IDVendedor;
                for (indice = 0; aux.ApellidoVendedor[indice] != '\0'; ++indice){
                        aux.ApellidoVendedor[indice] = toupper(aux.ApellidoVendedor[indice]);
                }

                strcpy(aux.ApellidoVendedor,x.ApellidoVendedor);

                aux.TasaRendimiento= CalcularTasaRendimiento(x.IDVendedor);
                pos= ((x.IDVendedor)-1)*sizeof(struct Vendedor);

                fseek(ep,pos,SEEK_SET);
                fwrite(&aux,sizeof(struct Vendedor),1,ep);

            printf("\n Se modificó correctamente la estructura %d", x.IDVendedor );
        }
    }
    fclose(ep);
}
/*FUNCION QUE RECORRE EL ARCHIVO PARA OBTENER EL ID QUE LUEGO SERÁ USADO EN LA FUNCIÓN ESCRIE ARCHIVO*/
void RecorreArchivoVendedores(void){
   FILE* rp;
    struct Vendedor Ven;

    if((rp=fopen("Vendedor.dat","rb+"))==NULL){
        printf("\n No se pudo abrir el archivo Vendedor.dat(16)");
    }
    else{
            /*Luego de abierto el flujo se posicióna al comienzo del archivo*/
        rewind(rp);
        fread(&Ven,sizeof(struct Vendedor),1, rp);

        while(!feof(rp)){

           EscribeArchivoModificar(Ven);
            printf("\n Paso por la estructura %d", Ven.IDVendedor);
            fread(&Ven, sizeof(struct Vendedor),1,rp);
        }}
    printf("\n\n");
    fclose(rp);
}

