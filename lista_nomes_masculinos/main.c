#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    /**> Abertura inicial do programa: título e objetivo. <**/
    printf("NOMES MASCULINOS\n\n");
    printf("Objetivo:\n\t");
    printf("criar uma lista de nomes e salvá-los em um arquivo *.bin.\n\n");

    /**> Cria um arquivo do tipo *.bin para escrita. <**/
    FILE *file = fopen("nomes_masculinos.bin","wb");

    /**> Declara ponteira para string, inicializa com NULL e alloca memoria <**/
    int Nchar = 15, Nname= 20; // tamanho da string nome
    char *caractere = (char *) calloc(Nname*Nchar,sizeof(char));
    char **nome = (char **) calloc(Nname,sizeof(char *));

    /**> Insere os nomes a serem gravados no arquivo. <**/
    int choose, i = 0;
    do{
        nome[i] = caractere + i*Nchar;
        int strtam;
        char nm[Nchar];
        do{
            printf("Diginte um nome masculino: ");
            //scanf("%Nchar[\n]",nome[i]);
             // informa um nome a partir do teclado
            strcpy(nm,fgets(nome[i],Nchar,stdin)); // informa um nome a partir do teclado
            // buffer: alex\n\0
            strtam = strlen(nm);
            printf("tamanho do nome: %d.\n",strtam);
            system("pause");
            if( strtam > Nchar){
                printf("O nome digitado excede o tamanho da memória disponível.\n");
                printf("Digite um nome com menos caracteres!\n");
            }
        }while(strtam > Nchar);
        printf("\n"); //salta para próxima linha
        printf("O nome digitado foi:\n\t");
        printf(" nome: %s",nome[i]); // imprime o nome informado
        printf("Deseja informar outro nome?\n\t");
        printf("Digite 1 para SIM e qualquer outro valor para NÃO.\n\t");
        printf("Informe a sua escolha: ");
        scanf("%d",&choose);
        // buffer 1\n
        if(choose == 1){
            getchar();
            printf("Valor escolhido: %d. ",choose);
            i++;
        }
        else{
            printf("Valor escolhido: %d.\n",choose);
        }

    }while( (choose == 1) && (i < Nname) );
    for(int k = 0; k <= i; k++){
        printf("nome[%d]: %s",k,*(nome + k));
    }
    free(nome);
    return 0;
}
