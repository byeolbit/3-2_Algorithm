//
//  PrimMST.h
//  SpanningTree
//
//  Created by Sang Gyeong Jo on 2016. 11. 16..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#ifndef PrimMST_h
#define PrimMST_h

#include "MinPriorityQueue.h"

#define INF 4294967295
#define BF 0
#define BT 1

unsigned int **path_cost;
unsigned int *min_cost;
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
    
    path_cost = calloc(path_size,sizeof(unsigned int*));
    printf("Enter the cost matrix\n");
    for (int i = 0; i < path_size ; i++)
    {
        path_cost[i] = calloc(path_size,sizeof(unsigned int));
        for(int j = 0; j < path_size; j++)
        {
            scanf("%d ",&path_cost[i][j]);
        }
    }
    min_cost = calloc(path_size,sizeof(unsigned int));
    chk_set = calloc(path_size,sizeof(int));
    prev_set = calloc(path_size,sizeof(unsigned int));
}

node new_node(int i, unsigned int d, int p)
{
    node n;// = calloc(1, sizeof(struct node));
    n.d = d, n.i = i, n.p = p;
    
    return n;
}

void build_path_static()
{
    path_size = 9;
    path_cost = calloc(path_size,sizeof(unsigned int*));
    for (int i = 0; i < path_size ; i++)
    {
        path_cost[i] = calloc(path_size,sizeof(unsigned int));
        for(int j = 0; j < path_size; j++)
        {
            path_cost[i][j] = 0;
        }
    }
    
    path_cost[0][0] = 0;
    path_cost[0][1] = 4;
    path_cost[0][7] = 8;
    path_cost[1][0] = 4;
    path_cost[1][1] = 0;
    path_cost[1][2] = 8;
    path_cost[1][7] = 11;
    path_cost[2][1] = 8;
    path_cost[2][3] = 7;
    path_cost[2][2] = 0;
    path_cost[2][5] = 4;
    path_cost[2][8] = 2;
    path_cost[3][2] = 7;
    path_cost[3][3] = 0;
    path_cost[3][4] = 9;
    path_cost[3][5] = 14;
    path_cost[4][3] = 9;
    path_cost[4][4] = 0;
    path_cost[4][5] = 10;
    path_cost[5][2] = 4;
    path_cost[5][3] = 14;
    path_cost[5][4] = 10;
    path_cost[5][5] = 0;
    path_cost[5][6] = 2;
    path_cost[6][5] = 2;
    path_cost[6][6] = 0;
    path_cost[6][7] = 1;
    path_cost[6][8] = 6;
    path_cost[7][0] = 8;
    path_cost[7][1] = 11;
    path_cost[7][6] = 1;
    path_cost[7][7] = 0;
    path_cost[7][8] = 7;
    path_cost[8][2] = 2;
    path_cost[8][6] = 6;
    path_cost[8][7] = 7;
    path_cost[8][8] = 0;
    
    min_cost = calloc(path_size,sizeof(unsigned int));
    chk_set = calloc(path_size,sizeof(int));
    prev_set = calloc(path_size,sizeof(unsigned int));
    
    for (int i = 0; i < path_size ; i++) chk_set[i] = BF;
    
    /*
    for (int i = 0; i < path_size ; i++)
    {
        for(int j = 0; j < path_size; j++)
        {
            printf("%3d ",path_cost[i][j]);
        }
        printf("\n");
    }
    */
}

int get_min_dist()
{
    int m = min_cost[0];
    int r_i = 0;
    
    for(int i = 0; i<path_size; i++)
    {
        if(min_cost[i] < m && !chk_set[i])
        {
            m = min_cost[i];
            r_i = i;
        }
    }
    
    return r_i;
}

void prim(int dst)
{
    make_heap();
    
    chk_set[dst] = BT;
    min_cost[dst] = 0;
    for (int i = 0; i < path_size; i++)
    {
        prev_set[i] = -1;
        if (i != dst && path_cost[dst][i] != 0)
        {
            prev_set[i] = dst;
            insert(queue, new_node(i, path_cost[dst][i], dst));
        }
    }
    prev_set[dst] = dst;
    
    //print_queue(queue);
    //printf("\n========\n");
    
    printf("w<%c,%c> = %d\n",prev_set[dst]+'a',dst+'a',min_cost[dst]);
    while(queue->size)
    {
        node e = extract_min(queue); //actually extract min
        int u = e.i;
        
        if (!chk_set[u])
        {
            chk_set[u] = BT;
            min_cost[u] = e.d;
            
            printf("w<%c,%c> = %d\n",prev_set[u]+'a',u+'a',min_cost[u]);
            
            for (int i = 0; i < path_size; i++)
            {
                if (i != dst &&i != u && path_cost[u][i] != 0)
                {
                    prev_set[i] = u;
                    insert(queue, new_node(i, path_cost[u][i], u));
                }
            }
        }
        
        //print_queue(queue);
        //printf("\n========\n");
    }
    int t = 0;
    for (int i = 0; i < path_size; i++) t += min_cost[i];
    printf("\nw<MST> = %d\n",t);
}

#endif /* PrimMST_h */
