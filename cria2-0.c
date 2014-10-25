#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BSIZE 100

int main(int argc, char* argv[]){
	char caracter[26]="abcdefghijklmnopqrstuvxwyz";
	int qtReg, ra;
	int comp, i,tamanhoString1,tamanhoString2,count;
	char *nome, *snome;
	int x;
	char buffer[BSIZE];
	int pos1=0;
	int j;
	float n1,n2,n3;
	FILE* arq;
	arq = fopen("arquivo.txt","w+");
	if(argc <2){
		exit(1);
	}
	qtReg = atoi(argv[1]);
	//printf("%d",qtReg);
	for(j=0;j<qtReg;j++){
		ra = j;
		comp=0;
		comp+=sizeof(int);
		//srand(time(NULL));
		tamanhoString1 = 1 + rand()%18; //sorteia o tamanho do nome
		nome = (char *)(malloc(sizeof(char)*tamanhoString1));//aloca memoria pro nome
		for(count=0;count<tamanhoString1;count++)
		{
			nome[count]=caracter[rand()%25];
			//printf("%c",nome[count]);
		}
		comp+=sizeof(char)*(tamanhoString1+1);
		tamanhoString2 = 1 + rand()%18; //sorteia o tamanho do sobrenome
		snome = (char *)(malloc(sizeof(char)*tamanhoString2)); //alone memoria pro sobrenome
		for(count=0;count<tamanhoString2;count++)
		{
			snome[count]=caracter[rand()%25];
		}
		comp+=sizeof(char)*(tamanhoString2+1);
		comp+=sizeof(float)*3;
		if(BSIZE-pos1 < comp){
			buffer[pos1] = '*';
			for (i = pos1; i < BSIZE; i++)
			{
				buffer[pos1] = '*';
			}
			
			fwrite(buffer,BSIZE,1,arq);
			pos1=0;
		}
		x = (rand()%1000);
		n1 =(float) x/100;
		x = (rand()%1000);
		n2 =(float) x/100;
		x = (rand()%1000);
		n3 =(float) x/100;
		memcpy(&buffer[pos1],&comp,sizeof(int));
		pos1+=sizeof(int);
		memcpy(&buffer[pos1],&ra,sizeof(int));
		pos1+=sizeof(int);
		memcpy(&buffer[pos1],nome,sizeof(char)*tamanhoString1);
		pos1+=sizeof(char)*(tamanhoString1);
		buffer[pos1]='#';
		pos1++;
		memcpy(&buffer[pos1],snome,sizeof(char)*tamanhoString2);
		pos1+=sizeof(char)*(tamanhoString2);
		buffer[pos1]='#';
		pos1++;
		memcpy(&buffer[pos1],&n1,sizeof(int));
		pos1+=sizeof(float);
		memcpy(&buffer[pos1],&n2,sizeof(int));
		pos1+=sizeof(float);
		memcpy(&buffer[pos1],&n3,sizeof(int));
		pos1+=sizeof(float);
		if(argc == 3){
			if(*argv[2]=='P'){
				printf("%d\t%d\t%-20s\t%-20s\t%.2f\t%.2f\t%.2f\n",comp, ra,nome,snome,n1,n2,n3);
			}
		}
		nome=NULL;
		free(nome);
		snome=NULL;
		free(snome);
	}
	fclose(arq);
	return 0;
	}

