#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 5

// REVISÃO DE STRUCTS
//---------------------------------

struct Ponto2D{
	int x, y;
};
typedef struct Ponto2D Ponto2D;

Ponto2D espelhamento( Ponto2D p ){
	p.x *= -1;
	p.y *= -1;
	return p;
}

void inverter( Ponto2D *p ){
	int aux = (*p).x;
	p->x = p->y;
	p->y = aux;
}

void show(const Ponto2D p){
	printf("(%d , %d)\n", p.x, p.y);
}

typedef struct Plano{
	Ponto2D *pontos; // armazena os pontos
	int n; // indica a quantidade de pontos
} Plano;

Plano* criarPlano(int n){
	/* Cuidado para não fazer isso!
	Plano p;
	p.pontos = malloc( n * sizeof(Ponto2D) );
	return &p; */

	Plano *p = malloc( sizeof(Plano) );
	p->pontos = malloc( n * sizeof(Ponto2D) );
	p->n = n;
	return p;
}

void showPlano( Plano *p ){
	printf("--- Plano ---\n");
	for(int i=0; i<(p->n); i++){
		printf("Ponto %d: ", i+1);
		show( p->pontos[i] );
	}
}

void addPonto( Plano *p, int x, int y ){
	int n = p->n + 1;
	p->n = n;
	p->pontos = realloc( p->pontos, n * sizeof(Ponto2D) );
	p->pontos[n-1].x = x;
	p->pontos[n-1].y = y;
}






typedef struct Cliente {
	int nro;
	char *nome;
	char *endereco;
	int telefone;
	struct Cliente *responsavel;
} Cliente;


Cliente* novoCliente(int nro, char* nome, char *endereco, int tel, Cliente *resp){
//Cliente* novoCliente(int nro, char* nome, char *endereco, int tel){
	Cliente *c = malloc( sizeof(Cliente) );
	c->nro      = nro;
	c->nome     = malloc( strlen(nome) * sizeof(char) );
	c->endereco = malloc( strlen(endereco) * sizeof(char) );
	c->telefone = tel;
	c->responsavel = resp;
	strcpy( c->nome, nome );
	strcpy( c->endereco, endereco );
	return c;
}

void showCliente( Cliente *c ){
	printf("\n:::REGISTRO:::\n");
	printf("      nro: %d\n", c->nro);
	printf("     nome: %s\n", c->nome);
	printf(" endereco: %s\n", c->endereco);
	printf(" telefone: %d\n", c->telefone);
	printf(" * responsavel: ");
	if( c->responsavel == NULL ) puts("-");
	else puts( c->responsavel->nome );
}






int main(){
	// como representar pontos (x,y) usando vetores tradicionais
	//    * problema: separação / isolamento dos elementos 
	int x[MAX_N], y[MAX_N];
	printf("Digite as coordenadas de %d pontos:\n", MAX_N);
	for(int i=0; i<MAX_N; i++)
		scanf("%d %d", &x[i], &y[i]);

	// representar registros de clientes
	int nros[MAX_N];
	char nomes[MAX_N][50];
	char enderecos[MAX_N][50];
	int telefones[MAX_N];
	for(int i=0; i<MAX_N; i++){
		printf("Digite o nro do cliente #%d: ", i);
		scanf("%d", &nros[i]);
		getchar();
		printf("Digite o nome do cliente #%d: ", i);
		fgets( nomes[i] , 50 , stdin );
		printf("Digite o endereco do cliente #%d: ", i);
		fgets( enderecos[i] , 50 , stdin );
		printf("Digite o telefone do cliente #%d: ", i);
		scanf("%d", &telefones[i]);
		puts("");
	}


	// Usar representação na forma de structs
	//  * declaração de structs
	//  * possibilidade de uso do typedef
	//  * utilização da estrutura (uso do operador .)
	//  * uso da estrutura em funções
	//  * utilizando ponteiros com estruturas (uso do operador ->)
	//  * utilizando vetor de estruturas
	Ponto2D ponto;
	printf("Digite as coordenadas de um ponto 2D: ");
	scanf("%d %d", &ponto.x, &ponto.y);

	Ponto2D p = espelhamento( ponto );
	printf("Ponto espelhado: %d | %d\n\n", p.x, p.y);

	inverter( &ponto );
	printf("Ponto invertido: %d | %d\n\n", ponto.x, ponto.y);


	Ponto2D pontos[MAX_N];
	printf("Digite as coordenadas de %d pontos:\n", MAX_N);
	for(int i=0; i<MAX_N; i++)
		scanf("%d %d", &pontos[i].x, &pontos[i].y);

	printf("Os pontos digitados foram: ");
	for(int i=0; i<MAX_N; i++)
		show( pontos[i] );


	// Union
	//https://pt.stackoverflow.com/questions/46668/oque-são-unions-porque-utilizá-los-dentro-de-structs
	


	// Struct com ponteiros
	Cliente *cli1 = novoCliente(1, "Bob Alex",   "Rua UDESC, Bom Retiro", 998342011, NULL);
	Cliente *cli2 = novoCliente(2, "Alexa Mark", "Rua Exame na certa, Choro", 0, cli1);
	Cliente *cli3 = novoCliente(3, "Eve Tyller", "Rua das Mariposas, Toledo", 988998899, cli2);
	showCliente( cli1 );
	showCliente( cli2 );
	showCliente( cli3 );


	// Struct com ponteiros e uso do memcpy
	Plano *plano = criarPlano(2);
	plano->pontos[0].x = 5;
	plano->pontos[0].y = 3;
	plano->pontos[1].x = 3;
	plano->pontos[1].y = -4;

	Plano planoB;
	memcpy( &planoB, plano, sizeof(Plano) );
	planoB.pontos[0].x = planoB.pontos[0].y = 9;
	// altera nos dois planos pois trata-se de um ponteiro

	showPlano( plano );
	showPlano( &planoB );


	// uso de realoc para adaptar tamanho da estrutura
	puts("Adicionando novo ponto...");
	addPonto( plano , 7, 7 );
	puts("Ponto adicionado...");
	showPlano( plano );
}



