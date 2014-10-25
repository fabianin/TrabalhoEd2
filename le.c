#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BSIZE 100

int main(int argc, char* argv[]){
	int pos1=0,i,RA,comp_reg,j;
	char nome[20], snome[20];
	float nota[3];
	char buffer[BSIZE];
	FILE* arq;
	arq=fopen("arquivo.txt","r");
	fread(buffer,BSIZE,1,arq);
	memcpy(&comp_reg,&(buffer[pos1]),sizeof(int));
	pos1+=sizeof(int);
	memcpy(&RA,&(buffer[pos1]),sizeof(int));
	pos1+=sizeof(int);
	i=0;
	while (buffer[pos1]!='#')
	{
		memcpy(&nome[i],&(buffer[pos1]),sizeof(char));
		pos1++;
		i++;
	}
	nome[i]='\0';
	pos1++;
	j=0;
	while (buffer[pos1]!='#')
	{
		memcpy(&snome[j],&(buffer[pos1]),sizeof(char));
		pos1++;
		j++;
	}
	snome[j]='\0';
	pos1++;
	memcpy(&nota[0],(&buffer[pos1]),sizeof(float));
	pos1+=sizeof(float);
	memcpy(&nota[1],(&buffer[pos1]),sizeof(float));
	pos1+=sizeof(float);
	memcpy(&nota[2],(&buffer[pos1]),sizeof(float));
	pos1+=sizeof(float);
	//nesse ponto um registro foi lido por completo e seus valores já estão salvo em váriaveis
	
	printf("%d\t%d\t%-20s\t%-20s\t%.2f\t%.2f\t%.2f\t",comp_reg, RA,nome,snome,nota[0],nota[1],nota[2]);
	fclose(arq);
	return 0;
}


