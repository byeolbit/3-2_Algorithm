//
//  SortingAlgorithm.h
//  Insertion&Merge
//
//  Created by Sang Gyeong Jo on 2016. 10. 12..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#ifndef SortingAlgorithm_h
#define SortingAlgorithm_h

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <memory.h>

/* Binary Search */
#define BS(type) \
    int binary_search_##type(type *array, type target, size_t size) \
    { \
    int low, high, mid; \
    low = 0; \
    mid = 0; \
    high = size-1; \
        while(low <= high) \
        { \
            mid = low + (high-low) / 2; \
            if (array[mid] > target) high = mid -1; \
            else if (array[mid] < target) low = mid +1; \
            else return mid; \
        } \
        return low-1; \
    } \


#define UBS(type) \
    int binary_search_unsigend_##type(unsigned type *array, unsigned type target, size_t size) \
    { \
        int low, high, mid; \
        low = 0; \
        mid = 0; \
        high = size-1; \
        while(low <= high) \
        { \
            mid = low + (high-low) / 2; \
            if (array[mid] > target) high = mid -1; \
            else if (array[mid] < target) low = mid +1; \
            else return mid; \
        } \
        return low-1; \
    } \

BS(int)
BS(long)
BS(double)
UBS(int)
UBS(long)

/**********************************************
 *
 *           Binary insertion Sort
 *
 **********************************************/

#define BIS(type) \
    int *binary_insertion_sort_##type(type *data_set, size_t size) \
    { \
        int i; \
        type key; \
        for (i=1; i<size; i++) \
        { \
            key = data_set[i]; \
            int target = binary_search_##type(data_set, key, i); \
            memmove(data_set+target+1, data_set+target, sizeof(type)*(i-target)); \
            data_set[target] = key; \
        } \
        return data_set; \
    } \


/* Swap */
void swap_int_arr(int *arr, int a, int b);

/* Random */
int get_random(int s, int e);


/* Sorting */

//Merge
int *merge(int *arr1, int *arr2, int size_a, int size_b);
int *merge_sort(int *data_set, int size);
int *three_way_merge(int *arr1, int *arr2, int *arr3, int size_a, int size_b, int size_c);
int *three_way_merge_sort(int *data_set, int size);

//Insertion
int *insertion_sort(int *data_set, int size);
int *binary_insertion_sort(int *data_set, int size);

//Quick
int partition(int *data_set, int f, int l);
int randomized_partition(int *data_set, int f, int l);
void quick_sort(int *data_set, int f, int k);


/* Random */
// get random integer number between s and e(s <= x <= e)
int get_random(int s, int e)
{
    srand((unsigned)time(NULL)+(unsigned)getpid());
    return (rand() % (e-s+1)) + s;
}

/* Swap */
// swap two element from int array
void swap_int_arr(int *arr, int a, int b)
{
    int t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}

/* Sorting */

int min(int a, int b, int c)
{
    int min = 0;
    
    if(a < b) min = a;
    else min = b;
    
    if(min > c) return c;
    else return min;
}

/**********************************************
 *
 *              Insertion Sort
 *
 **********************************************/



int *insertion_sort(int *data_set, int size)
{
    int i,j,key;
    
    for (j=1; j<size; j++)
    {
        key = data_set[j];
        i = j-1;
        while(i>=0 && data_set[i]>key){
            data_set[i+1] = data_set[i];
            --i;
        }
        data_set[i+1] = key;
    }
    return data_set;
}

/**********************************************
 *
 *                  Merge Sort
 *
 **********************************************/

void sort_extra(int **merged_arr_p, int *i_p, int total_size, int *k_p, int *arr2, int *j_p, int *arr1, int size_b, int size_a)
{
    while(*i_p <= total_size)
    {
        if (*j_p == size_a)     // end of part_a
        {
            (*merged_arr_p)[(*i_p)] = arr2[(*k_p)];     // put b
            ++(*k_p);
        } else if (*k_p == size_b) {                    // end of part_b
            (*merged_arr_p)[(*i_p)] = arr1[(*j_p)];     // put a
            ++(*j_p);
        } else {
            if (arr1[(*j_p)] < arr2[(*k_p)]) {
                (*merged_arr_p)[(*i_p)] = arr1[(*j_p)];
                ++(*j_p);
            } else {
                (*merged_arr_p)[(*i_p)] = arr2[(*k_p)];
                ++(*k_p);
            }
        }
        
        if(++(*i_p) != total_size)
        {
            int *temp = realloc(*merged_arr_p, sizeof(int) *(*i_p+1));    //increase array size
            *merged_arr_p = temp;
        } else break;
    }
}

int *merge(int *arr1, int *arr2, int size_a, int size_b)
{
    int *merged_arr = (int*) calloc(1,sizeof(int));
    
    int i,j,k;
    
    i = 0;
    j = 0;
    k = 0;
    
    sort_extra(&merged_arr, &i, size_a+size_b, &k, arr2, &j, arr1, size_b, size_a);
    
    free(arr1);     //avoid memory leak
    free(arr2);     //avoid memory leak
    
    return merged_arr;
}

int *merge_sort(int *data_set, int size)
{
    if(size == 1) return data_set;  //end of depth
    
    int size_a = size/2;
    int size_b = size - size_a;
    
    int *part_a = (int*)calloc(size_a, sizeof(int));
    int *part_b = (int*)calloc(size_b, sizeof(int));
    
    memmove(part_a, data_set, sizeof(int)*size_a);
    memmove(part_b, data_set + size_a, sizeof(int)*size_b);
    
    free(data_set);     //avoid memory leak
    
    if (size == 2) return merge(part_a, part_b, size_a, size_b);
    
    else return merge(merge_sort(part_a, size_a), merge_sort(part_b, size_b), size_a, size_b);
}

int *three_way_merge(int *arr1, int *arr2, int *arr3, int size_a, int size_b, int size_c){
    
    int *merged_arr = NULL;
    
    int i,j,k,l, total_size;
    
    i = 0;
    j = 0;
    k = 0;
    l = 0;
    
    total_size = size_a + size_b + size_c;
    
    while(i <= total_size){
        
        if (merged_arr == NULL) merged_arr = (int*) calloc(1,sizeof(int));
        else {
            int *temp = realloc(merged_arr, sizeof(int) *(i+1));    //increase array size
            merged_arr = temp;
        }
        
        if (!(j == size_a || k == size_b || l == size_c))
        {
            int min_value = min(arr1[j],arr2[k],arr3[l]);
            
            if (min_value == arr1[j]){
                merged_arr[i] = arr1[j];
                ++j;
            } else if (min_value == arr2[k]){
                merged_arr[i] = arr2[k];
                ++k;
            } else {
                merged_arr[i] = arr3[l];
                ++l;
            }
        }
        
        //If one array has end, sort with extra two arrays
        
        else if (j == size_a) sort_extra(&merged_arr, &i, total_size, &l, arr3, &k, arr2, size_c, size_b);
        
        else if (k == size_b) sort_extra(&merged_arr, &i, total_size, &l, arr3, &j, arr1, size_c, size_a);
        
        else sort_extra(&merged_arr, &i, total_size, &k, arr2, &j, arr1, size_b, size_a);
        
        i++;        //increase iterator
        
    }
    
    free(arr1);     //avoid memory leak
    free(arr2);     //avoid memory leak
    free(arr3);
    
    return merged_arr;
}

int *three_way_merge_sort(int *data_set, int size){
    
    if (size == 1) return data_set;
    
    if (size == 2)
    {
        if(data_set[0]>data_set[1])
        {
            int temp;
            
            temp = data_set[0];
            data_set[0] = data_set[1];
            data_set[1] = temp;
        }
        return data_set;
    }
    
    int size_a = size/3;
    int size_b = (size - size_a)/2;
    int size_c = size-(size_a+size_b);
    
    int *part_a = (int*)calloc(size_a, sizeof(int));
    int *part_b = (int*)calloc(size_b, sizeof(int));
    int *part_c = (int*)calloc(size_c, sizeof(int));
    
    memmove(part_a, data_set, sizeof(int)*size_a);
    memmove(part_b, data_set + size_a, sizeof(int)*size_b);
    memmove(part_c, data_set + size_a + size_b, sizeof(int)*size_c);
    
    //display_three_array(part_a, part_b, part_c, size_a, size_b, size_c);
    
    free(data_set);
    
    return three_way_merge(three_way_merge_sort(part_a, size_a), three_way_merge_sort(part_b, size_b), three_way_merge_sort(part_c, size_c), size_a, size_b, size_c);
}

/**********************************************
 *
 *                  Quick Sort
 *
 **********************************************/

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

/**********************************************
 *
 *             Quick Sort - end
 *
 **********************************************/



#endif /* SortingAlgorithm_h */
