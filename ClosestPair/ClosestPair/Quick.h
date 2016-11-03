//
//  Quick.h
//  QuickSort
//
//  Created by Sang Gyeong Jo on 2016. 10. 3..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#ifndef Quick_h
#define Quick_h

#include "Essential.h"


struct point
{
    double x,y;
};

typedef struct point point;

struct point_set
{
    int size;
    point *data;
};

typedef struct point_set point_s;


int partition(point *data_set, int f, int l);
int randomized_partition(point *data_set, int f, int l);
void quick_sort(point *data_set, int f, int k);
int size_of_dataset;
void swap_arr(point *arr, int a, int b)
{
    point t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}


int partition(point *data_set, int f, int l)
{
    double x = data_set[l].x;
    int i = f-1;
    
    for(int j=f; j<l; j++)
    {
        if(data_set[j].x<=x)
        {
            swap_arr(data_set, ++i, j);
        }
    }
    swap_arr(data_set, ++i, l);
    return i;
}

int randomized_partition(point *data_set, int f, int l)
{
    int i = get_random(f, l);
    swap_arr(data_set, l, i);
    return partition(data_set, f, l);
}

void quick_sort(point *data_set, int f, int k)
{
    if (f<k)
    {
        int q = partition(data_set, f, k);
        quick_sort(data_set, f, q-1);
        quick_sort(data_set, q+1, k);
    }
}

void quick_sort_randomized(point *data_set, int f, int k)
{
    if (f<k)
    {
        int q = randomized_partition(data_set, f, k);
        quick_sort_randomized(data_set, f, q-1);
        quick_sort_randomized(data_set, q+1, k);
    }
}



#endif /* Quick_h */
