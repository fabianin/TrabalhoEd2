#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#DEFINE BSIZE 100 
int main(int argc, char* argv[]){
	int numBytesReg; ///param numBytesReg é a variável que armazena o tamanho em bytes do registro
	int  RA; ///param RA é a chave primária do registro
	int  i, j; ///I e J são iteradores dos loops;
	int quantidade; ///param quantidade é a quantidade de registros que é passado para o programa através do argv
	int tamanhoString; ///param tamanhoString é a quantidade de caracters dos campos nome e snome que podem chegar até a 20
	char *nome; ///param nome é um ponteiro de char que armazena até 20 caracters
	char *snome; ///param snome idem nome
	float nota1, nota2, nota3; ///variáveis aonde são armazenadas as notas
	FILE* fp;
	if(argc <2){
		printf("Numero de parametros invalidos.\n\n");
		exit(1);
	}
	fp = fopen("arquivo.txt","w+");
	if(fp==NULL){
		printf("Erro ao abrir o arquivo.\n\n");
		exit(2);
	}
	
	return 0;
	}
