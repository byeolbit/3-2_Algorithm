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
#include "Essential.h"

#define PARENT(i)       (i - 1) / 2         //get node parent
#define LEFT_CHILD(i)   (i * 2) + 1         //get node left-child
#define RIGHT_CHILD(i)  (i * 2) + 2         //get node right-child

struct node {
    int key;
    char *value;
};

struct priority_queue {
    int size;
    struct node *heap;
};


void max_heapify(struct priority_queue p_queue, int i);                 //Sort nodes of heap
void build_max_heap(struct priority_queue p_queue);                     //Make heap to max-heap
struct priority_queue build_heap_data(FILE *fp);                        //Get heap data from file

int insert(struct priority_queue p_queue, struct node x);               //Insert x to heap
struct node max(struct priority_queue p_queue);                         //Find max element in heap
struct node extract(struct priority_queue p_queue);                     //Remove max element in heap
struct node increase_key(struct priority_queue p_queue, int x, int k);  //Increase value of x to k
struct node h_delete(struct priority_queue p_queue, int x);             //Delete element x

void print_queue(struct priority_queue p_queue);

void max_heapify(struct priority_queue p_queue, int i){
    
    int L = LEFT_CHILD(i);
    int R = RIGHT_CHILD(i);
    int largest;
    
    if(L <= p_queue.size-1 && p_queue.heap[L].key > p_queue.heap[i].key) largest = L;
    else largest = i;
    
    if(R <= p_queue.size-1 && p_queue.heap[R].key > p_queue.heap[largest].key) largest = R;
    
    if(largest != i){
        struct node temp = p_queue.heap[i];
        p_queue.heap[i] = p_queue.heap[largest];
        p_queue.heap[largest] = temp;
        max_heapify(p_queue, largest);
    }
}

void build_max_heap(struct priority_queue p_queue){
    int i = 0;
    for(i = (p_queue.size-1)/2; i>=0 ; i--){
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
        
        size_t len = 0;
        ssize_t read;
        
        fscanf(fp, "%d, ",&new_queue.heap[new_queue.size].key);
        new_queue.heap[new_queue.size].value = NULL;
        read = getline(&new_queue.heap[new_queue.size].value,&len,fp);
        
        new_queue.heap[new_queue.size].value = strtok(new_queue.heap[new_queue.size].value,"\n");
        
        new_queue.size++;
    }
    
    fclose(fp);
    
    return new_queue;
};

int insert(struct priority_queue p_queue, struct node x){
    
    struct node *temp;
    temp = realloc(p_queue.heap, (p_queue.size + 1) * sizeof(struct node));
    p_queue.heap[p_queue.size] = x;
    p_queue.size++;
    
    max_heapify(p_queue, p_queue.size-1);
    
    return 1;
}

struct node max(struct priority_queue p_queue){

    return p_queue.heap[0];
    
}

struct node extract_max(struct priority_queue p_queue){
    
    struct node max = p_queue.heap[0];
    
    memmove(p_queue.heap+1, p_queue.heap, (p_queue.size) * sizeof(struct node));
    
    struct node *temp;
    temp = realloc(p_queue.heap, (p_queue.size) * sizeof(struct node));
    p_queue.heap = temp;
    p_queue.size--;
    
    return max;
    
}

struct node increase_key(struct priority_queue p_queue, int x, int k){
    
    int i = 0;
    
    /* bfs */
    for(i = 0; i<p_queue.size; i++){
        if(p_queue.heap[i].key == x){
            p_queue.heap[i].key = k;
            break;
        }
    }
    
    build_max_heap(p_queue);
    
    return p_queue.heap[i];
    
}

struct node h_delete(struct priority_queue p_queue, int x){
    
    int i = 0;
    
    for (i = 0; i<p_queue.size; i++) if (p_queue.heap[i].key == x) break;
    
    struct node d_node = p_queue.heap[i];
    
    memmove(p_queue.heap+i+1, p_queue.heap+i, (p_queue.size-i) * sizeof(struct node));
    
    struct node *temp;
    temp = realloc(p_queue.heap, (p_queue.size) * sizeof(struct node));
    p_queue.heap = temp;
    p_queue.size--;
    
    build_max_heap(p_queue);
    
    return d_node;
    
}

void print_queue(struct priority_queue p_queue){
    
    int i = 0;
    
    printf("**** 현재 우선 순위 큐에 저장되어 있는 작업 대기 목록은 다음과 같습니다 ****\n\n");
    for(i=0; i<p_queue.size; i++) printf("%3d, %s\n",p_queue.heap[i].key,p_queue.heap[i].value);
    printf("\n--------------------------------------------------------\n");
    printf("1. 작업 추가\t\t2. 최대값\t\t3. 최대 우선순위 작업 처리\n");
    printf("4. 원소 키값 증가\t5. 작업제거\t6. 종료\n");
    printf("--------------------------------------------------------\n");
    
}


#endif /* Heap_h */
