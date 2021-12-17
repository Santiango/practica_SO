#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <errno.h>


int imprimirInformacion(FILE *arch){
    
    char line[1024];
    char *token, *auxiliar1;
    int i = 0;
    while (fgets(line,1024,arch))
    {
        token = strtok(line,":");
        auxiliar1 = strtok(NULL,"\n");
        if(strcmp(token,"Name")==0){
            printf("Nombre del proceso: %s\n",auxiliar1);
        }
        if(strcmp(token,"State")==0){
            printf("Estado: %s\n",auxiliar1);
        }
        if(strcmp(token,"VmSize")==0){
            printf("Tamaño total de la memoria: %s\n",auxiliar1);
        }
        if(strcmp(token,"VmData")==0){
            printf("\tTamaño total de la memoria de la región TEXT: %s\n",auxiliar1);
        }
        if(strcmp(token,"vmStk")==0){
            printf("\tTamaño de la memoria de la región DATA: %s\n",auxiliar1);
        }
        if(strcmp(token,"VmExe")==0){
            printf("\tTamaño total de la memoria de la región STACK: %s\n",auxiliar1);
        }
        if(strcmp(token,"voluntary_ctxt_switches")==0){
            printf("Número de cambios de contexto realizados (voluntarios - no voluntarios): %s",auxiliar1);
        }
        if (strcmp(token, "nonvoluntary_ctxt_switches") == 0)
        {
            printf(" - %s\n",auxiliar1);
        }

        i++;
        token = memset(token,0,1024);
        auxiliar1 = memset(auxiliar1,0,1024);
    }
    return 0;
}

int imprimirEnArchivo(FILE *arch,FILE *archSalida){
    char aux[1024];
    char line[1024];
    char *token, *auxiliar1;
    int i = 0;

    while (fgets(line,1024,arch))
    {
        token = strtok(line,":");
        auxiliar1 = strtok(NULL,"\n");
        if(strcmp(token,"Name")==0){
            sprintf(aux,"Nombre del proceso: %s\n",auxiliar1);
            fputs(aux,archSalida);
        }
        if(strcmp(token,"State")==0){
            sprintf(aux,"Estado: %s\n",auxiliar1);
            fputs(aux,archSalida);
        }
        if(strcmp(token,"VmSize")==0){
            sprintf(aux,"Tamaño total de la memoria: %s\n",auxiliar1);
            fputs(aux,archSalida);
        }
        if(strcmp(token,"VmData")==0){
            sprintf(aux,"\tTamaño total de la memoria de la región TEXT: %s\n",auxiliar1);
            fputs(aux,archSalida);
        }
        if(strcmp(token,"vmStk")==0){
            sprintf(aux,"\tTamaño total de la memoria de la región DATA: %s\n",auxiliar1);
            fputs(aux,archSalida);
        }
        if(strcmp(token,"VmExe")==0){
            sprintf(aux,"\tTamaño total de la memoria de la región STACK: %s\n",auxiliar1);
            fputs(aux,archSalida);
        }
        if(strcmp(token,"voluntary_ctxt_switches")==0){
            sprintf(aux,"Número de cambios de contexto realizados (voluntarios - no voluntarios): %s",auxiliar1);
            fputs(aux,archSalida);
        }
        if (strcmp(token, "nonvoluntary_ctxt_switches") == 0)
        {
            sprintf(aux," - %s\n",auxiliar1);
            fputs(aux,archSalida);
        }

        i++;
        token = memset(token,0,1024);
        auxiliar1 = memset(auxiliar1,0,1024);
    }
    return 0;
}
int main(int argc, char*argv[]){


    if(argc < 2){
        fprintf(stderr,"Debes especificar un id de proceso\n");
        return EXIT_FAILURE;
    }
    
    
    if(argc==2){
        char archivo[1024];
        sprintf(archivo,"/proc/%s/status",argv[1]);
        FILE *arch = fopen(archivo,"r");
        if(arch == NULL){
            fprintf(stderr,"Error abriendo el archivo %s\n",archivo);
            return EXIT_FAILURE;
        }
        imprimirInformacion(arch);
        fclose(arch);
    }

    if(argc > 2){
        if(strcmp(argv[1],"-l")==0){
            for(int i = 2; i < argc; i++){
                char archivo[1024];
                sprintf(archivo,"/proc/%s/status",argv[i]);
                FILE *arch = fopen(archivo,"r");
                if(arch == NULL){
                    fprintf(stderr,"Error abriendo el archivo %s\n",archivo);
                    return EXIT_FAILURE;
                }
                
                imprimirInformacion(arch);
                fclose(arch);
            }  
        } 
        
        if(strcmp(argv[1],"-r")==0){
            char archSal[1024];
            strcat(archSal, "psinfo-report");
            for(int i = 2; i < argc; i++){
                char aux[10];
                sprintf(aux, "-%s", argv[i]);
                strcat(archSal, aux);
            }
            strcat(archSal, ".info");
            for(int i = 2; i < argc; i++){
                printf("Archivo de salida generado: %s\n",archSal);
                char archivo[1024];
                sprintf(archivo,"/proc/%s/status",argv[i]);
                FILE *arch = fopen(archivo,"r");
                FILE *salida = fopen(archSal,"w+");
                if(arch == NULL){
                    fprintf(stderr,"Error abriendo el archivo %s\n",archivo);
                    return EXIT_FAILURE;
                }
                
                imprimirEnArchivo(arch,salida);
                fclose(arch);
                fclose(salida);
            }  
        } 
    }
    exit(0);
}





