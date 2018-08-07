#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// REVISÃO DE FUNÇÕES e PONTEIROS
//---------------------------------
int duplica(int);
int fatorial(int);
int fibonacci(int);
int multiplicacao(int,int);
void alocacao(int);
void printVetor(int*, int);

int divisaoA(int dividendo, int divisor, int resto){
	resto = dividendo % divisor;
	return dividendo / divisor;
}

int divisaoB(int dividendo, int divisor, int *resto){
	*resto = dividendo % divisor;
	return dividendo / divisor;
}

void identidade(int linhas, int colunas, int matriz[linhas][colunas]){
	for(int i=0; i<linhas; i++){
		for(int j=0; j<colunas; j++){
			matriz[i][j] = 0;
		}
		matriz[i][i] = 1;
	}
}

void showMatriz( int **m , int n, int *cols ){
	for(int i=0; i<n; i++){
		for(int j=0; j<cols[i]; j++){
			m[i][j] = i*j + j;
			printf("%3d ", m[i][j]);
		}
		puts("");
	}
}




int main(){
	// criação e uso de uma função simples
	int v = 5;
	int res = duplica( v );
	printf("res: %d\n", res);

	// criação de funções recursivas
	//  * fatorial
	//  * fibonacci
	//  * multiplicação através de somas
	//  * divisão através de subtrações
	int fat = fatorial(6);
	printf("fat: %d\n", fat);
	int fib = fibonacci(9);
	printf("fib: %d\n", fib);
	int mul = multiplicacao(4, 5);
	printf("mul: %d\n", mul);


	// explicação do que é um ponteiro
	//  * representação visual de apontador
	//  * uso em funções (passagem por valor / passagem por referência)
	//  * uso de ponteiro de ponteiro
	//  * passagem de matriz fixa como parâmetro
	puts("\n--PONTEIRO BÁSICO--");
	int *pt;
	int a = 7;
	pt = &a;
	*pt = 99;
	printf("a = %d / *pt = %d\n", a, *pt);

	int dividendo = 78;
	int divisor = 5;
	int resto = 0;
	int quociente = divisaoA( dividendo , divisor, resto );
	printf("quociente = %d / resto: %d\n", quociente, resto);
	quociente = divisaoB( dividendo , divisor, &resto );
	printf("quociente = %d / resto: %d\n", quociente, resto);


	puts("\n--PONTEIRO DE PONTEIRO--");
	pt = &a;
	int b = 8;
	int **multipointer = &pt;
	*multipointer = &b;
	**multipointer = 1107;
	printf("b = %d / *pt = %d / **mp = %d\n", b, *pt, **multipointer);

	int linhas = 4;
	int colunas = 4;
	int matriz[linhas][colunas];
	identidade( linhas, colunas, matriz );
	for(int i=0; i<linhas; i++){
		for(int j=0; j<colunas; j++)
			printf("%3d ", matriz[i][j]);
		puts("");
	}


	// alocação dinâmica de memória 
	//  * alocação em função (stack) vs. alocação dinâmica (heap)
	alocacao( 5 );

	

	// ?? como gerar uma matriz irregular - com número de colunas variável ??
	//  * uso de ponteiro de ponteiro para matriz irregular (yagged) 
	puts("\n--MATRIZ IRREGULAR--");
	#define N 3
	int tamanhos[N] = {2,4,3};
	int **multiarray;
	multiarray = malloc(N * sizeof(int));
	for(int i=0; i<N; i++)
		multiarray[i] = malloc( tamanhos[i] * sizeof(int) );
	showMatriz( multiarray , N , tamanhos );


	// realocação de memória
	double *p = malloc( N * sizeof(double) );
	printf("&p(N)  = %p\n", p);
	for( int i=0; i<N; i++ )
		p[i] = i*i;
	p = realloc( p , 10 * sizeof(double) );
	printf("&p(10) = %p\n", p);
	p = realloc( p , 2 * sizeof(double) );
	printf("&p(2)  = %p\n", p);

	puts("");
}






int duplica(int b){
	return b*2;
}


int fatorial(int f){
	if( f<0 ) return 0;
	if( f==0 ) return 1;
	return f * fatorial(f-1);
}


int fibonacci(int f){
	if( f<0 ) return -1;
	if( f==0 || f==1 ) return 1;
	return fibonacci(f-1) + fibonacci(f-2);
}


int multiplicacao(int a, int b){
	if( a==0 || b==0 ) return 0;
	return a + multiplicacao(a, b-1);
}



void alocacao(int n){
	int elementos[n];
	int elementosB;
	int *elems = (int*) malloc (n * sizeof(int));
	int *vetor = (int*) calloc (n, sizeof(int));
	printf("&elementos:  %p\n", &elementos[0]);
	printf("&elementosB: %p\n", &elementosB);
	printf("&elems:      %p\n", &elems[0]);
	printf("&vetor:      %p\n", &vetor[0]);

	for(int i=0; i<n; i++) elementos[i] = i;
	printVetor( elementos, n );
	printVetor( elems, n );
	printVetor( vetor, n );

	free( elems );
	free( vetor );
}


void printVetor( int *v, int n ){
	printf("Vetor: { ");
	for(int i=0; i<n; i++)
		printf("%d ", v[i]);
	printf("}\n");
}
