#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "LinkedList.h"
#include "Controller.h"
#include "peliculas.h"
#include "utn.h"

/** \brief Menu de opciones
 *
 * \return int La opcion elegida por el usuario
 *
 */
int controller_principalMain()
{
    system("cls");

    printf(">> Menu de Opciones\n");
    printf("\n1_ Cargar desde el archivo(CVS).");
    printf("\n2_ Listar.");
    printf("\n3_ Depurar");
    printf("\n4_ Filtrar");
    printf("\n5_ Salir");

    fflush(stdin);
    return getInt("\n\nIngrese opcion: ");
}

/** \brief Menu de opciones a filtro por escoger
 *
 * \return int La opcion elegida por el usuario
 *
 */
int controller_filterMain()
{
    system("cls");

    printf(">> Menu de Filtros\n");
    printf("\n1_ Precios Altos");
    printf("\n2_ Precios Bajos");
    printf("\n3_ Volver al Menu Principal");

    fflush(stdin);
    return getInt("\n\nIngrese opcion: ");
}
/** \brief Carga los datos desde el archivo (modo texto).
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int retorna la funcion (1 - TodoOK // 0 - Error)
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayList)
{
    FILE* pArchivo = fopen(path, "r"); //Variable puntero al archivo
    system("cls");
    int flag = 0;

    printf(">> Cargar Modo Texto\n\n");
    if(pArchivo != NULL && pArrayList != NULL)  //Verifico si la lectura del archivo, si no retorna NULL accedo al parse
        flag = parser_FromText(pArchivo, pArrayList);
        if (flag)
            printf("\nArchivo Cargado con Exito\n\n");
    else
        printf("\nArchivo No Encontrado\n\n");
    return flag;
}

int controller_List(LinkedList* pArrayList)
{
    system("cls");
    printf(">> Datos\n\n");
    printf("  ID |  PELICULA  |  ANIO  | CATEGORIA/S \n\n");

    for(int i=0; i<ll_len(pArrayList); i++) //Recorro el array de datos
    {
        ePelicula* this = (ePelicula*)ll_get(pArrayList, i); //Le asigno al puntero ePelicula "this" lo que retorna "ll_get()"
        _show(this); //Imprimo los datos
    }
    printf("\n\n");
    return 1;
}

int controller_saveAsText(char* path, LinkedList* pArrayList)
{
    char var_2[50], var_4[50];
    int var_1, var_3;
    FILE* text = fopen(path, "w");

    if(text != NULL && pArrayList != NULL && confirmation())
    {
        fprintf(text,"id,pelicula,anio,categoria/s\n");
        for(int i=0; i<ll_len(pArrayList); i++)
        {
            ePelicula* this = (ePelicula*) ll_get(pArrayList, i);
            if (_getters(this, &var_1, var_2, &var_3, var_4))
                fprintf(text, "%d,%s,%d,%s\n", var_1, var_2, var_3, var_4);
        }
        return 1;
    }
    fclose(text);
    return 0;
}

/** \brief Guarda los datos en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayList)
{
    FILE* pArchivo = fopen(path, "wb");; //Puntero al archivo, abro el archivo en modo escritura binaria
    int flag = 0, datosLeidos;

    if(pArchivo != NULL && pArrayList != NULL) //Verifico que la apertura del archivo y el array de eEnvios no sea NULL, si no lo es ingreso
    {
        rewind(pArchivo); //Voy al inicio del archivo
        for(int i=0; i<ll_len(pArrayList); i++)
        {
            ePelicula* this = (ePelicula*)ll_get(pArrayList,i);
            datosLeidos = fwrite(this, sizeof(ePelicula), 1, pArchivo);
            flag = 1;
            if(datosLeidos != 1)
                printf("\nError al escribir los datos en el archivo.\n\n");
        }
        printf("\nDatos Guardados Con Exito\n\n");
    }

    else  //Si no pudo acceder al archivo lo informo
        printf("\nNo se pudo acceder al archivo.\n");

    fclose(pArchivo); //Cierro el archivo
    return flag;
}
