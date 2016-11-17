//
//  MinPriorityQueue.h
//  minHeap
//
//  Created by Sang-Gyueong Jo on 2016. 9. 27..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//
//  MinPrioirtyQueue로 수정됨 - 2016.11.16
//

#ifndef MinPriorityQueue_h
#define MinPriorityQueue_h

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define PARENT(i)       (i - 1) / 2         //get node parent
#define LEFT_CHILD(i)   (i * 2) + 1         //get node left-child
#define RIGHT_CHILD(i)  (i * 2) + 2         //get node right-child

struct node {
    unsigned int freq;
    int is_leaf;
    char c;
    char vcwd[256];
    struct node *left;
    struct node *right;
};

struct priority_queue {
    int size;
    struct node **heap;
};

typedef struct node *node;

void min_heapify(struct priority_queue *p_queue, int i);                 //Sort nodes of heap
void build_min_heap(struct priority_queue *p_queue);                     //Make heap to max-heap
struct priority_queue build_heap_data(FILE *fp);                        //Get heap data from file

int insert(struct priority_queue *p_queue, node x);               //Insert x to heap
node min(struct priority_queue *p_queue);                         //Find max element in heap
node extract(struct priority_queue *p_queue);                     //Remove max element in heap
int increase_key(struct priority_queue *p_queue, char x, int k);  //Increase value of x to k
int h_delete(struct priority_queue *p_queue, char x);             //Delete element x

void print_queue(struct priority_queue *p_queue);

void min_heapify(struct priority_queue *p_queue, int i){
    
    int L = LEFT_CHILD(i);
    int R = RIGHT_CHILD(i);
    int largest;
    
    if(L <= p_queue->size-1 && p_queue->heap[L]->freq < p_queue->heap[i]->freq) largest = L;
    else largest = i;
    
    if(R <= p_queue->size-1 && p_queue->heap[R]->freq < p_queue->heap[largest]->freq) largest = R;
    
    if(largest != i){
        node temp = p_queue->heap[i];
        p_queue->heap[i] = p_queue->heap[largest];
        p_queue->heap[largest] = temp;
        min_heapify(p_queue, largest);
    }
}

void build_min_heap(struct priority_queue *p_queue){
    for(int i = (p_queue->size-1)/2; i>=0 ; i--){
        min_heapify(p_queue, i);
    }
}

int insert(struct priority_queue *p_queue, node x){
    
    node *temp;
    temp = realloc(p_queue->heap, (p_queue->size + 1) * sizeof(node));
    p_queue->heap = temp;
    p_queue->heap[p_queue->size] = x;
    p_queue->size++;
    
    build_min_heap(p_queue);
    
    return 1;
}

node min(struct priority_queue *p_queue){

    return p_queue->heap[0];
    
}

node extract_min(struct priority_queue *p_queue){
    
    node min = p_queue->heap[0];
    
    memmove(p_queue->heap, p_queue->heap+1, (p_queue->size) * sizeof(node));
    
    node *temp;
    temp = realloc(p_queue->heap, (p_queue->size) * sizeof(node));
    p_queue->heap = temp;
    p_queue->size--;
    
    build_min_heap(p_queue);
    
    return min;
    
}

int change_key(struct priority_queue *p_queue, char x, int k){
    
    int i = 0;
    int chk = 0;
    
    /* bfs */
    for(i = 0; i<p_queue->size; i++){
        if(p_queue->heap[i]->c == x){
            p_queue->heap[i]->freq = k;
            
            chk = 1;
            break;
        }
    }
    
    if(chk == 0){
        return 0;
    }
    
    
    build_min_heap(p_queue);
    
    return 1;
    
}

int increase_key(struct priority_queue *p_queue, char x, int k){
    
    int i = 0;
    int chk = 0;
    
    /* bfs */
    for(i = 0; i<p_queue->size; i++){
        if(p_queue->heap[i]->c == x){
            p_queue->heap[i]->freq += k;
            chk = 1;
            break;
        }
    }
    
    if(chk == 0){
        return 0;
    }
    
    
    build_min_heap(p_queue);
    
    return 1;
    
}

node decrease_key(struct priority_queue *p_queue, char x, int k){
    
    int i = 0;
    int chk = 0;
    
    /* bfs */
    for(i = 0; i<p_queue->size; i++){
        if(p_queue->heap[i]->c == x){
            p_queue->heap[i]->freq -= k;
            chk = 1;
            break;
        }
    }
    
    if(chk == 0){
        node d_node;
        d_node->freq = -1;
        d_node->c = 0;
        return d_node;
    }
    
    
    build_min_heap(p_queue);
    
    return p_queue->heap[i];
    
}

int h_delete(struct priority_queue *p_queue, char x){
    
    int i = 0;
    int chk = 0;
    
    for (i = 0; i<p_queue->size; i++) if (p_queue->heap[i]->freq == x) {chk=1; break;}
    
    if(chk == 0){
        return 0;
    }
    
    memmove(p_queue->heap+i, p_queue->heap+i+1, (p_queue->size-i) * sizeof(node));
    
    node *temp;
    temp = realloc(p_queue->heap, (p_queue->size) * sizeof(node));
    p_queue->heap = temp;
    p_queue->size--;
    
    build_min_heap(p_queue);
    
    return 1;
    
}

void print_queue(struct priority_queue *queue){
    
    for(int i=0; i<queue->size; i++) printf("%c, %5u\n",queue->heap[i]->c,queue->heap[i]->freq);
    
}


#endif /* MinPriorityQueue_h */
