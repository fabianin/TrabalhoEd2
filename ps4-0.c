#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
int main (int argc, char *argv[])
{
    FILE *fp = fopen ("dados.bin","rb");
    char buffer[BSIZE];
    char *aux = NULL;
    unsigned bloco_corrente = 1, RA_consultado = atoi(argv[1]), resultPesq, ultimo_bloco = qntd_blocos (fp);
    while (bloco_corrente <= ultimo_bloco)
    {
        fseek (fp, (bloco_corrente - 1) * BSIZE, SEEK_SET);  // posiciona o ponteiro no bloco a ser lido
        fread (buffer, sizeof (char), BSIZE, fp); // lê o bloco para o buffer
        resultPesq = pesquisa_no_bloco (buffer, &aux, RA_consultado);
        if (resultPesq == ENCONTRADO){
			imprime(aux,bloco_corrente);
		}
        bloco_corrente++;
    }
    return 0;
}
