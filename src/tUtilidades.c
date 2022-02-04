#include "../include/tUtilidades.h"
#include "../include/tAlgoritmosOrdenacao.h"
#include "../include/tRelatorio.h"


struct tVetorOrdenavel{
    int *vet;
    int tam;
};

int qtdNumeros(char *entrada){
    int qtdNumeros = 0;
    for(int i = 0; i < strlen(entrada); i++){
        if(ehNumero(entrada[i]) == TRUE)
            qtdNumeros++; 
    }
    return qtdNumeros;
}

int qtdLetras(char *entrada){
    int qtdLetras = 0;
    for(int i=0; i < strlen(entrada);i++){
        if(ehLetra(entrada[i]) == TRUE)
            qtdLetras++;
    }
    return qtdLetras;
}

char *inicializaVetorChar(int tam){
    char *vet = (char *) calloc(tam+1,sizeof(char));
    if(vet == NULL){
        printf("Erro na alocação do vetor de char!\n");
        exit(1);
    }
    return vet;
}

static int* inicializaVetorInt(int tam){
    int *vet = (int *) malloc(sizeof(int)*tam);
    if(vet == NULL){
        printf("Erro na alocação do vetor de int!\n");
        exit(1);
    }
    return vet;
}

void liberaVetor(void *vet){
    free(vet);
}

void preencheVetorNum(char *vetNum, char *entrada){
    int j = 0;
    for(int i=0; i<strlen(entrada) ;i++){
        if(ehNumero(entrada[i]) == TRUE){
            vetNum[j] = entrada[i];
            j++;
        }
    }
    vetNum[j] = '\0';
}

void preencheVetorLetras(char *vetLetras, char *entrada){
    int j = 0;
    for(int i=0; i < strlen(entrada); i++){
        if(ehLetra(entrada[i]) == TRUE){
            vetLetras[j] = entrada[i];
            j++;
        }
    }
    vetLetras[j] = '\0';
}

tVetorOrdenavel *inicializaEstruturaDoVetor(char *caminho){
    tVetorOrdenavel *tVetor = malloc(sizeof(tVetorOrdenavel));
    FILE *arq = fopen(caminho,"r");
    if(arq == NULL){
        printf("Erro na abertura do arquivo de entrada!\n");
        exit(1);
    }
    fscanf(arq,"%d",&tVetor->tam);
    tVetor->vet = inicializaVetorInt(tVetor->tam);
    for(int i = 0; i < tVetor->tam; i++){
        fscanf(arq,"%d",&tVetor->vet[i]);
    }
    fclose(arq);

    return tVetor;
}

void liberaEstrutura(tVetorOrdenavel *tVet){
    free(tVet->vet);
    free(tVet);
}

void inicializaEspecificacao(tVetorOrdenavel *tVet, char *vetNum, char *vetLetras, int t, char *caminho){
    int *vetAux = inicializaVetorInt(tVet->tam);
    transfereConteudo(vetAux, tVet->vet, tVet->tam);

    int trocas, comp;
    //roda o algoritmo
    for(int i=0; i < strlen(vetLetras) ;i++){
        time_t t_init,t_final;
        t_init = time(NULL);
        trocas = comp = 0;
        switch (vetLetras[i]){
            case 'a':
                //executa todos os métodos
                break;
            case 's':
                selectionsort(tVet->vet,tVet->tam,t,&comp,&trocas);
                break;
            case 'i':
                insertionsort(tVet->vet,tVet->tam,t,&comp,&trocas);
                break;
            case 'e':
                //shellsort
                break;
            case 'q':
                quickSort(tVet->vet,0,tVet->tam-1,&comp,&trocas,t);
                break;
            case 'h':
                //heapsort
                break;
            default:
                break;
        }

        //imprime
        for(int j=0; j<strlen(vetNum) ;j++){
            //sleep(10);
            t_final = time(NULL);
            //printf("Tempo de execucao: %.2f", difftime(t_final,t_init));
            switch (vetNum[j]){
                case '1':
                    relatorio1(tVet->vet,t);
                    break;
                case '2':
                    relatorio2(difftime(t_final,t_init),comp,trocas);
                    break;
                case '3':
                    relatorio3(vetLetras[i],caminho,tVet->tam,t,comp,trocas,difftime(t_final,t_init));
                    break;

                default:
                    break;
            }
        }
        transfereConteudo(tVet->vet, vetAux, tVet->tam);
    }
    liberaVetor(vetAux);
}

static void transfereConteudo(int *vetReceb, int *vetDistr, int tam){
    for(int i=0; i<tam ;i++){
        vetReceb[i] = vetDistr[i];
    }
}

static int ehNumero(char c){
    if(c > '0' && c <= '3') 
        return TRUE;
    return FALSE;
}

static int ehLetra(char c){
    if((c >= 'a' && c <= 'z') || (c >='A' && c <='Z')) 
        return TRUE;
    return FALSE;
}

