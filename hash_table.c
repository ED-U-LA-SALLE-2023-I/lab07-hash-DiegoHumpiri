#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int randomtimes = 1;

struct Cell{
    int data;
    struct Cell* next;
};

struct Lista{
    struct Cell *inicio;
    struct Cell *fin;
};
void insertarLista(struct Lista *lista, int data);
void eliminarItemLista(struct Lista *lista, int data);
bool buscarItemLista(struct Lista *lista, int data);

struct HashTable{
    int n;
    struct Lista* buckets;
    int (*funcionHash)(int, int);
    //void initHastTable(struct HashTable* self, int n);
    //void delete(struct HashTable* self, int x);
    //int find(struct HashTable* self, int x);
};
void initHashTable(struct HashTable* self, int n, int (*fHash)(int, int)){
    self->n = n;
    self->buckets = (struct Lista*)malloc(n * sizeof(struct HashTable));
    for(int i = 0; i < n; i++) {
        self->buckets[i].inicio = NULL;
        self->buckets[i].fin = NULL;
    }
    self->funcionHash = fHash;
}
void insert(struct HashTable* self, int x){
    insertarLista(&(self->buckets[self->funcionHash(x, 10)]), x);
}
int delete(struct HashTable* self, int x) {
    int pos = self->funcionHash(x, 10);
    eliminarItemLista(&(self->buckets[pos]), x);
}
int find(struct HashTable* self, int x){
    int pos = self->funcionHash(x, 10);
    if(!buscarItemLista(&(self->buckets[pos]), x)) {
        printf("None ");
        return -1;
    } else {
        return x;
    }
}
void* randomHashFun(int m, int n){
    //int (**funciones)(int, int) = malloc(m * sizeof(int (*)(int, int))); 
    srand(time(NULL));
    int* fnTable = malloc(m * sizeof(int));
    for(int i = 0; i < m; i++) {
        fnTable[i] = rand() % n;
    }
    int randFn( int x , int n) {
        return fnTable[x];
    }
    return &randFn;
}
int mi_Mod(int x, int n);
int randomFn(int x, int n);


int main(){
    printf("mi_Mod(52) = %d\n", mi_Mod(52, 10));
    printf("mi_Mod(3235235) = %d\nHash Table:\n", mi_Mod(3235235, 10));
    struct HashTable table;
    initHashTable(&table, 10, &mi_Mod);
    int x = 1234567;
    int y = 765543344;
    insert(&table, x);
    insert(&table, y);
    printf( "%d\n", find(&table, 1234567) );
    printf( "%d\n", find(&table, 12345) );
    insert(&table, 543723);
    insert(&table, 54354);
    printf( "%d\n", find(&table, y) );
    printf( "%d\n", find(&table, 54354) );

    printf("\nrandomFn(52) = %d\nrandomFn(3235235, 10) = %d\nHash Table:\n", 
            randomFn(3235235, 10), randomFn(3235235, 10));

    initHashTable(&table, 10, &randomFn);
    x = 1234567;
    y = 765543344;
    insert(&table, x);
    insert(&table, y);
    printf( "%d\n", find(&table, x) );
    printf( "%d\n", find(&table, y) );
    printf( "%d\n", find(&table, x) );

    int (*randomFn2)(int, int) = (int (*)(int, int))randomHashFun(1000, 10);
    
    printf("\nrandomFn2(52) = %d\nrandomFn2(3235235, 10) = %d\nHash Table:\n", 
            randomFn2(3235235, 10), randomFn2(3235235, 10));

    return 0;
}

int mi_Mod(int x, int n) {
    return x%n;
}
int randomFn(int x, int n) {
    srand(time(NULL));
    int r = rand() % n;
    for(int i = 0; i < randomtimes; i++) {
        r = rand() % n;
    }
    randomtimes++;
    return r;
}


//Cosas de listas enlazadas
void insertarLista(struct Lista *lista, int data){
     struct Cell *cell = malloc(sizeof(struct Cell));
     cell->data = data;
     if(lista->inicio == NULL){
        cell->next = lista->inicio;
        lista->inicio = cell;
        lista->fin = cell;
     }
     else{
         cell->next = lista->inicio;
         lista->inicio = cell;
     }
}
void eliminarItemLista(struct Lista *lista, int data){
    if(!buscarItemLista(lista, data)){
        printf("No existe el item\n");
    }else {
        struct Cell *anterior = lista->inicio;
        struct Cell *actual = lista->inicio;
        if(actual->data == data){
            lista->inicio = actual->next;
            free(actual->next);
            actual = anterior->next;
        } else {
            actual = anterior->next;
        }
        while( actual != NULL ) {
            if( actual->data == data ) {
                anterior->next = actual->next;
                free(actual);
                actual = anterior->next;
            } else {
                actual = actual->next;
                anterior = anterior->next;
            }
        } 
    }
}
bool buscarItemLista(struct Lista *lista, int data){
    if(lista->inicio == NULL){
        return false;
    }else {
        for(struct Cell *temp = lista->inicio; temp !=NULL; temp = temp->next){
            if( temp->data == data ){
                return true;
            }
        }
    }
    return false;
}
