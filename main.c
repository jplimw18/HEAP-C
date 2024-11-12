#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int *arr;
    int tail;
    size_t range;
} Heap;

//inicializador do heap
Heap* init_heap(size_t range)
{
    Heap* h = malloc(sizeof(Heap)); // reserva um espaço de memória adequado para comportar o esperado de bytes de um struct Heap
    h->arr = calloc(range, sizeof(int));
    h->tail = -1;
    h->range = range;

    return h;
}

// func para exibir mais fácilmente o Heap na tela
void print_heap(Heap* h)
{
    for(size_t i = 0; i < h->range; ++i) {
        if((int)i > h->tail)
        {
            printf("campo nulo: ");
        }
        else
        {
            printf("campo ok: ");
        }

        printf("%d\n", h->arr[i]);
    }

    printf("\ntail: %i, range: %zu\n", h->tail, h->range);
}

// func para realocar vetor se necessário para a adição de mais valores
void resize_heap(Heap* h)
{
    size_t new_range = h->range + 2;
    int *new_arr = realloc(h->arr, new_range * sizeof(int)); // tranfere valores do antigo array para o novo com o range incrementado

    memset(new_arr + h->range, 0, (new_range - h->range) * sizeof(int)); // zera espaços de novos de memória

    h->arr = new_arr;
    h->range = new_range;
}

void insert_node(Heap* h, int node)
{
    if(h->tail + 1 > h->range)
    {
        resize_heap(h);
    }

    if(h->tail == -1)
    {
        h->arr[0] = node;
        h->tail++;
    }
    else
    {
        h->arr[h->tail++] = node;
    }
}

int main()
{
    Heap* h = init_heap(10);
    insert_node(h, 10);
    print_heap(h);
    return 0;
}