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

struct inv_array
{
    int count;
    int size;
    int *data;
};

typedef struct inv_array array;

array *sort_and_cnt ( array *L );
array *merge_and_cnt ( array *A, array *B );
array *div_half ( array *L );

array *new_array ();

array *new_array ()
{
    array *new_a;
    return new_a;
}

array *div_half ( array *L )
{
    array *new_a;
    
    new_a -> size = L -> size/2;
    L -> size -= new_a -> size;
    
    new_a -> data = calloc(new_a->size,sizeof(int));
    memmove(new_a->data, L->data, new_a->size);
    
    int *tmp = calloc(L->size,sizeof(int));
    memmove(tmp, L->data + new_a->size, L->size);
    free(L->data);
    L -> data = tmp;
    
    return new_a;
}

array *sort_and_cnt ( array *L )
{
    if ( L->size == 1 )
    {
        array *new_a;
        new_a->data = L->data;
        new_a->count = 0;
        return new_a;
    }
    
    array *A = div_half(L);
    
    merge_and_cnt(sort_and_cnt(A), sort_and_cnt(L));
    
    return L;
    
    
}

#endif /* Inversion_h */
