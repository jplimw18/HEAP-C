#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// retorna o índice do nó a direita
int node_left(size_t idx)
{
    return (int)(2 * idx + 1);
}

// retorna o índice do nó a direita
int node_right(size_t idx)
{
    return (int)(2 * (idx + 1));
}

// retorna o índice do nó pai
int node_parent(size_t idx)
{
    return (int)((idx - 1) / 2);
} 

// definindo a estrutura do heap
typedef struct {
    int *arr;
    int tail;
    size_t range;
    bool type; // false to max true to min
} Heap;

// iniciador dos valores do heap
Heap* init_heap(size_t range, bool type)
{
    Heap* heap = malloc(sizeof(Heap));
    heap->arr = calloc(range, sizeof(int));
    heap->tail = -1;
    heap->range = range;
    heap->type = type;
    return heap;
}

// saída visual dosvalores do heap
void print_heap(Heap* heap)
{
    for(size_t i = 0; i < heap->range; ++i) {
        if(i > heap->tail | heap->tail == -1){
            printf("campo nulo: ");
        }
        else
        {
            printf("campo ok: ");
        }

        printf("%d\n", heap->arr[i]);
    }
    printf("tail = %d\n", heap->tail);
    printf("range = %d\n", heap->range);
}

// realoca o espaço de memória do heap
void realloc_heap(Heap* heap)
{
    size_t new_range = heap->range + 2; 
    int *new_arr = realloc(heap->arr, new_range * sizeof(int));
    memset(new_arr + heap->range, 0, (new_range - heap->range) * sizeof(int));

    heap->arr = new_arr;
    heap->range = new_range;
}

//func para ajuste do heap tipo max de acordo com a propriedade 1
void max_heapify(Heap* heap)
{
    
}

// func para organizar o heap do tipo max de acordo com a propriedade - 1
void swap_max_heap(Heap* heap)
{
    bool turn = false;
    size_t tail = heap->tail;
    size_t idx = heap->tail;

    int parent_idx = 0;
    int left_idx = 0;
    int right_idx = 0;

    int val_parent = 0;
    int val_left = 0;
    int val_right = 0;

    while(!turn) {
        parent_idx = node_parent(idx);

        if(parent_idx >= 0 & parent_idx <= tail)
        {
            val_parent = heap->arr[parent_idx];
            left_idx = node_left(parent_idx);
            right_idx = node_right(parent_idx);

            if(left_idx >= 0 & left_idx <= tail) 
            {
                val_left = heap->arr[left_idx];

                if(val_left > val_parent)
                {
                    heap->arr[parent_idx] = val_left;
                    heap->arr[left_idx] = val_parent;

                    val_parent = heap->arr[parent_idx];
                    val_left = heap->arr[left_idx];
                }

                if(right_idx >= 0 & right_idx <= tail)
                {
                    val_right = heap->arr[right_idx];

                    if(val_right > val_parent)
                    {
                        heap->arr[parent_idx] = val_right;
                        heap->arr[right_idx] = val_parent;

                        val_parent = heap->arr[parent_idx];
                        val_right = heap->arr[right_idx];
                    }
                }
            }
        }
        else
        {
            printf("swap_max_response: ok\n");
            turn = true;
        }

        idx--;
    }
}

// inserindo nós no heap
void insert_node(Heap* heap, int val)
{   
    if(heap->tail >= (int)heap->range)
    {
        realloc_heap(heap);
    }

    heap->arr[++heap->tail] = val;
    swap_max_heap(heap);
}

// func para adicionar valores via vetor 
void add_arr(Heap* heap, int *arr, size_t arr_count)
{
    for(size_t i = 0; i < arr_count; ++i) {
        insert_node(heap, arr[i]);
    }

    swap_max_heap(heap);
}

void remove_node(Heap* heap)
{
    int remove_val = heap->arr[0];
    int last_val = heap->arr[heap->tail];

    heap->arr[0] = last_val;
    heap->arr[heap->tail] = remove_val;

    heap->tail -= 1;

    // print_heap(heap);
    max_heapfy(heap);
}

// void swap_min_heap(Heap* heap)
// {

// }

int main(void)
{
    int arr[8] = {88, 87, 73, 47, 54, 6, 0, 43};
    size_t count = sizeof(arr) / sizeof(arr[0]);
    Heap* heap = init_heap(10, false);
    add_arr(heap, arr, count);
    print_heap(heap);

    printf("------------\n");

    insert_node(heap, 100);
    print_heap(heap);

    printf("------------\n");

    insert_node(heap, 90);
    print_heap(heap);

    printf("------------\n");

    remove_node(heap);
    print_heap(heap);
    return 0;
}