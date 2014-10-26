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
        *aux = *aux + (num_bytes); //Aponta para o início do próximo registro. O +sizeof (int) representa os sizeof (int) Bytes correspondentes ao campo de número de Bytes.
    }
    return NAO_ENCONTRADO;
}

void imprime(char *aux, int bloco_corrente){
	int i,j,pos1,RA,comp_reg;
	char nome[20],snome[20];
	float nota[3];
	pos1=0;
	memcpy(&comp_reg,&(aux[pos1]),sizeof(int));
	pos1+=sizeof(int);
	memcpy(&RA,&(aux[pos1]),sizeof(int));
	pos1+=sizeof(int);
	i=0;
	while (aux[pos1]!='#')
	{
		memcpy(&nome[i],&(aux[pos1]),sizeof(char));
		pos1++;
		i++;
	}
	nome[i]='\0';
	pos1++;
	j=0;
	while (aux[pos1]!='#')
	{
		memcpy(&snome[j],&(aux[pos1]),sizeof(char));
		pos1++;
		j++;
	}
	snome[j]='\0';
	pos1++;
	memcpy(&nota[0],(&aux[pos1]),sizeof(float));
	pos1+=sizeof(float);
	memcpy(&nota[1],(&aux[pos1]),sizeof(float));
	pos1+=sizeof(float);
	memcpy(&nota[2],(&aux[pos1]),sizeof(float));
	pos1+=sizeof(float);
	printf("%d %d %-20s %-20s %.2f %.2f %.2f\n%d\n",comp_reg, RA,nome,snome,nota[0],nota[1],nota[2],bloco_corrente);
}



// para pesquisa binaria



unsigned pesquisa_no_blocoB (char *buffer, char **aux, unsigned RA_consultado)
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
        *aux = *aux + (num_bytes); //Aponta para o início do próximo registro.
    }
    return SEGUNDA_METADE; //Se a chave procurada for maior que a chave do último registro do bloco, deve-se pesquisar na segunda metade do intervalo considerado do arquivo.
}
