//
//  Heap.h
//  maxHeap
//
//  Created by Sang-Gyueong Jo on 2016. 9. 27..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#ifndef Heap_h
#define Heap_h

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define PARENT(i)       (i - 1) / 2         //get node parent
#define LEFT_CHILD(i)   (i * 2) + 1         //get node left-child
#define RIGHT_CHILD(i)  (i * 2) + 2         //get node right-child

struct node {
    int d;
    int i;
    int p;
};

struct priority_queue {
    int size;
    struct node *heap;
};


void max_heapify(struct priority_queue *p_queue, int i);                 //Sort nodes of heap
void build_max_heap(struct priority_queue *p_queue);                     //Make heap to max-heap
struct priority_queue build_heap_data(FILE *fp);                        //Get heap data from file

int insert(struct priority_queue *p_queue, struct node x);               //Insert x to heap
struct node max(struct priority_queue *p_queue);                         //Find max element in heap
struct node extract(struct priority_queue *p_queue);                     //Remove max element in heap
struct node increase_key(struct priority_queue *p_queue, int x, int k);  //Increase value of x to k
struct node h_delete(struct priority_queue *p_queue, int x);             //Delete element x

void print_queue(struct priority_queue *p_queue);

void max_heapify(struct priority_queue *p_queue, int i){
    
    int L = LEFT_CHILD(i);
    int R = RIGHT_CHILD(i);
    int largest;
    
    if(L <= p_queue->size-1 && p_queue->heap[L].d < p_queue->heap[i].d) largest = L;
    else largest = i;
    
    if(R <= p_queue->size-1 && p_queue->heap[R].d < p_queue->heap[largest].d) largest = R;
    
    if(largest != i){
        struct node temp = p_queue->heap[i];
        p_queue->heap[i] = p_queue->heap[largest];
        p_queue->heap[largest] = temp;
        max_heapify(p_queue, largest);
    }
}

void build_max_heap(struct priority_queue *p_queue){
    int i = 0;
    for(i = (p_queue->size-1)/2; i>=0 ; i--){
        max_heapify(p_queue, i);
    }
}

int insert(struct priority_queue *p_queue, struct node x){
    
    struct node *temp;
    temp = realloc(p_queue->heap, (p_queue->size + 1) * sizeof(struct node));
    p_queue->heap = temp;
    p_queue->heap[p_queue->size] = x;
    p_queue->size++;
    
    build_max_heap(p_queue);
    
    return 1;
}

struct node max(struct priority_queue *p_queue){

    return p_queue->heap[0];
    
}

struct node extract_max(struct priority_queue *p_queue){
    
    struct node max = p_queue->heap[0];
    
    memmove(p_queue->heap, p_queue->heap+1, (p_queue->size) * sizeof(struct node));
    
    struct node *temp;
    temp = realloc(p_queue->heap, (p_queue->size) * sizeof(struct node));
    p_queue->heap = temp;
    p_queue->size--;
    
    build_max_heap(p_queue);
    
    return max;
    
}

struct node increase_key(struct priority_queue *p_queue, int x, int k){
    
    int i = 0;
    int chk = 0;
    
    /* bfs */
    for(i = 0; i<p_queue->size; i++){
        if(p_queue->heap[i].d == x){
            p_queue->heap[i].d += k;
            chk = 1;
            break;
        }
    }
    
    if(chk == 0){
        struct node d_node;
        d_node.d = -1;
        d_node.i = 0;
        d_node.p = 0;
        return d_node;
    }
    
    
    build_max_heap(p_queue);
    
    return p_queue->heap[i];
    
}

struct node decrease_key(struct priority_queue *p_queue, int x, int k){
    
    int i = 0;
    int chk = 0;
    
    /* bfs */
    for(i = 0; i<p_queue->size; i++){
        if(p_queue->heap[i].i == x){
            p_queue->heap[i].d -= k;
            chk = 1;
            break;
        }
    }
    
    if(chk == 0){
        struct node d_node;
        d_node.d = -1;
        d_node.i = 0;
        d_node.p = 0;
        return d_node;
    }
    
    
    build_max_heap(p_queue);
    
    return p_queue->heap[i];
    
}

struct node h_delete(struct priority_queue *p_queue, int x){
    
    int i = 0;
    int chk = 0;
    
    for (i = 0; i<p_queue->size; i++) if (p_queue->heap[i].d == x) {chk=1; break;}
    
    if(chk == 0){
        struct node d_node;
        d_node.d = -1;
        d_node.i = 0;
        d_node.p = 0;
        return d_node;
    }
    
    struct node d_node = p_queue->heap[i];
    
    memmove(p_queue->heap+i, p_queue->heap+i+1, (p_queue->size-i) * sizeof(struct node));
    
    struct node *temp;
    temp = realloc(p_queue->heap, (p_queue->size) * sizeof(struct node));
    p_queue->heap = temp;
    p_queue->size--;
    
    build_max_heap(p_queue);
    
    return d_node;
    
}

void print_queue(struct priority_queue *queue){
    
    for(int i=0; i<queue->size; i++) printf("%d, %d, %d\n",queue->heap[i].i,queue->heap[i].d,queue->heap[i].p);
    
}


#endif /* Heap_h */
