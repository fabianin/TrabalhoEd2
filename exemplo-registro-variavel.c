#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 100

typedef struct _aluno {
  int RA;
  char primeiro_nome[20];
  char ultimo_nome[20];
  float nota[3];
} Aluno;

int main()
{
  char buffer[BSIZE];
  Aluno a[10], b;
  int   comp_reg,num_reg=3;
  int   pos1,pos2,r;
  FILE *fp;
  
  /*
   * Simulando a gravacao de um arquivo com 3 registros. 
   * O vetor de registros pode ser criado para facilitar a geracao do 
   * arquivo binario. Depois voce deve assumir que apenas um registro 
   * estara' na memoria por vez. 
   * Voce pode gravar tambem o numero de registros para facilitar a leitura. 
   */
  
  fp = fopen("dados.bin","wb");

  /* cria 1o registro */
  a[0].RA = 64545;
  sprintf(a[0].primeiro_nome,"Paula"); 
  sprintf(a[0].ultimo_nome,"Sinval"); 
  a[0].nota[0]=8.9;
  a[0].nota[1]=7.5;
  a[0].nota[2]=4.5;

  /* cria 2o registro */
  a[1].RA = 55444;
  sprintf(a[1].primeiro_nome,"Marcelo"); 
  sprintf(a[1].ultimo_nome,"Pinheiro"); 
  a[1].nota[0]=8.0;
  a[1].nota[1]=7.2;
  a[1].nota[2]=5.6;

  /* cria 3o registro */
  a[2].RA = 123456;
  sprintf(a[2].primeiro_nome,"Juliana"); 
  sprintf(a[2].ultimo_nome,"Andalo"); 
  a[2].nota[0]=9.0;
  a[2].nota[1]=8.7;
  a[2].nota[2]=2.4;

  a[3].RA = 123431;
  sprintf(a[3].primeiro_nome,"Fabiano"); 
  sprintf(a[3].ultimo_nome,"Magro"); 
  a[3].nota[0]=9.3;
  a[3].nota[1]=8.1;
  a[3].nota[2]=2.6;

  a[4].RA = 199721;
  sprintf(a[4].primeiro_nome,"Jean"); 
  sprintf(a[4].ultimo_nome,"szHelcio"); 
  a[4].nota[0]=9.9;
  a[4].nota[1]=8.9;
  a[4].nota[2]=8.8;

  a[5].RA = 86858;
  sprintf(a[5].primeiro_nome,"quatroevinte"); 
  sprintf(a[5].ultimo_nome,"Brenfei"); 
  a[5].nota[0]=9.0;
  a[5].nota[1]=8.7;
  a[5].nota[2]=2.4;

  a[6].RA = 99958;
  sprintf(a[6].primeiro_nome,"Ferrin"); 
  sprintf(a[6].ultimo_nome,"Ferro"); 
  a[6].nota[0]=0.0;
  a[6].nota[1]=0.7;
  a[6].nota[2]=0.4;

  a[7].RA = 444456;
  sprintf(a[7].primeiro_nome,"Alguem"); 
  sprintf(a[7].ultimo_nome,"Segundo nome"); 
  a[7].nota[0]=5.0;
  a[7].nota[1]=3.7;
  a[7].nota[2]=7.4;

  a[8].RA = 444456;
  sprintf(a[8].primeiro_nome,"Renan"); 
  sprintf(a[8].ultimo_nome,"Alouca"); 
  a[8].nota[0]=2.0;
  a[8].nota[1]=9.7;
  a[8].nota[2]=0.4;

  a[9].RA = 124456;
  sprintf(a[7].primeiro_nome,"Profi"); 
  sprintf(a[7].ultimo_nome,"Renatin"); 
  a[9].nota[0]=1.0;
  a[9].nota[1]=1.7;
  a[9].nota[2]=1.4;


  /* Vamos assumir que os registros sempre ocupam menos que BSIZE bytes */
  /* Para facilitar, mudamos a sintaxe dos registros:
   * | num total de bytes do registro | ra | nome1 | # | nome2 | # | nota1 | nota2 | nota3 |
   *          int                      int   char*  char char*  char float   float   float
   */
  
  pos1 = 0; //numero de bytes ocupados no buffer
  
  memcpy(&(buffer[pos1]),&num_reg,sizeof(int));
  //printf("num_reg %d %s\n",num_reg,&(buffer[pos1]));
  pos1 += sizeof(int); //esta sendo ocupado o numero de bytes de um inteiro no buffer
  
 /*A função memcpy() é uma função presente na biblioteca string.h cuja finalidade é copiar blocos de memória. 
  *Ela recebe 3 parâmetros: destino, origem e número de bytes a serem copiados.*/
  
  for (r=0; r < num_reg; r++) {
    
    comp_reg =  //calcula quantos bytes serao ocupados no buffer
      sizeof(int) + // ra
      strlen(a[r].primeiro_nome)*(sizeof(char)) + // nome1 
      1*sizeof(char) + // # 
      strlen(a[r].ultimo_nome)*(sizeof(char)) + // nome2 
      1*sizeof(char) + // # 
      sizeof(float) + sizeof(float) + sizeof(float); // nota1 nota2 nota3
    //printf("--NOVO REG: %d\n",comp_reg);

    /* Montando buffer */

    // num total de bytes
    if (pos1+sizeof(int)>=BSIZE) {         //se a escrita de um int ultrapassar o tamanho do buffer.
      fwrite(buffer,sizeof(char),pos1,fp); //escreve o buffer em memoria e 
      pos1 = 0;                            //esvazia buffer
    }
    memcpy(&(buffer[pos1]),&comp_reg,sizeof(int)); //escreve quantos bytes o registro ocupa no buffer
    //printf("comp_reg %s\n",&(buffer[pos1]));
    pos1+=sizeof(int);                             //atualiza numero de bytes ocupados no buffer
    
    // ra
    if (pos1+sizeof(int)>=BSIZE) {
      fwrite(buffer,sizeof(char),pos1,fp);
      pos1 = 0;
    }
    memcpy(&(buffer[pos1]),&a[r].RA,sizeof(int));
    //printf("ra %s\n",&(buffer[pos1]));
    pos1 += sizeof(int);
    
    // nome1 + #
    if (pos1+sizeof(char)*(strlen(a[r].primeiro_nome)+2)>=BSIZE) {
      fwrite(buffer,sizeof(char),pos1,fp);
      pos1 = 0;
    }
    memcpy(&(buffer[pos1]),a[r].primeiro_nome,sizeof(char)*strlen(a[r].primeiro_nome));
    pos1 += sizeof(char)*strlen(a[r].primeiro_nome);
    buffer[pos1] = '#';
    //printf("nome1 %s\n",&(buffer[pos1-sizeof(char)*strlen(a[r].primeiro_nome)]));
    pos1 += 1*sizeof(char);
    
    // nome2 + #
    if (pos1+sizeof(char)*(strlen(a[r].ultimo_nome)+2)>=BSIZE) {
      fwrite(buffer,sizeof(char),pos1,fp);
      pos1 = 0;
    }
    memcpy(&(buffer[pos1]),a[r].ultimo_nome,sizeof(char)*strlen(a[r].ultimo_nome));
    pos1 += sizeof(char)*strlen(a[r].ultimo_nome);
    buffer[pos1] = '#';
    //printf("nome2 %s\n",&(buffer[pos1-sizeof(char)*strlen(a[r].ultimo_nome)]));
    pos1 += 1*sizeof(char);
    
    // nota1
    if (pos1+sizeof(float)>=BSIZE) {
      fwrite(buffer,sizeof(char),pos1,fp);
      pos1 = 0;
    }
    memcpy(&(buffer[pos1]),&a[r].nota[0],sizeof(float));
    //printf("nota1 %s\n",&(buffer[pos1]));
    pos1 += sizeof(float);

    // nota2
    if (pos1+sizeof(float)>=BSIZE) {
      fwrite(buffer,sizeof(char),pos1,fp);
      pos1 = 0;
    }
    memcpy(&(buffer[pos1]),&a[r].nota[1],sizeof(float));
    //printf("nota2 %s\n",&(buffer[pos1]));
    pos1 += sizeof(float);

    // nota3
    if (pos1+sizeof(float)>=BSIZE) {
      fwrite(buffer,sizeof(char),pos1,fp);
      pos1 = 0;
    }
    memcpy(&(buffer[pos1]),&a[r].nota[2],sizeof(float));
    //printf("nota3 %s\n",&(buffer[pos1]));
    pos1 += sizeof(float);
    
  } // end for

  if (pos1>0) {
    //printf("final %s %d %d\n",buffer,strlen(buffer),pos1);
    fwrite(buffer,sizeof(char),pos1,fp);
  }

  fclose(fp);

  /*-----------------------------------------------------------------------------*/
  /* Simulando a leitura do arquivo */

  fp = fopen("dados.bin","r+");

  pos1 = 0;
  fread(&(buffer[pos1]),sizeof(char),BSIZE,fp);     /* le BSIZE bytes do arquivo para buffer */

  memcpy(&num_reg,&(buffer[pos1]),sizeof(int));     // le um inteiro do buffer para a variavel num_reg
  pos1 += sizeof(int);                              // atualiza posicao de leitura
  //printf("num_reg %d\n",num_reg);

  for (r=0; r < num_reg; r++) {

    // Verifico se posso ler NUM_TOTAL_BYTES 
    if (pos1 > BSIZE-4) {
      // fseek(fp, posicao corrente - (offset), a partir do início do arquivo) 
      fseek(fp,ftell(fp)-(BSIZE-pos1),SEEK_SET);  //posiciona ponteiro do arquivo no inicio do proximo registro
      fread(buffer,sizeof(char),BSIZE,fp);        //carrega o proximo registro desde o seu inicio
      pos1 = 0;
    }
    // Lendo NUM_TOTAL_BYTES
    memcpy(&comp_reg,&(buffer[pos1]),sizeof(int));
    //printf("NOVO REG: %d\n",comp_reg);
    pos1 += sizeof(int);

    // Verifico se o registro inteiro esta no buffer
    if (comp_reg > BSIZE-pos1) { 
      fseek(fp,ftell(fp)-(BSIZE-pos1),SEEK_SET);
      pos1 = 0;
      fread(buffer,sizeof(char),BSIZE,fp);
    }
    
    /* copia demais campos do registro */

    // ra
    memcpy(&b.RA,&(buffer[pos1]),sizeof(int));
    pos1 += sizeof(int);
    //printf("ra %d\n",b.RA);

    // nome1
    pos2 = pos1;
    while(buffer[pos2]!='#') pos2 += sizeof(char);
    memcpy(b.primeiro_nome,&(buffer[pos1]),pos2-pos1);
    b.primeiro_nome[pos2-pos1] = '\0';
    //printf("nome1 %d - %d = %d %s \n",pos2,pos1,pos2-pos1,b.primeiro_nome);

    //printf("MARCADOR %c\n",buffer[pos2]);

    // nome2
    pos1 = pos2 + sizeof(char);
    pos2 = pos1;
    while(buffer[pos2]!='#') pos2 += sizeof(char);
    memcpy(b.ultimo_nome,&(buffer[pos1]),pos2-pos1);
    b.ultimo_nome[pos2-pos1] = '\0';
    //printf("nome2 %d - %d = %d %s \n",pos2,pos1,pos2-pos1,b.ultimo_nome);

    //printf("MARCADOR %c\n",buffer[pos2]);
    pos1 = pos2 + sizeof(char);

    // nota1
    memcpy(&b.nota[0],&(buffer[pos1]),sizeof(float));
    pos1 += sizeof(float);
    //printf("nota %.2f\n",b.nota[0]);

    // nota2
    memcpy(&b.nota[1],&(buffer[pos1]),sizeof(float));
    pos1 += sizeof(float);
    //printf("nota %.2f\n",b.nota[1]);

    // nota3
    memcpy(&b.nota[2],&(buffer[pos1]),sizeof(float));
    pos1 += sizeof(float);
    //printf("nota %.2f\n",b.nota[2]);

    /* imprime o registro lido */
    if(b.RA==64545)printf("%d %6d %s %s %.2f %.2f %.2f\n",
	   comp_reg,b.RA,b.primeiro_nome,b.ultimo_nome,b.nota[0],b.nota[1],b.nota[2]); 
  }
  fclose(fp);
  
  return(0);
}

void leituraArquivo(){

  
}


 