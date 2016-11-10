//
//  Dijkstra.h
//  Dijkstra
//
//  Created by Sang Gyeong Jo on 2016. 11. 9..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#ifndef Dijkstra_h
#define Dijkstra_h

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "Heap.h"

#define INF 4294967295

unsigned int **path_list;
unsigned int *min_set;
int *prev_set;
int *chk_set;

int path_size;

struct priority_queue *queue;

void make_heap(){
    
    queue = calloc(1,sizeof(struct priority_queue));
    
    queue->size = 0;
    
    queue->heap = calloc(0,sizeof(struct node));
    
}

void build_path()
{
    printf("Enter the number of nodes : ");
    scanf("%d",&path_size);
    
    path_list = calloc(path_size,sizeof(unsigned int*));
    printf("Enter the cost matrix\n");
    for (int i = 0; i < path_size ; i++)
    {
        path_list[i] = calloc(path_size,sizeof(unsigned int));
        for(int j = 0; j < path_size; j++)
        {
            scanf("%d ",&path_list[i][j]);
        }
    }
    min_set = calloc(path_size,sizeof(unsigned int));
    chk_set = calloc(path_size,sizeof(int));
    prev_set = calloc(path_size,sizeof(unsigned int));
}
int get_min_dist()
{
    int m = min_set[0];
    int r_i = 0;
    
    for(int i = 0; i<path_size; i++)
    {
        if(min_set[i] < m && !chk_set[i])
        {
            m = min_set[i];
            r_i = i;
        }
    }
    
    return r_i;
}

void dijkstra(int dst)
{
    for (int i = 0; i < path_size; i++)
    {
        min_set[i] = INF;
        chk_set[i] = 0;     //0 -> false, 1 -> true
    }
    
    min_set[dst] = 0;
    
    for (int i = 0; i < path_size-1; i++)
    {
        int u = get_min_dist();
        chk_set[u] = 1;
        
        for (int j = 0; j < path_size; j++)
        {
            if(min_set[u] + path_list[u][j] < min_set[j] && !chk_set[j] && path_list[u][j] && min_set[u] != INF)
                min_set[j] = min_set[u] + path_list[u][j];
        }
    }
    
}

struct node new_node(unsigned int i, unsigned int d, int p)
{
    struct node n;// = calloc(1, sizeof(struct node));
    n.d = d, n.i = i, n.p = p;
    
    return n;
}

void dijkstra_queue(int dst)
{
    min_set[dst] = 0;
    
    for (int i = 0; i < path_size; i++)
    {
        if( i != dst )
            min_set[i] = INF;
        
        insert(queue, new_node(i, min_set[i], -1)); //-1 is undefined
    }
    
    while(queue->size)
    {
        int u = extract_max(queue).i;
        
        for (int v = 0; v < queue->size; v++)
        {
            int v_i = queue->heap[v].i;
            if (path_list[u][v_i] != 0)
            {
                int a = min_set[u] + path_list[u][v_i];
                
                if( a < min_set[v_i] )
                {
                    min_set[v_i] = a;
                    change_key(queue, v_i, a, u);
                }
            }
        }
        //print_queue(queue);
        //printf("\n========\n");
    }
}

void print_set(){
    int dst;
    printf("Enter the source matrix : ");
    scanf("%d",&dst);
    printf("\n");
    dst--;
    make_heap();
    dijkstra(dst);
    for (int i = 0; i < path_size ; i++)
        if( i != dst )printf("%d -> %d, cost=%d\n",dst,i,min_set[i]);
    
    for (int i = 0; i < path_size ; i++)
             free(path_list[i]);
    free(path_list);
    free(min_set);
    free(chk_set);
}

void print_queue_set(){
    int dst;
    printf("Enter the source matrix : ");
    scanf("%d",&dst);
    printf("\n");
    dst--;
    make_heap();
    dijkstra_queue(dst);
    for (int i = 0; i < path_size ; i++)
        if( i != dst )printf("%d -> %d, cost=%u\n",dst,i,min_set[i]);
    
    for (int i = 0; i < path_size ; i++)
        free(path_list[i]);
    free(path_list);
    free(min_set);
    free(chk_set);
}


#endif /* Dijkstra_h */
