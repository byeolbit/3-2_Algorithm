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
    struct node *array;
};


void max_heapify(struct priority_queue p_queue, int i);
void build_max_heap(struct priority_queue p_queue);

int *insert(int *heap, struct node x);      //Insert x to heap
int *max(int *heap);                        //Find max element in heap
int *extract(int *heap);                    //Remove max element in heap
int increase_key(int *heap, int x, int k);  //Increase value of x to k
int h_delete(int *heap, int x);             //Delete element x

void max_heapify(struct priority_queue p_queue, int i){
    
    int L = LEFT_CHILD(i);
    int R = RIGHT_CHILD(i);
    int largest;
    
    
    if(L <= p_queue.size && p_queue.array[L].key > p_queue.array[i].key) largest = L;
    else largest = i;
    
    if(R <= p_queue.size && p_queue.array[R].key > p_queue.array[largest].key) largest = R;
    
    if(largest != i){
        struct node temp = p_queue.array[i];
        p_queue.array[i] = p_queue.array[largest];
        p_queue.array[largest] = temp;
        
        max_heapify(p_queue, largest);
    }
    
}

void build_max_heap(struct priority_queue p_queue){
    int heap_size = p_queue.size;
    for(int i = p_queue.size/2; i>0 ;){
        max_heapify(p_queue, i);
    }
}



#endif /* Heap_h */
