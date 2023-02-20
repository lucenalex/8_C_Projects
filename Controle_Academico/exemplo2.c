#define MAX 3
int main() {
    typedef struct funcionario{
       char nome[21];
      float salario;
    }Func;
    Func *f[MAX];
    int i;
    for(i=0; i < MAX; i++){
      f[i] = malloc(sizeof(funcionario));
      printf("\nNome: ");
      scanf("%s",f[i]->nome);
      printf("Salario: ");
      scanf("%f", &f[i]->salario);
    }
    for(i=0; i<MAX; i++) {
        printf("\nNome: %s ", f[i]->nome);
        printf("\nSalario: %f ", f[i]->salario);
    }
}
