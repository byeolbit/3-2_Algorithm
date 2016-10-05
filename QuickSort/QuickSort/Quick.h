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
int *quick_sort(int *data_set, int f, int k);

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
    
    return data_set;
}

int partition(int *data_set, int f, int l)
{
    int x = data_set[l];
    int i = f-1;
    int j = f;
    
    for(j=f; j+1 != i; j++)
    {
        if(data_set[j]<=x)
        {
            int swap_temp = data_set[++i];
            data_set[i] = data_set[j];
            data_set[j] = swap_temp;
        }
        int swap_temp = data_set[++i];
        data_set[i] = data_set[l];
        data_set[l] = swap_temp;
    }
    return i;
}

int randomized_partition(int *data_set, int f, int l){
    
    return partition(data_set, f, l);
}

int *quick_sort(int *data_set, int f, int k)
{
    if (f<k)
    {
        int q = partition(data_set, f, k);
        quick_sort(data_set, q, q-1);
        quick_sort(data_set, q+1, k);
    }
    return data_set;
}



#endif /* Quick_h */
