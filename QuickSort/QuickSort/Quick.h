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

int *build_dataset(FILE *fp);
int partition(int *data_set, int f, int l);
int randomized_partition(int *data_set, int f, int l);
void quick_sort(int *data_set, int f, int k);
int size_of_dataset;

int *build_dataset(FILE *fp)
{
    int *data_set;
    int read_count = 0;
    
    data_set = calloc(1, sizeof(int));
    
    while(!feof(fp))
    {
        int *temp_data_set;
        
        temp_data_set = realloc(data_set, (++read_count)*sizeof(int));
        data_set = temp_data_set;
        
        fscanf(fp,"%d,",&data_set[read_count-1]);
    }
    fclose(fp);
    
    size_of_dataset = read_count;
    
    return data_set;
}

int partition(int *data_set, int f, int l)
{
    int x = data_set[l];
    int i = f-1;
    
    for(int j=f; j<l; j++)
    {
        if(data_set[j]<=x)
        {
            swap_int_arr(data_set, ++i, j);
        }
    }
    swap_int_arr(data_set, ++i, l);
    return i;
}

int randomized_partition(int *data_set, int f, int l)
{
    int i = get_random(f, l);
    swap_int_arr(data_set, l, i);
    return partition(data_set, f, l);
}

void quick_sort(int *data_set, int f, int k)
{
    if (f<k)
    {
        int q = partition(data_set, f, k);
        quick_sort(data_set, f, q-1);
        quick_sort(data_set, q+1, k);
    }
}

void quick_sort_randomized(int *data_set, int f, int k)
{
    if (f<k)
    {
        int q = randomized_partition(data_set, f, k);
        quick_sort_randomized(data_set, f, q-1);
        quick_sort_randomized(data_set, q+1, k);
    }
}



#endif /* Quick_h */
