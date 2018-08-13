#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void requisitos(int *software, int n, int s){
	// não tem pre-requisito de instalação
	if( software[s] == -1 ){
		printf(" %d", s);
		return;
	}
	
	requisitos( software, n, software[s] );
	printf(" %d", s);
}

int compara(int *a, int n, int *b, int m){
	if( n > m )
		return +1;
	if( m > n )
		return -1;
	
	for(int i=0; i<n; i++){
		if( a[i] > b[i] )
			return +1;
		else if( b[i] > a[i] )
			return -1;
	}
	
	return 0;
}


int* find(char *t, char *p){
	int *res = malloc( sizeof(int) );
	int cont = 0;
	int n = strlen( t );
	int m = strlen( p );
	
	for(int i=0; i<n; i++){
		int a = 1;
		for(int k=0; k<m; k++){
			if( t[i+k] != p[k] ){
				a = 0;
				break;
			}
		}
		if( a==1 ){
			res[cont] = i;
			cont += 1;
			res = realloc( res, (cont+1) * sizeof(int) );
		}
	}
	res[cont] = -1;
	return res;
}


int main(){
	char texto[50];
	char palavra[5];
	fgets( texto, 49, stdin );
	texto[ strlen(texto)-1 ] = '\0';
	
	fgets( palavra, 4, stdin );
	palavra[ strlen(palavra)-1 ] = '\0';
	
	int *p = find( texto, palavra );
	for(int i=0; p[i]!=-1; i++)
		printf(" %d", p[i] );
	puts("");
	
	
	/*
	int n,m;
	printf("Digite o numero de digitos de n e m: ");
	scanf("%d %d", &n, &m);
	printf("Digite o primeiro número grande: ");
	int na[n];
	for(int i=0; i<n; i++)
		scanf("%d", &na[i]);
	
	printf("Digite o segundo número grande: ");	
	int nb[m];
	for(int i=0; i<m; i++)
		scanf("%d", &nb[i]);
	int resposta = compara( na, n, nb, m );
	printf("resposta: %d\n", resposta);
	*/
	
	
	/*
	int soft[6] = {1, 4, 0, 1, -1, 4};
	requisitos( soft, 6, 2 );
	puts("");
	*/
	
	
	
	return 0;
}
