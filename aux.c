#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aux.h"


void lerString(char str[], int max) {
	int i;
	char c;
	for (i = 0; i < max-1 && (c=getchar()) != EOF && c != '\n'; i++)
		str[i] = c;
	str[i] = '\0';
}

mensagem adicionaMsg(int atividade[MAX_USERS], int contador, int *maior) {
	if (contador >= 10000)						//verifica que o numero maximo de mensagens no sistema nao foi excedido
		exit(0);

	mensagem msg;
	
	msg.id = leID();							//le o id

	lerString(msg.texto, MAX_MSG);				//le a mensagem

	msg.tamanho = strlen(msg.texto);			//guarda o tamanho da mensagem

	if (msg.tamanho > forum[*maior].tamanho)	//verifica se a nova mensagem e maior que a anteriormente maior
		(*maior) = contador;

	atividade[msg.id]++;						//incrementa a atividade do utilizador

	return msg;

}

int leID() {                          

	int id=0;
	char c;
	getchar();

	while ((c=getchar())<='9' && c>='0')
		id = id*10 + (c - '0');

	if (id > 999)		//verifica se o id nao excede o valor permitido
		exit(0);

	return id;
}

void listaTodas(int total) {
	int i;

	printf("*TOTAL MESSAGES:%d\n", total);

	for (i=0; i<total; i++)
		escreveMsg(i);

}

void escreveMsg(int n) {	//escreve uma mensagem no ecran

	printf("%d:%s\n", forum[n].id, forum[n].texto);

}

void listaUser(int total) {
	int i, user;

	user=leID();

	printf("*MESSAGES FROM USER:%d\n", user);

	for (i=0; i<total; i++)				   //percorre todas as mensagens e escreve as que forem do utilizador
		if (forum[i].id == user)
			printf("%s\n", forum[i].texto);

}

void maisLonga(int total, int maior) {
	int i, comp = forum[maior].tamanho;

	for (i=maior; i<total; i++)            //escreve a primeira maior mensagem e procura outras mensagens com o mesmo tamanho
		if (forum[i].tamanho == comp) {
			printf("*LONGEST SENTENCE:");
			escreveMsg(i);
		}
}

void maisAtivo(int atividade[MAX_USERS]) {
	int i, mais=0;

	for (i=0; i<MAX_USERS; i++)             //procura o primeiro utilizador mais ativo
		if (atividade[i] > atividade[mais])
			mais=i;

	if (atividade[mais]==0)                 //retorna se nao houver atividade
		return;

	for (i=mais; i<MAX_USERS; i++)			//escreve o primeiro utilizador mais ativo e procura outros utilizadores com o mesmo numero de mensagens
		if (atividade[i]==atividade[mais])
			printf("*MOST ACTIVE USER:%d:%d\n", i, atividade[i]);
}

void procuraPalavra(int total) {
	int i, ocorrencias=0;
	char palavra[MAX_MSG];
	getchar();                       //necessario para nao ler o espaco apos o comando 'C'

	lerString(palavra, MAX_MSG);     //le a palavra a procurar

	for (i=0; i<total; i++)			 //percorre todas as mensagens
		ocorrencias += ocorrePalavra(palavra, forum[i].texto);


	printf("*WORD %s:%d\n", palavra, ocorrencias);

}

int ocorrePalavra(char palavra[MAX_MSG], char texto[MAX_MSG]) { 
	int i, j, ocorrencias=0;

	for (i=0; texto[i]!='\0'; i++)									//percorre o texto da mensagem
		if (i==0 || whiteSpace(texto[i-1])) {						//verifica que começa a ler na primeira posicao ou apos um caracter branco
			for (j=0; palavra[j]!='\0' && texto[i+j]!='\0'; j++)	//percorre o palavra e a mensagem
				if (texto[i+j]!=palavra[j])							//se os carcteres forem diferentes para o ciclo
					break;
			if (palavra[j]=='\0')									//verifica que o ciclo anterior acabou no fim da palavra
				if (whiteSpace(texto[i+j]) || texto[i+j]=='\0')		//se apos a palavra esta um caracter branco ou o fim da mensagem, incrementa as ocorrencias
					ocorrencias++;
		}

	return ocorrencias;
}

int whiteSpace(char c) {	//retorna 1 se o caracter e um caracter branco e 0 se nao
	if (c==';' || c==',' || c==' ' || c=='\t' || c=='\n' || c=='.')
		return 1;
	else
		return 0;
}

void ordena(int total) {
	int a[MAX_MENSAGENS+1], aux[MAX_MENSAGENS+1];
	int i;

	printf("*SORTED MESSAGES:%d\n", total);

	for (i=0; i<total; i++)			//cria um vetor com os indices das mensagens
		a[i]=i;

	mergesort(a, 0, total-1, aux);	//ordena alfabeticamente o vetor de indices

	for (i=0; i<total; i++)			//escreve as mensagens ordenadas
		escreveMsg(a[i]);

}

void merge(int a[MAX_MENSAGENS+1], int l, int m, int r, int aux[MAX_MENSAGENS+1]) {
	int i, j, k;
	for (i = m+1; i > l; i--)
	 	aux[i-1] = a[i-1];
	for (j = m; j < r; j++)
	 	aux[r+m-j] = a[j+1];
	for (k = l; k <= r; k++) {
		if (less(aux[j], aux[i]))
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
	}

}

void mergesort(int a[MAX_MENSAGENS+1], int l, int r, int aux[MAX_MENSAGENS+1]) {
	int m = (r+l)/2;
	if (r <= l)
		return;
	mergesort(a, l, m, aux);
	mergesort(a, m+1, r, aux);
	merge(a, l, m, r, aux); 
 }

 int less(int j, int i) {	//retorna 1 se a primeira mensagem e lexicograficamente menor que a segunda ou se forem iguais mas o id da primeira for menor que o da segunda
 	int comp;				//retorna 0 se a segunda mensagem e lexicograficamente menor que a primeira ou se forem iguais mas o id da segunda for menor que o da primeira
 	if (((comp=strcmp(forum[j].texto, forum[i].texto))==0 && forum[j].id < forum[i].id) || comp<0)
		return 1;
	else
		return 0;

 }
