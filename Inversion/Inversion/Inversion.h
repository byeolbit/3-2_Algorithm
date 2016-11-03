//
//  Inversion.h
//  Inversion
//
//  Created by Sang-Gyeong Jo on 2016. 11. 1..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#ifndef Inversion_h
#define Inversion_h

#include <stdlib.h>
#include <memory.h>
#include "Essential.h"

struct inv_array
{
    int count;
    int size;
    int *data;
};

typedef struct inv_array array;

array *build_data (FILE *fp);
array *sort_and_cnt ( array *L );
array *merge_and_cnt ( array *A, array *B );
array *div_half ( array *L );
void array_push(array *arr, int x);
array *new_array ();

array *new_array ()
{
    array *new_a = calloc(1,sizeof(array));
    new_a->size = 0;
    new_a->count = 0;
    new_a->data = calloc(0,sizeof(int));
    return new_a;
}

array *build_data (FILE *fp)
{
    array *new_data = new_array();
    
    while(!feof(fp))
    {
        int tmp;
        fscanf(fp, "%d,",&tmp);
        
        array_push(new_data, tmp);
    }
    
    fclose(fp);
    
    printf("original data : ");
    for( int i = 0 ; i < new_data -> size ; i++ )
        printf("%d ",new_data->data[i]);
    printf("\n");
    
    return new_data;
}

void array_push(array *arr, int x)
{
    arr->size++;
    int *tmp = realloc(arr->data, (arr->size)*sizeof(int));
    tmp[arr->size-1] = x;
    arr->data = tmp;
}

array *div_half ( array *L )
{
    array *new_a = new_array();
    
    new_a -> size = L -> size/2;
    L -> size -= new_a -> size;
    
    new_a -> data = calloc(new_a->size,sizeof(int));
    memmove(new_a->data, L->data, new_a->size * sizeof(int));
    
    int *tmp = calloc(L->size,sizeof(int));
    memmove(tmp, L->data + new_a->size, L->size * sizeof(int));
    free(L->data);
    L -> data = tmp;
    /*
    printf("half data a(size:%d):",new_a->size);
    for( int i = 0 ; i < new_a -> size ; i++ )
        printf("%d,",new_a->data[i]);
    printf("\n");
    
    printf("half data b(size:%d):",L->size);
    for( int i = 0 ; i < L-> size ; i++ )
        printf("%d,",L->data[i]);
    printf("\n");
    */
    
    return new_a;
}

array *sort_and_cnt ( array *L )
{
    if ( L->size == 1 )
    {
        L->count = 0;
        return L;
    }
    
    array *A = div_half(L);
    array *B = L;
    
    array *r_a = sort_and_cnt(A);
    array *r_b = sort_and_cnt(B);
    array *R = merge_and_cnt(r_a, r_b);
    R->count = r_a->count + r_b->count + R->count;
    
    return R;
}

array *merge_and_cnt ( array *A, array *B )
{
    array *result = new_array();
    
    int inv_cnt = 0;
    int i_A = 0, i_B = 0;
    int s_A, s_B;
    s_A = A->size;
    s_B = B->size;
    
    while (A->size != 0 && B->size != 0)
    {
        if(A->data[i_A] > B->data[i_B])
        {
            inv_cnt += A->size;
            array_push(result,B->data[i_B]);
            i_B++;
            B->size--;
        }
        else
        {
            array_push(result,A->data[i_A]);
            i_A++;
            A->size--;
        }
    }
    
    if (A->size == 0)
    {
        while(B->size > 0)
        {
            array_push(result, B->data[s_B-B->size]);
            B->size--;
        }
    }
    else if (B->size ==0)
    {
        while(A->size > 0)
        {
            array_push(result, A->data[s_A-A->size]);
            A->size--;
        }
    }
    else
    {
        exit(1); //error
    }
    /*
    printf("merge data result(size:%d):",result->size);
    for( int i = 0 ; i < result -> size ; i++ )
        printf("%d,",result->data[i]);
    printf("\n");
    */
    result->count = inv_cnt;
    return result;
}

#endif /* Inversion_h */
