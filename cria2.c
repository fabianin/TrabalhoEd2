#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]){
	char caracter[26]="abcdefghijklmnopqrstuvxwyz";
	int qtReg, ra;
	int comp, i,tamanhoString,count;
	char *nome, *snome;
	int x;
	float n1,n2,n3;
	FILE* arq;
	arq = fopen("arquivo.txt","w+");
	if(argc <2){
		exit(1);
	}
	qtReg = atoi(argv[1]);
	for(i=0;i<qtReg;i++){
		ra=i;
		comp+=sizeof(int);
		srand(time(NULL));
		tamanhoString = rand()%20; //sorteia o tamanho do nome
		nome = (char *)(malloc(sizeof(char)*tamanhoString));//aloca memoria pro nome
		for(count=0;count<tamanhoString;count++)
		{
			nome[count]=caracter[rand()%25];
			//printf("%c",nome[count]);
		}
		comp+=sizeof(char)*tamanhoString+1*sizeof(char);
		tamanhoString = rand()%20; //sorteia o tamanho do sobrenome
		snome = (char *)(malloc(sizeof(char)*tamanhoString)); //alone memoria pro sobrenome
		for(count=0;count<tamanhoString;count++)
		{
			snome[count]=caracter[rand()%25];
		}
		comp+=sizeof(char)*tamanhoString+1*sizeof(char);
		x = (rand()%1000);
		n1 =(float) x/100;
		x = (rand()%1000);
		n2 =(float) x/100;
		x = (rand()%1000);
		n3 =(float) x/100;
		comp+=sizeof(float)*3;
		//imprime a quantidade de bytes do registro
		fprintf(arq,"%d",comp);
		//imprime o RA no arquivo
		fprintf(arq,"%d",ra);
		//imprime o nome e sobrenome no arquivo
		fprintf(arq,"%s",nome);
		fprintf(arq,"#");
		fprintf(arq,"%s",snome);
		fprintf(arq,"#");
		//imprime as notas no arquivo
		fprintf(arq,"%.2f",n1);
		fprintf(arq,"%.2f",n2);
		fprintf(arq,"%.2f",n3);
		fprintf(arq,"\n");
		//libera a memoria alocada para nome e sobrenome
		free(nome);
		free(snome);
	}
	fclose(arq);
	return 0;
	}

