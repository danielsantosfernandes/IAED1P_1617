// Daniel Fernandes 86400

#include <stdio.h>
#include "aux.h"


int main() {

	int contador=0, maior=0, atividade[MAX_USERS], i;  //contador - numero de mensagens no sistema
	char com = 0;									   //maior - indice da (primeira) maior mensagem

	for (i=0; i<=MAX_USERS; i++) 					   //atividade - vetor que guarda o numero de mensagens de cada utilizador
		atividade[i]=0;

	while (com != 'X') {

		com=getchar();

		switch(com) {

			case 'A': //Adiciona uma mensagem.
				forum[contador]=adicionaMsg(atividade, contador, &maior);
				contador++;
				break;
			case 'L': //Lista todas.
				listaTodas(contador);
				break;
			case 'U': //Lista todas de um dado utilizador.
				listaUser(contador);
				break;
			case 'O': //Lista mais longa.
				maisLonga(contador, maior);
				break;
			case 'T': //Utilizador mais activo.
				maisAtivo(atividade);
				break;
			case 'S': //Lista todas por ordem alfabética.
				ordena(contador);
				break;
			case 'C': //Escreve o número de ocorrências de uma palavra.
				procuraPalavra(contador);
				break;
			case 'X': //Termina.
				printf("%d\n", contador);
				return 0;
				break;
			default:
				break;

		}

	}


	return 0;
}