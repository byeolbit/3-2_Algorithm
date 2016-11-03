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
#include <math.h>
#include <memory.h>

struct point_pair
{
    point a;
    point b;
    double dist;
};

typedef struct point_pair pair;

double get_dist( point a, point b)
{
    double x = a.x>b.x ? (a.x-b.x) : (b.x-a.x);
    double y = a.y>b.y ? (a.y-b.y) : (b.y-a.y);
    
    return sqrt(pow(x,2)+pow(y,2));
}

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
    
    while(!feof(fp))
    {
        new_data -> size++;
        point *tmp = realloc(new_data->data, new_data->size*sizeof(point));
        new_data -> data = tmp;
        double x, y;
        fscanf(fp, "%lf,%lf\n",&x, &y);
        new_data->data[new_data->size-1].x = x;
        new_data->data[new_data->size-1].y = y;
    }
    
    printf("read data : ");
    for ( int i = 0; i < new_data->size ; i++ )
        printf("(x:%0.1lf,y:%0.1lf) ",new_data->data[i].x,new_data->data[i].y);
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
    d_set -> data = tmp;
    
    printf("half data a(size:%d):",new_d->size);
    for( int i = 0 ; i < new_d -> size ; i++ )
        printf("(%0.1lf,%0.1lf) ",new_d->data[i].x,new_d->data[i].y);
    printf("\n");
    
    printf("half data b(size:%d):",d_set->size);
    for( int i = 0 ; i < d_set-> size ; i++ )
        printf("(%0.1lf,%0.1lf) ",d_set->data[i].x,d_set->data[i].y);
    printf("\n");

    
    return new_d;
}

pair min_pair(pair p1, pair p2)
{
    return p1.dist < p1.dist ? p1 : p2;
}

pair brute_force(point_s *d_set)
{
    pair result;
    int i, j;
    double d;
    result.dist = get_dist(d_set->data[0], d_set->data[1]);
    
    for (i = 0 ; i < d_set->size ; i++) {
        for (j = i + 1; j < d_set->size ; j++) {
            d = get_dist(d_set->data[i], d_set->data[j]);
            if (d < result.dist )
            {
                result.a = d_set->data[i];
                result.b = d_set->data[j];
                result.dist = d;
            }
        }
    }
    
    return result;
}

void push_point( point_s *D, point p )
{
    D->size++;
    point *tmp = realloc(D->data, D->size*sizeof(point));
    tmp[D->size-1] = p;
    D -> data = tmp;
}

point_s *del( double L, point_s *d_set, pair r)
{
    point_s *new_p = new_point_set();

    for ( int i = 0 ; i < d_set->size; i++ )
    {
        if ( d_set->data[i].x < L )
        {
            if ( L - d_set->data[i].x < r.dist)
                push_point(new_p, d_set->data[i]);
        }
        else
        {
            if ( d_set->data[i].x - L < r.dist)
                push_point(new_p, d_set->data[i]);
        }
    }
    
    return new_p;
}

pair closest_pair(point_s *d_set)
{
    if ( d_set -> size < 4 )
        return brute_force(d_set);
    
    double half_line = compute_half(d_set);
    
    point_s *right_half = new_point_set();
    free(right_half->data);
    right_half->size = d_set->size;
    right_half->data = calloc(right_half->size,sizeof(point));
    memmove(right_half->data, d_set->data, d_set->size*sizeof(point));
    
    point_s *left_half = div_half(right_half);
    
    pair r1 = closest_pair(left_half);
    pair r2 = closest_pair(right_half);
    pair r = min_pair(r1, r2);
    
    printf("min : %lf\n",r.dist);
    
    point_s *tmp = del(half_line, d_set, r);
    free(d_set);
    d_set = tmp;
    
    quick_sort_y(d_set->data, 0, d_set->size-1);
    
    for (int i = 0 ; i < d_set->size ; i++) {
        for (int j = i + 1; j < d_set->size ; j++) {
            double d = get_dist(d_set->data[i], d_set->data[j]);
            if (d < r.dist )
            {
                r.a = d_set->data[i];
                r.b = d_set->data[j];
                r.dist = d;
            }
        }
    }
    
    return r;
}




#endif /* ClosestPair_h */
