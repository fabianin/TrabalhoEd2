#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int tamanho = 50;
	int vetorRa[tamanho];
	int i,j, temp, k,l;

	for(k=0;k<tamanho;k++){
		vetorRa[k]=k;
	}

	if (tamanho > 1) {
        
        for (i = 0; i < tamanho - 1; i++) {                            //Embaralha os elementos do vetor de registros para gerar uma 
            j = i + rand() / (RAND_MAX/(tamanho-i)+1);                 //sequência de inteiros aleatória
            temp = vetorRa[j];
            vetorRa[j] = vetorRa[i];
            vetorRa[i] = temp;
        }
    }

    for(l=0;l<tamanho;l++){
    	printf("%d\n",vetorRa[l]);
    }
}