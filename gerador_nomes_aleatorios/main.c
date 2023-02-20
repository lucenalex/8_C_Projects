#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fp;
    char string[100], c;
    int i;
    fp = fopen("exemplo.txt","r");
    if(fp == NULL){
        printf("Erro na abertura do arquivo");
        system("pause");
        exit(1);
    }
    else{
        printf("Abertura do arquivo foi bem-sucedida!\n");
    }
    printf("Entre com a string a ser gravada no arquivo: ");

    gets(string);
    /**> char *gets(char *): lê uma string da entrada-padrão (teclado) <**/

    /**> Grava a string, caractere a caractere <**/
    for(i = 0; i < strlen(string); i++){
            /**> size_t strlen const char *): comprimento da string <**/
        fputc(string[i],fp);
    /**> int fputc(int, FILE *): escreve um caractere em arquivo. <**/
    }

    printf("(feof(fp)) = %d, \n",(feof(fp)));
    printf("!(feof(fp)) = %d. \n",!(feof(fp)));
    system("pause");
    printf("Fechando o arquivo. \n");
    fclose(fp);

    printf("Abrindo o arquivo. \n");
    fp = fopen("exemplo.txt","r");
    if(fp == NULL){
        printf("Erro na abertura do arquivo");
        system("pause");
        exit(1);
    }
    else{
        printf("Abertura do arquivo foi bem-sucedida!\n");
    }
    printf("(feof(fp)) = %d, \n",(feof(fp)));
    printf("!(feof(fp)) = %d. \n",!(feof(fp)));
    system("pause");
    printf("Incio do while. \n");
    while( !(feof(fp)) ){
            /**> int feof(FILE *): indicador de fim de arquivo. <**/
        c = fgetc(fp);
    /**> int fgetc(*FILE): Lê um caractere do arquivo <**/
        printf("%c",c);
    }
    printf("\n");
    system("pause");
    printf("(feof(fp)) = %d, \n",(feof(fp)));
    printf("!(feof(fp)) = %d. \n",!(feof(fp)));
    system("pause");
    printf("Fechando o arquivo. \n");
    fclose(fp);
    printf("Abrindo o arquivo: leitura e gravação. \n");
    fp = fopen("exemplo.txt","r+");
    if(fp == NULL){
        printf("Erro na abertura do arquivo");
        system("pause");
        exit(1);
    }
    else{
        printf("Abertura do arquivo foi bem-sucedida!\n");
    }
    printf("(feof(fp)) = %d, \n",(feof(fp)));
    printf("!(feof(fp)) = %d. \n",!(feof(fp)));
    system("pause");
    fgets(string,100,stdin);
    printf("(feof(fp)) = %d, \n",(feof(fp)));
    printf("!(feof(fp)) = %d. \n",!(feof(fp)));
    system("pause");
    int result = fputs(string,fp);
    if(result == EOF){
        printf("Erro na gravação do arquivo\n");
        system("pause");
        exit(1);
    }
    else{
        printf("Gravação do arquivo foi bem-sucedida.\n");
        printf("%s",string);
        system("pause");
    }
    fclose(fp);
    system("pause");
    return 0;
}
