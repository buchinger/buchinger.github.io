#include <cstdio>
#include <cmath>
#include <climits>
#include <iostream>

using namespace std;

//============================
class No{
public:
    int elemento;
    No* proximo;
    No(int valor, No* prox){
        elemento = valor;
        proximo = prox;
    }
};
//============================
//============================
class Pilha{
private:
    int elementos;
    No* topo;
public:
    Pilha( ){
        elementos = 0;
        topo = NULL;
    }
    void empilha(int valor){
        No *n = new No( valor, topo );
        topo = n;
        elementos++;
    }
    int desempilha( ){
        if( topo == NULL )
            return INT_MAX;
        No *n = topo;
        int ret = n->elemento;
        topo = n->proximo;
        elementos--;
        delete n;
        return ret;
    }
    void limpar( ){
        No *temp = topo;
        while( temp!=NULL ){
            topo = temp->proximo;
            delete temp;
            elementos--;
            temp = topo;
        }
    }
    void print(){
        No *temp = topo;
        cout << "Pilha: ";
        while( temp!=NULL ){
            cout << temp->elemento << ",";
            temp = temp->proximo;
        }
        cout << endl;
    }
    int tamanho(){
        return elementos;
    }
};
//============================
//============================
class ListaEncadeada{
private:
    int elementos;
    No* inicio;
public:
    ListaEncadeada(){
        elementos = 0;
        inicio = NULL;
    }
    No* getInicio(){ return inicio; }
    int getTamanho(){ return elementos; }

    void adicionar(int valor){
        No* novo = new No(valor, inicio);
        inicio = novo;
    }
    void anexar(int valor){
        No *novo = new No(valor, NULL);
        No *temp = inicio;
        if( inicio == NULL )
            inicio = novo;
        else{
            while( temp!=NULL ){
                if( temp->proximo == NULL ){
                    temp->proximo = novo;
                    break;
                }
                temp = temp->proximo;
            }
        }
    }
    bool remover(int valor){
        No *temp = inicio;
        while( temp!=NULL ){
            if( temp->proximo != NULL and temp->proximo->elemento == valor ){
                No *aux = temp->proximo;
                temp->proximo = aux->proximo;
                delete aux;
                elementos--;
                return true;
            }
            temp = temp->proximo;
        }
        return false;
    }
    int encontrar(int valor){
        int indice = 0;
        No *temp = inicio;
        while( temp!=NULL ){
            if( temp->elemento == valor )
                return indice;
            indice++;
            temp = temp->proximo;
        }
        return -1;
    }
    void removerDuplicatas(){
        ListaEncadeada ja_foram = ListaEncadeada();
        No *temp = inicio;
        if( temp != NULL )
            ja_foram.adicionar( temp->elemento );

        while( temp->proximo != NULL ){
            bool replica = false;
            No *aux = ja_foram.getInicio();
            while( aux!=NULL ){
                if( temp->proximo->elemento == aux->elemento ){
                    No *duplicata = temp->proximo;
                    temp->proximo = duplicata->proximo;
                    delete duplicata;
                    replica = true;
                    break;
                }
                aux = aux->proximo;
            }
            if( !replica ){
                ja_foram.adicionar( temp->proximo->elemento );
                temp = temp->proximo;
            }
        }
    }
    void print(){
        No *temp = inicio;
        cout << "Lista Encadeada: ";
        while( temp!=NULL ){
            cout << temp->elemento << ",";
            temp = temp->proximo;
        }
        cout << endl;
    }
};




#define FOLHA NULL
#define PRETO true
#define VERMELHO false
// Nó Vermelho e Preto (usado na árvore Vermelha e Preta)
class NoVP{
public:
    int elemento;
    bool cor;
    NoVP *esquerda, *direita, *pai;

    // construtor
    NoVP( int valor, NoVP* p=FOLHA, NoVP* e=FOLHA, NoVP* d=FOLHA, bool c=VERMELHO ){
        elemento = valor;
        cor = c;
        pai = p;
        esquerda = e;
        direita = d;
    }
};

/*
    Propriedades da árvore vermelha-preta
    1 - Todos os nós são vermelhos ou pretos
    2 - A raiz é preta
    3 - Toda folha é preta
    4 - Se um nó é vermelho então ambos os seus filhos são pretos
    5 - Para cada nó, todos os caminhos deste um nó até as folhas
        descendentes contêm o mesmo número de nós pretos.
*/

class ArvoreVP{
private:
    NoVP *raiz;
    int elementos;
public:
    //construtor
    ArvoreVP(){
        raiz = FOLHA;
        elementos = 0;
    }
    //---------------------------------------------
    void inserir( int valor ){
        elementos++;
        NoVP *novo = new NoVP( valor );
        NoVP *temp = raiz;
        NoVP *aux = FOLHA;
        while( temp != FOLHA ){
            aux = temp;
            if( valor < aux->elemento )
                temp = aux->esquerda;
            else
                temp = aux->direita;
        }
        novo->pai = aux;
        if( aux == FOLHA )
            raiz = novo;
        else{
            if( valor < aux->elemento )
                aux->esquerda = novo;
            else
                aux->direita = novo;
        }
        insertFixUp( novo );
    }
    //---------------------------------------------
    private:void rotateLeft( NoVP* novo ){
        if( novo == FOLHA ) return;
        NoVP *aux = novo->direita;
        novo->direita = aux->esquerda;
        if( aux->esquerda != FOLHA )
            aux->esquerda->pai = novo;
        aux->pai = novo->pai;
        if( novo->pai == FOLHA )
            raiz = aux;
        else if(novo == novo->pai->esquerda)
            novo->pai->esquerda = aux;
        else
            novo->pai->direita = aux;
        aux->esquerda = novo;
        novo->pai = aux;
    }
    //---------------------------------------------
    private:void rotateRight( NoVP* novo ){
        if( novo == FOLHA ) return;
        NoVP *aux = novo->esquerda;
        novo->esquerda = aux->direita;
        if( aux->direita != FOLHA )
            aux->direita->pai = novo;
        aux->pai = novo->pai;
        if( novo->pai == FOLHA )
            raiz = aux;
        else if(novo == novo->pai->direita)
            novo->pai->direita = aux;
        else
            novo->pai->esquerda = aux;
        aux->direita = novo;
        novo->pai = aux;
    }
    //---------------------------------------------
    private:void insertFixUp( NoVP* novo ){
        NoVP *aux;
        while( novo->pai!=FOLHA && novo->pai->cor == VERMELHO ){
            if( novo->pai == novo->pai->pai->esquerda ){
                aux = novo->pai->pai->direita;
                if( aux!=FOLHA && aux->cor == VERMELHO ){
                    novo->pai->cor = PRETO;
                    aux->cor = PRETO;
                    novo->pai->pai->cor = VERMELHO;
                    novo = novo->pai->pai;
                }
                else if( novo == novo->pai->direita ){
                    novo = novo->pai;
                    rotateLeft( novo );
                }
                novo->pai->cor = PRETO;
                novo->pai->pai->cor = VERMELHO;
                rotateRight( novo->pai->pai );
            }
            else {
                aux = novo->pai->pai->esquerda;
                if( aux!=FOLHA && aux->cor == VERMELHO ){
                    novo->pai->cor = PRETO;
                    aux->cor = PRETO;
                    novo->pai->pai->cor = VERMELHO;
                    novo = novo->pai->pai;
                }
                else if( novo == novo->pai->esquerda ){
                    novo = novo->pai;
                    rotateRight( novo );
                }
                if( novo!=FOLHA && novo->pai != FOLHA ){
                    novo->pai->cor = PRETO;
                    if( novo->pai->pai != FOLHA ){
                        novo->pai->pai->cor = VERMELHO;
                        rotateLeft( novo->pai->pai );
                    }
                }
            }
        }
        raiz->cor = PRETO;
    }

    //---------------------------------------------
    public:void printPreOrder( ){
        preOrder( raiz );
    }
    private:void preOrder( NoVP *no ){
        if( no != FOLHA ){
            //printf("%c%i(", (no->cor==PRETO ? 'P':'V'), no->elemento);
            printf("%i(", no->elemento);
            preOrder( no->esquerda );
            preOrder( no->direita );
            printf(")");
        }
    }
    //---------------------------------------------
    public:NoVP* busca(int valor){
        NoVP *aux = raiz;
        while( aux != FOLHA ){
            if( aux->elemento == valor )
                return aux;
            if( valor < aux->elemento )
                aux = aux->esquerda;
            else
                aux = aux->direita;
        }
        return FOLHA;
    }
    public:NoVP* minimo(){
        NoVP *aux = raiz;
        if( raiz == FOLHA )
            return FOLHA;
        while( aux->esquerda != FOLHA ){
            aux = aux->esquerda;
        }
        return aux;
    }
    public:NoVP* maximo(){
        NoVP *aux = raiz;
        if( raiz == FOLHA )
            return FOLHA;
        while( aux->direita != FOLHA ){
            aux = aux->direita;
        }
        return aux;
    }
};




void testePilha();
void testeListaEncadeada();
void testeArvore();


//=============================================================//
//=============================================================//
//=============================================================//


int main(){
    testePilha();
    testeListaEncadeada();
    testeArvore();
}

//=============================================================//
//=============================================================//
//=============================================================//

void testePilha(){
    cout << "==============================" << endl;
    cout << "INICIO DO TESTE DA PILHA" << endl;
    cout << "==============================" << endl;
    Pilha pilha = Pilha();
    pilha.empilha(5);
    pilha.empilha(2);
    pilha.empilha(7);
    pilha.empilha(1);
    pilha.empilha(3);
    cout << "Tamanho:" << pilha.tamanho() << endl;
    pilha.print();

    pilha.desempilha();
    pilha.desempilha();
    cout << "Tamanho:" << pilha.tamanho() << endl;
    pilha.print();

    pilha.limpar();
    cout << "Tamanho:" << pilha.tamanho() << endl;
    pilha.print();

    pilha.desempilha();
    cout << "==============================" << endl << endl;
}
//=============================================================//
//=============================================================//
void testeListaEncadeada(){
    cout << "==============================" << endl;
    cout << "INICIO DO TESTE DA LISTA ENCADEADA" << endl;
    cout << "==============================" << endl;
    ListaEncadeada lista = ListaEncadeada();
    lista.adicionar( 11 );
    lista.anexar( 17 );
    lista.anexar( 9 );
    lista.adicionar( 17 );
    lista.anexar( 7 );
    lista.adicionar( 11 );
    lista.print();

    cout << "Encontrar 7: esta na posicao " << lista.encontrar(7) << endl;
    cout << "Encontrar 13: esta na posicao " << lista.encontrar(13) << endl;

    cout << "Excluindo o 9" << endl;
    lista.remover( 9 );
    lista.print();

    cout << "Excluindo as duplicatas" << endl;
    lista.removerDuplicatas();
    lista.print();
    cout << "==============================" << endl << endl;
}
//=============================================================//
//=============================================================//
void testeArvore(){
    cout << "==============================" << endl;
    cout << "INICIO DO TESTE DA ARVORE VERMELHA-PRETA" << endl;
    cout << "==============================" << endl;
    ArvoreVP arvore = ArvoreVP();
    arvore.inserir( 5 );
    arvore.inserir( 6 );
    arvore.inserir( 9 );
    arvore.inserir( 11 );
    arvore.inserir( 2 );
    arvore.inserir( 3 );
    arvore.inserir( 12 );
    arvore.inserir( 13 );
    arvore.inserir( 14 );
    cout << "A arvore binaria em pre-ordem: " << endl;
    arvore.printPreOrder();

    cout << endl << "Elemento 1 esta na arvore? ";
    NoVP *no = arvore.busca( 1 );
    if( no == FOLHA ) cout << "NAO!";
    else cout << "SIM!!";

    cout << endl << "Elemento 11 esta na arvore? ";
    no = arvore.busca( 11 );
    if( no == FOLHA ) cout << "NAO!";
    else cout << "SIM!!";

    cout << endl << "O menor elemento eh: " << arvore.minimo()->elemento;
    cout << endl << "O maior elemento eh: " << arvore.maximo()->elemento << endl;
    cout << "==============================" << endl << endl;
}
//=============================================================//
//=============================================================//
