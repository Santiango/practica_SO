#ifndef __PSINFO_H_
#define __PSINFO_H_

typedef struct __status status;

struct __status
{
    char name[1024];
    char state[1024];
    char vmSize[1024];
    char vmExe[1024];
    char vmData[1024];
    char vmStk[1024];
    char voluswit[1024];
    char nonvoluswit[1024];
};

FILE* abrirArchivo(char proc[]);
int imprimirInformacion(FILE *arch,FILE *out);
int guardarInformacion(int nProc, char *proc[]);
int escribirFile(int nProc, char *proc[]);
int infoError(int e);

#endif