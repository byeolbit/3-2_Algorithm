//
//  ClosestPair.h
//  ClosestPair
//
//  Created by Sang Gyeong Jo on 2016. 11. 3..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#ifndef ClosestPair_h
#define ClosestPair_h

#include "Essential.h"
#include "Quick.h"
#include <memory.h>

point_s *new_point_set()
{
    
    point_s *new_data = calloc(1,sizeof(point_s));
    
    new_data -> size = 0;
    new_data -> data = calloc(0,sizeof(point));
    
    return new_data;
}

point_s *build_data( FILE *fp )
{
    point_s *new_data = new_point_set();
    
    while(feof(fp))
    {
        new_data -> size++;
        new_data -> data = realloc(new_data->data, new_data->size);
        fscanf(fp, "%lf,%lf",&new_data->data[new_data->size-1].x, &new_data->data[new_data->size-1].y);
    }
    
    printf("read data : ");
    for ( int i = 0; i < new_data->size ; i++ )
        printf("(x: %lf, y: %lf) ",new_data->data[i].x,new_data->data[i].y);
    printf("\n");
    
    fclose(fp);
    
    return new_data;
}

double compute_half(point_s *d_set)
{
    int mid = d_set->size/2;
    return (d_set->data[mid+1].x - d_set->data[mid].x)/2 + d_set->data[mid].x;
}

point_s *div_half(point_s *d_set)
{
    point_s *new_d = new_point_set();
    
    new_d -> size = d_set -> size/2;
    d_set -> size -= new_d -> size;
    
    new_d -> data = calloc(new_d->size,sizeof(point));
    memmove(new_d->data, d_set->data, new_d->size * sizeof(point));
    
    point *tmp = calloc(d_set->size,sizeof(int));
    memmove(tmp, d_set->data + new_d->size, d_set->size * sizeof(point));
    free(d_set->data);
    d_set -> data = tmp;
    
    return new_d;
}

point closest_pair(point_s *d_set)
{
    point result;
    
    quick_sort(d_set->data, 0, d_set->size-1);
    double half_line = compute_half(d_set);
    
    point_s *left_half = div_half(d_set);
    point_s *right_half = d_set;
    
    point *r1 = closet_pair(left_half);
    point *r2 = closet_pair(right_half);
    
    
    
    return result;
}




#endif /* ClosestPair_h */
