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
		ra = i;
		comp=0;
		comp+=sizeof(int);
		//srand(time(NULL));
		tamanhoString = rand()%20; //sorteia o tamanho do nome
		nome = (char *)(malloc(sizeof(char)*tamanhoString));//aloca memoria pro nome
		for(count=0;count<tamanhoString;count++)
		{
			nome[count]=caracter[rand()%25];
			//printf("%c",nome[count]);
		}
		comp+=sizeof(char)*(tamanhoString+1);
		tamanhoString = rand()%20; //sorteia o tamanho do sobrenome
		snome = (char *)(malloc(sizeof(char)*tamanhoString)); //alone memoria pro sobrenome
		for(count=0;count<tamanhoString;count++)
		{
			snome[count]=caracter[rand()%25];
		}
		comp+=sizeof(char)*(tamanhoString+1);
		comp+=sizeof(float)*3;
		if(ra==0){
			fprintf(arq,"%d\n",qtReg);
		}
		//coloca o tamanho do registro
		fprintf(arq,"%d",comp);
		//coloca o RA
		fprintf(arq,"%d",ra);
		//coloca o nome e sobrenome
		fprintf(arq,"%s",nome);
		fprintf(arq,"#");
		fprintf(arq,"%s",snome);
		fprintf(arq,"#");
		//coloca as notas
		x = (rand()%1000);
		n1 =(float) x/100;
		fprintf(arq,"%.2f",n1);
		x = (rand()%1000);
		n2 =(float) x/100;
		fprintf(arq,"%.2f",n2);
		x = (rand()%1000);
		n3 =(float) x/100;
		fprintf(arq,"%.2f",n3);
		fprintf(arq,"\n");
		nome=NULL;
		free(nome);
		snome=NULL;
		free(snome);
	}
	fclose(arq);
	return 0;
	}

