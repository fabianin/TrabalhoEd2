#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
int main (int argc, char *argv[])
{
	FILE *fp = fopen ("indices.bin","rb");
	char buffer[BSIZE];
	char *aux = NULL;
	int offset;
	unsigned i, RA_consultado = atoi (argv[1]), resultPesq, primeiro_bloco = 1, ultimo_bloco = qntd_blocos (fp);
	while (ultimo_bloco >= primeiro_bloco)
	{
		i = (primeiro_bloco + ultimo_bloco) / 2;
		fseek (fp, (i - 1) * BSIZE, SEEK_SET);  // posiciona o ponteiro no bloco do meio
		fread (buffer, sizeof (char), BSIZE, fp); // lê o bloco para o buffer
		resultPesq = pesquisa_no_blocoI (buffer, &aux, RA_consultado, i);
		if (resultPesq == PRIMEIRA_METADE){
			ultimo_bloco = i - 1;
		}
		else{
			if (resultPesq == SEGUNDA_METADE){
				primeiro_bloco = i + 1;
			}
			else
			{
				if (resultPesq == ENCONTRADO)
					{
						memcpy(&offset,aux+sizeof(int),sizeof(int));
						printf ("offset: %d",offset);
					}
				break;
			}
		}
	}
	return 0;
}
