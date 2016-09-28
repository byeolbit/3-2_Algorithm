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
#include "Essential.h"

#define PARENT(i)       i / 2       //get node parent
#define LEFT_CHILD(i)   i * 2       //get node left-child
#define RIGHT_CHILD(i)  i * 2 + 1   //get node right-child

struct node {
    int key;
    char *value;
};

struct priority_queue {
    int size;
    struct node *heap;
};


void max_heapify(struct priority_queue p_queue, int i);         //Sort nodes of heap
void build_max_heap(struct priority_queue p_queue);             //Make heap to max-heap
struct priority_queue build_heap_data(FILE *fp);                //Get heap data from file

int insert(struct priority_queue p_queue, struct node x);       //Insert x to heap
int *max(struct priority_queue p_queue);                        //Find max element in heap
int *extract(struct priority_queue p_queue);                    //Remove max element in heap
int increase_key(struct priority_queue p_queue, int x, int k);  //Increase value of x to k
int h_delete(struct priority_queue p_queue, int x);             //Delete element x

void max_heapify(struct priority_queue p_queue, int i){
    
    int L = LEFT_CHILD(i);
    int R = RIGHT_CHILD(i);
    int largest;
    
    if(L <= p_queue.size && p_queue.heap[L].key > p_queue.heap[i].key) largest = L;
    else largest = i;
    
    if(R <= p_queue.size && p_queue.heap[R].key > p_queue.heap[largest].key) largest = R;
    
    if(largest != i){
        struct node temp = p_queue.heap[i];
        p_queue.heap[i] = p_queue.heap[largest];
        p_queue.heap[largest] = temp;
        max_heapify(p_queue, largest);
    }
}

void build_max_heap(struct priority_queue p_queue){
    int i = 0;
    for(i = p_queue.size/2; i>0 ; i--){
        max_heapify(p_queue, i);
    }
}

struct priority_queue build_heap_data(FILE *fp) {
    
    /* Init queue */
    struct priority_queue new_queue;
    new_queue.size = 0;
    
    while(!feof(fp)){
        if(new_queue.size == 0){
            new_queue.heap = calloc(1,sizeof(struct node));
        } else {
            struct node *temp;
            temp = realloc(new_queue.heap, (new_queue.size + 1) * sizeof(struct node));
            new_queue.heap = temp;
        }
        fscanf(fp, "%d, %s",&new_queue.heap[new_queue.size].key, new_queue.heap[new_queue.size].value);
        new_queue.size++;
    }
    
    return new_queue;
};

int insert(struct priority_queue p_queue, struct node x){
    
    struct node *temp;
    temp = realloc(p_queue.heap, (p_queue.size + 1) * sizeof(struct node));
    p_queue.heap[p_queue.size] = x;
    p_queue.size++;
    
    max_heapify(p_queue, p_queue.size);
    
    return 1;
}



#endif /* Heap_h */
