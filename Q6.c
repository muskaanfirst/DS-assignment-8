#include <stdio.h>
#include <stdlib.h>

typedef struct PriorityQueue {
    int *data;
    int capacity;
    int size;
    int is_max; 
} PriorityQueue;

PriorityQueue* pq_create(int capacity, int is_max) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity > 0 ? capacity : 16;
    pq->data = (int*)malloc(sizeof(int) * pq->capacity);
    pq->size = 0;
    pq->is_max = is_max ? 1 : 0;
    return pq;
}

void pq_free(PriorityQueue *pq) {
    if (!pq) return;
    free(pq->data);
    free(pq);
}

int compare(PriorityQueue *pq, int a, int b) {
    if (pq->is_max) return a > b;
    else return a < b;
}

void pq_swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void pq_resize_if_needed(PriorityQueue *pq) {
    if (pq->size < pq->capacity) return;
    pq->capacity *= 2;
    pq->data = (int*)realloc(pq->data, sizeof(int) * pq->capacity);
}

void pq_heapify_up(PriorityQueue *pq, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (compare(pq, pq->data[idx], pq->data[parent])) {
            pq_swap(&pq->data[idx], &pq->data[parent]);
            idx = parent;
        } else break;
    }
}

void pq_heapify_down(PriorityQueue *pq, int idx) {
    int n = pq->size;
    while (1) {
        int l = 2*idx + 1;
        int r = 2*idx + 2;
        int best = idx;
        if (l < n && compare(pq, pq->data[l], pq->data[best])) best = l;
        if (r < n && compare(pq, pq->data[r], pq->data[best])) best = r;
        if (best != idx) {
            pq_swap(&pq->data[idx], &pq->data[best]);
            idx = best;
        } else break;
    }
}

void pq_push(PriorityQueue *pq, int value) {
    pq_resize_if_needed(pq);
    pq->data[pq->size++] = value;
    pq_heapify_up(pq, pq->size - 1);
}

int pq_top(PriorityQueue *pq) {
    if (pq->size == 0) return 0;
    return pq->data[0];
}

int pq_pop(PriorityQueue *pq) {
    if (pq->size == 0) return 0;
    int top = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    pq_heapify_down(pq, 0);
    return top;
}

int pq_size(PriorityQueue *pq) {
    return pq->size;
}

int pq_empty(PriorityQueue *pq) {
    return pq->size == 0;
}

/* demo */
int main(void) {
    PriorityQueue *maxpq = pq_create(8, 1);
    pq_push(maxpq, 20);
    pq_push(maxpq, 5);
    pq_push(maxpq, 15);
    pq_push(maxpq, 30);
    pq_push(maxpq, 25);

    printf("Max-heap order popping: ");
    while (!pq_empty(maxpq)) {
        printf("%d ", pq_pop(maxpq));
    }
    printf("\n");
    pq_free(maxpq);

    PriorityQueue *minpq = pq_create(8, 0);
    pq_push(minpq, 20);
    pq_push(minpq, 5);
    pq_push(minpq, 15);
    pq_push(minpq, 30);
    pq_push(minpq, 25);

    printf("Min-heap order popping: ");
    while (!pq_empty(minpq)) {
        printf("%d ", pq_pop(minpq));
    }
    printf("\n");
    pq_free(minpq);

    return 0;
}
