// ATENÇÃO: tudo o que estiver depois do "//" é apenas comentário
// texto que não é considerado no algoritmo

#include <stdio.h> // permite o uso das instruções de entrada e saída de dados
#include <math.h>  // permite o uso das principais funções matemáticas

main(){                       // define o início do algoritmo
       int a,b,c;             // declara algumas variáveis inteiras
       float delta, x1, x2;   // declara outras variáveis reais (decimais)
       printf("Digite os valores de a, b e c: ");  // mostra texto na tela
       scanf("%i %i %i", &a, &b, &c);              // recebe os valores
       delta = b*b - 4*a*c;  // calcula delta
       if( delta>=0 ){       // testa se delta é positivo (ou zero)
           x1 = (-b + sqrt(delta)) / (2*a);    // calcula x1
           x2 = (-b - sqrt(delta)) / (2*a);    // calcula x2
           printf("x' = %f\n", x1);            // mostra valor de x1
           printf("x'' = %f\n", x2);           // mostra valor de x2
       } // indica o final da condição "se"
       else{                 // senão, se delta não for maior ou igual a zero
            printf("Nao existem raizes reais!!\n");  // mostra texto
       } // indica o final do "senão"
       printf("\nFIM =)\n"); // mostra texto na tela
       system("pause"); // faz com que o programa pare antes de fechar / terminar
} // indica o final do programa
