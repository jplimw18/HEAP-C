#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct {
    int *arr;
    int tail;
    size_t range;
    bool type; // True para MIN e false para MAX
} Heap;

// retorna indice da folha a esquerda
int left_node(size_t idx)
{
    return 2 * idx + 1;
}

// retorna indice da folha a direita
int right_node(size_t idx)
{
    return 2 * (idx + 1);
}

// retorna o indice do nodo pai
int parent_node(size_t idx)
{
    return (int)((idx - 1) / 2); 
}

//inicializador do heap
Heap* init_heap(size_t range, bool type)
{
    Heap* h = malloc(sizeof(Heap)); // reserva um espaço de memória adequado para comportar o esperado de bytes de um struct Heap
    h->arr = calloc(range, sizeof(int));
    h->tail = -1;
    h->range = range;
    h->type = type;

    return h;
}

// func para exibir mais facilmente o Heap na tela
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

void swap_max_heap(Heap* h)
{
    size_t curr_idx = h->tail;
    int parent_idx = 0;
    int left_idx = 0;
    int right_idx = 0;
    bool swap = false;

    do
    {
        parent_idx = parent_node(curr_idx);
        if(parent_idx >= 0 & parent_idx <= h->tail)
        {
            left_idx = left_node(parent_idx);
            if(left_idx >= 0 & left_idx <= h->tail)
            {
                if(h->arr[left_idx] > h->arr[parent_idx])
                {
                    int temp_value = h->arr[parent_idx];

                    h->arr[parent_idx] = h->arr[left_idx];
                    h->arr[left_idx] = temp_value;

                    right_idx = right_node(parent_idx);
                    if(right_idx >= 0 & right_idx <= h->tail)
                    {
                        if(h->arr[right_idx] > h->arr[parent_idx])
                        {
                            temp_value = h->arr[parent_idx];

                            h->arr[parent_idx] = h->arr[right_idx];
                            h->arr[right_idx] = temp_value;
                        }
                    }
                }
            }

            curr_idx--;
        }
        else
        {
            swap = true;
        }
    } while (!swap);

    printf("swap_max_response: ok\n");
}

void swap_min_heap(Heap* h)
{
    printf("swap_min_response: ok\n");
}

void swap_heap(Heap* h)
{
    if(h->type)
    {
        swap_min_heap(h);
    }
    else
    {
        swap_max_heap(h);
    }
}

void insert_node(Heap* h, int node)
{
    if(h->tail + 1 >= h->range)
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
        h->arr[++h->tail] = node;
    }

    swap_heap(h);
}

void insert_arr(Heap* h, int *nodes, size_t len)
{
    for(size_t i = 0; i < len; ++i) {
        insert_node(h, nodes[i]);
    }
}

int main()
{
    Heap* h = init_heap(10, false);
    int nums[8] = {88, 87, 73, 47, 54, 6, 0, 43};
    int len_arr = sizeof(nums) / sizeof(int);
    insert_arr(h, nums, len_arr);
    print_heap(h);

    insert_node(h, 100);
    print_heap(h);
    return 0;
}