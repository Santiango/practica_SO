#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "psinfo.h"

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        infoError(1);
    }

    if (argc == 2)
    {

        FILE *arch = abrirArchivo(argv[1]);

        imprimirInformacion(arch, stdout);
        fclose(arch);
    }

    if (argc > 2)
    {

        if (strcmp(argv[1], "-l") == 0)
        {
            guardarInformacion(argc - 2, &argv[2]);
        }
        else
        {

            if (strcmp(argv[1], "-r") == 0)
            {

                escribirFile(argc - 2, &argv[2]);
            }
            else
            {
                infoError(3);
            }
        }
    }
    exit(0);
}
