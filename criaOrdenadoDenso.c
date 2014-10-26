#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"
#define BSIZE 100
 
int main(int argc, char* argv[]){
	/** @param caracter é um vetor que armazena os carateres válidos para as strings que serão geradas
	 * @param qtReg é uma informação que será passada para o programa chamada dele através de argv para dizer quantos registros serão gerados 
	 * @param RA chave principal do registro
	 * @param comp = numero de bytes do registro, incluindo seu proprio campo
	 * @param tamanhoString1 é o tamanho para a string nome
	 * @param tamanhoString2 é o tamanho para a string snome
	 * @param cout iterador de loop
	 * @param i interador de loop
	 * @param j iterador de loop
	 * @param *nome ponteiro para armazenas a string nome
	 * @param *snome ponteiro para a sting snome
	 * @param pos1 armazena até qual posição do buffer está preenchido
	 * @param buffer é a simulação de um buffer
	 * @param n1, váriavel para as notas do registro
	 * @param n2, váriavel para as notas do registro
	 * @param n3, váriavel para as notas do registro */
	char caracter[26]="abcdefghijklmnopqrstuvxwyz";
	int qtReg, ra;
	int comp, i,tamanhoString1,tamanhoString2,count;
	char *nome, *snome;
	int x;
	int offset=0;
	char buffer[BSIZE],buffer2[BSIZE];
	int pos1=0, pos2=0;
	int j;
	float n1,n2,n3;
	FILE* arq, *indices;
	arq = fopen("dados.bin","wb+");
	if((argc==4 && *argv[2]=='P') || (*argv[2]!='P')){
			indices = fopen("indices.bin","wb+");
		}
	if(argc <2){
			exit(1);
	}
	qtReg = atoi(argv[1]);
	//printf("%d",qtReg);
	for(j=0;j<qtReg;j++){
		ra = j;
		comp=0;
		comp+=sizeof(int);//RA e comprimento do registro
		comp+=sizeof(int);
		//srand(time(NULL));
		tamanhoString1 = 1 + rand()%18; //sorteia o tamanho do nome
		nome = (char *)(malloc(sizeof(char)*tamanhoString1));//aloca memoria pro nome
		for(count=0;count<tamanhoString1;count++)
		{
			nome[count]=caracter[rand()%25];
			//printf("%c",nome[count]);
		}
		nome[count]='\0';
		comp+=sizeof(char)*(tamanhoString1+1); //O tamanho do Nome + 1 caracter separador de campo
		tamanhoString2 = 1 + rand()%18; //sorteia o tamanho do sobrenome
		snome = (char *)(malloc(sizeof(char)*tamanhoString2)); //alone memoria pro sobrenome
		for(count=0;count<tamanhoString2;count++)
		{
				snome[count]=caracter[rand()%25];
		}
		snome[count]='\0';
		comp+=sizeof(char)*(tamanhoString2+1); //O tamanho do Nome + 1 caracter separador de campo
		comp+=sizeof(float)*3; //as 3 notas
		if(BSIZE-pos1 < comp){
			if(pos1+sizeof(char)<=BSIZE)buffer[pos1] = '*';
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
		memcpy(&buffer[pos1],&n1,sizeof(float));
		pos1+=sizeof(float);
		memcpy(&buffer[pos1],&n2,sizeof(float));
		pos1+=sizeof(float);
		memcpy(&buffer[pos1],&n3,sizeof(float));
		pos1+=sizeof(float);
		
		if(*argv[2]=='P'){
			printf("%d\t%d\t%-20s\t%-20s\t%.2f\t%.2f\t%.2f\n",comp, ra,nome,snome,n1,n2,n3);
		}
		
		if((argc==4 && *argv[2]=='P') || (*argv[2]!='P')){
			if(j==0){

			}
			if(BSIZE-pos2 < 8){
				if(pos2+sizeof(char)<=BSIZE){
					buffer2[pos2] = '*';
				}
				for (i = pos2; i < BSIZE; i++)
				{
					buffer[pos2] = '*';
				}
				fwrite(buffer2,BSIZE,1,indices);
				pos2=0;
			}
			if(j==0){
				memcpy(&buffer[pos2],&qtReg,sizeof(int));
				pos2+=sizeof(int);
			}
			memcpy(&buffer2[pos2],&ra,sizeof(int));
			pos2+=sizeof(int);
			memcpy(&buffer2[pos2],&offset,sizeof(int));
			pos2+=sizeof(int);
			offset+=comp;
		}
		free(nome);
		free(snome);
		}
		for (i = pos1; i < BSIZE; i++)
			{
				buffer[pos1] = '*';
			}
		fwrite(buffer,BSIZE,1,arq);
		pos1=0;
		if((argc==4 && *argv[2]=='P') || (*argv[2]!='P'))
		{
			for (i = pos2; i < BSIZE; i++)
			{
				buffer[pos2] = '*';
			}
			fwrite(buffer2,BSIZE,1,indices);
			fclose(indices);
		}
		
		fclose(arq);
		return 0;
}
