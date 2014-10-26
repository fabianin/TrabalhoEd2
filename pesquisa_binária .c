#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 100

enum resultados_pesquisa {ENCONTRADO, NAO_ENCONTRADO, PRIMEIRA_METADE, SEGUNDA_METADE};

unsigned qntd_blocos (FILE *fp)
{
    fseek (fp, 0, SEEK_END); //posiciona ponteiro no fim do arquivo.
    return ftell(fp) / BSIZE;
}

unsigned pesquisa_no_bloco (char *buffer, char **aux, unsigned RA_consultado)
{
    unsigned chave_atual, num_bytes;
    *aux = buffer;
    while (**aux != '*' && *aux - buffer < BSIZE) //Lê registros enquanto não encontra o caractere pós-último registro do bloco e o buffer não é extrapolado.
    {
        memcpy(&num_bytes, *aux, sizeof(int)); //Lê o número de Bytes do registro corrente para a variável num_bytes.
        memcpy (&chave_atual, *aux + sizeof (int), sizeof (int)); //Deslocamento de +sizeof (int) para ignorar o campo de quantidade de Bytes do registro e ir para o campo de RA.
        if(RA_consultado == chave_atual)
            return ENCONTRADO;
        if(RA_consultado < chave_atual){
            if (*aux != buffer){            //Se a chave procurada for menor que a chave do registro lido e este não for o primeiro do bloco,
                return NAO_ENCONTRADO;
            }    //a chave procurada não existe no arquivo.
		}
            else
                return PRIMEIRA_METADE;   //Se a chave procurada for menor que a chave do registro lido e este for o primeiro do bloco, deve-se pesquisar na primeira metade do intervalo considerado do arquivo.
        *aux = *aux + (num_bytes + sizeof (int)); //Aponta para o início do próximo registro. O +sizeof (int) representa os sizeof (int) Bytes correspondentes ao campo de número de Bytes.
    }
    return SEGUNDA_METADE; //Se a chave procurada for maior que a chave do último registro do bloco, deve-se pesquisar na segunda metade do intervalo considerado do arquivo.
}

int main (int argc, char *argv[])
{
    FILE *fp = fopen ("dados_ord.bin","r");
    char buffer[BSIZE];
    char *aux = NULL;
    unsigned i, RA_consultado = atoi (argv[1]), resultPesq, primeiro_bloco = 1, ultimo_bloco = qntd_blocos (fp);
    while (ultimo_bloco >= primeiro_bloco)
    {
        i = (primeiro_bloco + ultimo_bloco) / 2;
        fseek (fp, (i - 1) * BSIZE, SEEK_SET);  // posiciona o ponteiro no bloco do meio
        fread (buffer, sizeof (char), BSIZE, fp); // lê o bloco para o buffer
        resultPesq = pesquisa_no_bloco (buffer, &aux, RA_consultado);
        if (resultPesq == PRIMEIRA_METADE)
            ultimo_bloco = i - 1;
        else
            if (resultPesq == SEGUNDA_METADE)
                primeiro_bloco = i + 1;
            else
            {
                if (resultPesq == ENCONTRADO)
                    printf ("%s\n\n",aux+8);// valor encontrado
                else
                    printf ("Error 404: not found\n\n");// não encontrado
                break;
            }
    }
    return 0;
}
