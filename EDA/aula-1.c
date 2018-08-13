#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// REVISÃO BÁSICA DE C
//---------------------------------
int main(){
	// -> tipos básicos (int, long long, float, double, char) e declaração de variáveis
	// -> declaração de vetores e matrizes (inicialização)
	// -> vetores de caracteres (detalhe do \0 no final)
	// -> compilação manual básica: gcc nomePrograma -o nomeResultado
	int valor = 123456789;
	long long valorAlto = 1234567890123456789L;
	float custo = 5.2972f;
	double preco = 5.2556;
	int vetor[5];
	int vetorAux[3] = {1,5,2};
	int matriz[2][3] = {{1,0,0}, {0,1,0}};
	char palavra[10] = {'o', 'l', 'a', '\0' };
	char palavraSimples[10] = "ola";



	//--- escrita de dados
	// -> escrita de dados: print com %i, %lld, %f %lf, %c
	// -> tratamento de caractere como número (tabela ascii);
	// -> detalhes de formatação:
	//      * definir o número de espaços a utilizar no mínimo (com zeros ou não)
	//      * forçar a aparição de sinal
	//      * definir o número de casas decimais
	// -> escrita de strings: print %s e puts
	puts("--ESCRITA DE DADOS--");
	printf("valor = %d\n", valor);
	printf("valor = %lld\n", valorAlto);
	printf("palavra[2] = %c (%d)\n", palavra[2], palavra[2]);
	valor = 11;
	printf("valor = %05d\n", valor);
	printf("valor = %+5d\n", valor);
	printf("custo = %f\n", custo);
	printf("custo = %6.2f\n", custo);
	char frase[100] = "Soh sei que nada sei!";
	printf("puts frase >> ");
	puts( frase );



	//--- leitura de dados
	// -> leitura de dados: scanf com %d, %lld, %f %lf
	//      * (lembre-te: não se especifica o número de casas decimais)
	// -> leitura de caracteres e strings: getchar() e fgets();
	puts("\n--LEITURA DE DADOS--");
	/*scanf("%d", &valor);
	scanf("%lld", &valorAlto);
	scanf("%f", &custo);
	printf("Digite uma letra: ");
	char letra = getchar( );
	printf("letra: %c\n", letra);*/

	//--- leitura de frases
	puts("\n--LEITURA FRASE--");
	char verso[100];
	printf("Digite um verso: ");
	//scanf("%s", verso);
	fgets( verso, 100, stdin );
	printf("verso: %s\n", &verso[0]);
	



	// --- unsigned
	// -> utilização de unsigned (%u)
	puts("\n--UNSIGNED--");
	unsigned int x = -1; // maior valor possível 
	printf("x = %u\n", x);


	// --- precisão
	// -> problema de precisão com números reais (0.1 seria representado como em binário?)
	// -> comparação segura entre números reais (EPS)
	puts("\n--PRECISAO / COMPARAÇÃO REAL--");
	const float EPS = 0.0001;
	float valorReal  = 0.0000023f;
	float valorAprox = 0.0000027f;
	if( valorReal == valorAprox )
		printf("(1) ValorReal == valorAprox\n");
	if( fabs(valorReal - valorAprox) < EPS )
		printf("(2) ValorReal == valorAprox\n");

	// bit shift
	puts("\n--BIT SHIFT--");
	valor = 1 << 30;
	printf("1 << 30 = %d\n", valor);
	valor = 1 << 31;
	printf("1 << 31 = %d\n", valor);
	valorAlto = ((long long) 1) << 60;
	printf("1 << 60 = %lld\n", valorAlto);


	// --- estruturas básicas de decisão e repetição
	// !!cuidado!!
	if( valor >= 0 )
		if( valor > 0 ) printf("POSITIVO");
	else
		printf("NEGATIVO");

	char caracter = 'S';
	switch( caracter ){
		case 'S':
			printf("SIM");
			break;
		case 'N':
			printf("NAO");
			break;
		case 'T':
			printf("TALVEZ");
			break;
		default:
			printf("opção inválida");
	}

	printf("WHILE: ");
	int y = 0;
	while( y < 5 ){
		printf("%d ", y);
		y++;
	}

	printf("\nDO WHILE: ");
	y = 2;
	while( y < 5 ){
		printf("%d ", y);
		y++;
	}

	// -> compilação usando padrão semi-novo c99: gcc -std=c99 nomePrograma -o nomeResultado
	//                   ou padrão novo c11: gcc -std=c11 nomePrograma -o nomeResultado
	//     ** NOTA: melhor uso do hardware do computador e tecnologias de compilação
	//     ** ex: permite o uso de for(int i=...).
	printf("\nFOR: ");
	for(int i=7; i>=0; i--){
		printf("%d ", i);
	}
	puts("\n");


	// -> possibilidade de criar um vetor de tamanho variável 
	printf("Digite o numero de elementos: ");
	int n;
	scanf("%d", &n);
	int elementos[n];

	return 0;
}
//---------------------------------
//*/
