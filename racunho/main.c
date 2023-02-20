#include <stdio.h>
#include <stdlib.h>

int main(){
    int linha = 20,i=0;
    char *nome = (char*) calloc(15,sizeof(char));
    char **pos = (char**) calloc(linha,sizeof(char*));
    do{
        pos[i] = nome;
        i++;
    }while(i<linha);
    return 0;
}
