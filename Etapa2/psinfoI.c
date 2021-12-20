#include <string.h>
#include <stdio.h>
#include "psinfo.h"
#include <stdlib.h>


/*
Función que abre el file donde se encuentra la información del proceso
 
Recibe como parámetro el Pid del proceso
 
Retorna el File abierto
*/
FILE *abrirArchivo(char proc[])
{

    char archivo[1024];
    sprintf(archivo, "/proc/%s/status", proc);
    FILE *arch = fopen(archivo, "r");
    return arch;
}

/*
Función que imprime la información necesitada del file del status del proceso
 
Recibe como parámetro dos File:
arch: donde se encuentra la información del status del proceso
out: donde será imprimida la información del proceso
 
*/
int imprimirInformacion(FILE *arch, FILE *out)
{
    char line[1024];
    char *token, *auxiliar1;

    while (fgets(line, 1024, arch))
    {
        token = strtok(line, ":");
        auxiliar1 = strtok(NULL, "\n");
        if (strcmp(token, "Name") == 0)
        {
            fprintf(out, "Nombre del proceso: %s\n", auxiliar1);
        }
        if (strcmp(token, "State") == 0)
        {
            fprintf(out, "Estado: %s\n", auxiliar1);
        }
        if (strcmp(token, "VmSize") == 0)
        {
            fprintf(out, "Tamaño total de la memoria: %s\n", auxiliar1);
        }
        if (strcmp(token, "VmExe") == 0)
        {
            fprintf(out, "\tTamaño total de la memoria de la región TEXT: %s\n", auxiliar1);
        }
        if (strcmp(token, "VmData") == 0)
        {
            fprintf(out, "\tTamaño de la memoria de la región DATA: %s\n", auxiliar1);
        }
        if (strcmp(token, "VmStk") == 0)
        {
            fprintf(out, "\tTamaño total de la memoria de la región STACK: %s\n", auxiliar1);
        }
        if (strcmp(token, "voluntary_ctxt_switches") == 0)
        {
            fprintf(out, "Número de cambios de contexto realizados (voluntarios - no voluntarios): %s", auxiliar1);
        }
        if (strcmp(token, "nonvoluntary_ctxt_switches") == 0)
        {
            fprintf(out, " - %s\n", auxiliar1);
        }
    }

    return 0;
}

/*
Función que crea en la memoria dinámica una estructura con la información referente al status de cada proceso y imprime la información
Recibe como parámetro un int y un arreglo de apuntadores de tipo char:
nProc: número de procesos a consultar
proc[]: array con las direcciones de los pid de cada proceso
*/

int guardarInformacion(int nProc, char *proc[])
{
    fprintf(stdout, "Información recolectada: \n");
    for (int i = 0; i < nProc; i++)
    {
        FILE *arch2=abrirArchivo(proc[i]);
        FILE *arch = abrirArchivo(proc[i]);
        status *s = (status *)malloc(sizeof(status));
        char line[1024];
        char *token, *auxiliar1;

        while (fgets(line, 1024, arch))
        {
            token = strtok(line, ":");
            auxiliar1 = strtok(NULL, "\n");
            if (strcmp(token, "Name") == 0)
            {
                strcpy(s->name, auxiliar1);
            }
            if (strcmp(token, "State") == 0)
            {
                strcpy(s->state, auxiliar1);
            }
            if (strcmp(token, "VmSize") == 0)
            {
                strcpy(s->vmSize, auxiliar1);
            }
            if (strcmp(token, "VmExe") == 0)
            {
                strcpy(s->vmExe, auxiliar1);
            }
            if (strcmp(token, "VmData") == 0)
            {
                strcpy(s->vmData, auxiliar1);
            }
            if (strcmp(token, "VmStk") == 0)
            {
                strcpy(s->vmStk, auxiliar1);
            }
            if (strcmp(token, "voluntary_ctxt_switches") == 0)
            {
                strcpy(s->voluswit, auxiliar1);
            }
            if (strcmp(token, "nonvoluntary_ctxt_switches") == 0)
            {
                strcpy(s->nonvoluswit, auxiliar1);
            }
        }
        free(s);
        imprimirInformacion(arch2,stdout);
        fprintf(stdout,"-------------------------------------------------------------------------\n");
        fclose(arch);
        fclose(arch2);
    }

    return 0;
}
