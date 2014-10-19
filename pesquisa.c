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

FILE *fp=NULL;

	char buffer[BSIZE];
    Aluno  b;
    int comp_reg, num_reg;
    int pos1, pos2, r;

void busca();
int main(int argc, char* argv[]) {
    fp = fopen(argv[1],"r");
    printf("%s",argv[1]);
    busca(fp);
    return (0);
}
void busca() {
    /*-----------------------------------------------------------------------------*/
    /* Simulando a leitura do arquivo */
    int chave;
    printf("Digite o RA a ser pesquisado: ");
    scanf("%d",&chave);
    pos1 = 0;
    fread(&(buffer[pos1]), sizeof (char), BSIZE, fp); /* le BSIZE bytes do arquivo para buffer */
    memcpy(&num_reg, &(buffer[pos1]), sizeof (int)); // le um inteiro dop buffer para a variavel num_reg
    pos1 += sizeof (int); // atualiza posicao de leitura
    //printf("num_reg %d\n",num_reg);
    //fread(&num_reg,sizeof(int),1,fp);
    printf("%d",num_reg);
    for (r = 0; r < num_reg; r++) {

        // Verifico se posso ler NUM_TOTAL_BYTES 
        if (pos1 > BSIZE - 4) {
            // fseek(fp, posicao corrente - (offset), a partir do início do arquivo) 
            fseek(fp, ftell(fp)-(BSIZE - pos1), SEEK_SET); //posiciona ponteiro do arquivo no inicio do proximo registro
            fread(buffer, sizeof (char), BSIZE, fp); //carrega o proximo registro desde o seu inicio
            pos1 = 0;
        }
        // Lendo NUM_TOTAL_BYTES
        memcpy(&comp_reg, &(buffer[pos1]), sizeof (int));
        //printf("NOVO REG: %d\n",comp_reg);
        pos1 += sizeof (int);

        // Verifico se o registro inteiro esta no buffer
        if (comp_reg > BSIZE - pos1) {
            fseek(fp, ftell(fp)-(BSIZE - pos1), SEEK_SET);
            pos1 = 0;
            fread(buffer, sizeof (char), BSIZE, fp);
        }

        /* copia demais campos do registro */

        // ra
        memcpy(&b.RA, &(buffer[pos1]), sizeof (int));
        pos1 += sizeof (int);
        //printf("ra %d\n",b.RA);

        // nome1
        pos2 = pos1;
        while (buffer[pos2] != '#') pos2 += sizeof (char);
        memcpy(b.primeiro_nome, &(buffer[pos1]), pos2 - pos1);
        b.primeiro_nome[pos2 - pos1] = '\0';
        //printf("nome1 %d - %d = %d %s \n",pos2,pos1,pos2-pos1,b.primeiro_nome);

        //printf("MARCADOR %c\n",buffer[pos2]);

        // nome2
        pos1 = pos2 + sizeof (char);
        pos2 = pos1;
        while (buffer[pos2] != '#') pos2 += sizeof (char);
        memcpy(b.ultimo_nome, &(buffer[pos1]), pos2 - pos1);
        b.ultimo_nome[pos2 - pos1] = '\0';
        //printf("nome2 %d - %d = %d %s \n",pos2,pos1,pos2-pos1,b.ultimo_nome);

        //printf("MARCADOR %c\n",buffer[pos2]);
        pos1 = pos2 + sizeof (char);

        // nota1
        memcpy(&b.nota[0], &(buffer[pos1]), sizeof (float));
        pos1 += sizeof (float);
        //printf("nota %.2f\n",b.nota[0]);

        // nota2
        memcpy(&b.nota[1], &(buffer[pos1]), sizeof (float));
        pos1 += sizeof (float);
        //printf("nota %.2f\n",b.nota[1]);

        // nota3
        memcpy(&b.nota[2], &(buffer[pos1]), sizeof (float));
        pos1 += sizeof (float);
        //printf("nota %.2f\n",b.nota[2]);

        /* imprime o registro lido */
        if(b.RA == chave){
				printf("%d %6d %s %s %.2f %.2f %.2f\n",
					comp_reg, b.RA, b.primeiro_nome, b.ultimo_nome, b.nota[0], b.nota[1], b.nota[2]);
		}
    }
    fclose(fp);
}
