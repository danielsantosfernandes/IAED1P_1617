#define MAX_MSG 141
#define MAX_MENSAGENS 10000
#define MAX_USERS 1000

typedef struct {

	int id;
	char texto[MAX_MSG];
	int tamanho;

} mensagem;

void lerString(char str[], int max);
mensagem adicionaMsg(int atividade[MAX_USERS], int contador, int *maior);
int leID();
void listaTodas(int total);
void escreveMsg(int n);
void listaUser(int total);
void maisLonga(int total, int maior);
void maisAtivo(int atividade[MAX_USERS]);
void procuraPalavra(int total);
int ocorrePalavra(char palavra[MAX_MSG], char texto[MAX_MSG]);
void ordena(int total);
void merge(int a[MAX_MENSAGENS+1], int l, int m, int r, int aux[MAX_MENSAGENS+1]);
void mergesort(int a[MAX_MENSAGENS+1], int l, int r, int aux[MAX_MENSAGENS+1]);
int whiteSpace(char c);
int less(int j, int i);

mensagem forum[MAX_MENSAGENS];
