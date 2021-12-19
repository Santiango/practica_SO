#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <errno.h>
#include "psinfo.h"

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        fprintf(stderr, "Debes especificar un id de proceso\n");
        return EXIT_FAILURE;
    }

    if (argc == 2)
    {

        FILE *arch = abrirArchivo(argv[1]);
        if (!arch)
        {
            fprintf(stderr, "Error abriendo el archivo \n");
            return EXIT_FAILURE;
        }
        else
        {
            imprimirInformacion(arch, stdout);
            fclose(arch);
        }
    }

    if (argc > 2)
    {
        if (strcmp(argv[1], "-l") == 0)
        {
            guardarInformacion(argc - 2, &argv[2]);
        }
    }
    exit(0);
}
