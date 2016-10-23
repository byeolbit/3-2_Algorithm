//
//  Skyline.h
//  Skyline
//
//  Created by Sang Gyeong Jo on 2016. 10. 20..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#ifndef Skyline_h
#define Skyline_h

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

struct building
{
    int left;
    int height;
    int right;
};

struct skyline
{
    int start;
    int height;
};

struct skylines
{
    struct skyline *_skyline;
    int size;
};

typedef struct skyline skyline;
typedef struct skylines skyline_s;
typedef struct building building;

building *new_buildings( int n );
building *get_building(int l, int h, int r);
building *build_buildings ( int n );

skyline *new_skyline(int s, int h);
skyline_s *new_skylines();
void append_skyline( skyline_s *S, int s, int h);

skyline_s *find_skyline(building *B, int s, int e);
skyline_s *merge_skyline( skyline_s *sky1, skyline_s *sky2 );


building *new_buildings( int n )
{
    building *buildings = calloc(n, sizeof(building));
    
    return buildings;
}

building *get_building(int l, int h, int r)
{
    building *new_b = calloc(1,sizeof(building));
    
    new_b->left = l;
    new_b->height = h;
    new_b->right = r;
    
    return new_b;
}

building *build_buildings ( int n )
{
    building *new_B = new_buildings(n);
    
    for ( int i = 0 ; i < n ; i++ )
    {
        int l, h, r;
        
        scanf("%d,%d,%d",&l,&h,&r);
        
        new_B[i] = *get_building(l, h, r);
    }
    
    return new_B;
}

skyline *new_skyline(int s, int h)
{
    skyline *new_s = calloc(1,sizeof(skyline));
    new_s->start = s;
    new_s->height = h;
    
    return new_s;
}

skyline_s *new_skylines()
{
    skyline_s *new_S = calloc(1,sizeof(skyline_s));
    new_S->size = 0;
    new_S->_skyline = calloc(0,sizeof(skyline));
    
    return new_S;
}

void append_skyline( skyline_s *S, int s, int h)
{
    S->size++;
    skyline *tmp = realloc(S->_skyline, (S->size)*sizeof(skyline));
    S->_skyline = tmp;
    
    S->_skyline[S->size-1] = *new_skyline(s, h);
}

void remove_skyline( skyline_s *S, int i )
{
    if (S->size == 1)
    {
        S->size--;
        skyline *tmp = calloc(0, sizeof(skyline));
        free(S->_skyline);
        S->_skyline = tmp;
    } else
    {
        S->size--;
        skyline *tmp = calloc(S->size, sizeof(skyline));
        memmove(tmp, S->_skyline+1+i, (S->size-i)*sizeof(skyline));
        free(S->_skyline);
        S->_skyline = tmp;
    }
}


skyline_s *find_skyline(building *B, int s, int e)
{
    if ( s == e )
    {
        skyline_s *new_S = new_skylines();
        append_skyline(new_S, B[s].left, B[s].height);
        append_skyline(new_S, B[e].right, 0);
        return new_S;
    }
    
    int mid = (s+e)/2;
    
    skyline_s *sky1 = find_skyline(B, s, mid);
    skyline_s *sky2 = find_skyline(B, mid+1, e);
    
    return merge_skyline(sky1, sky2);
}

skyline_s *merge_skyline( skyline_s *sky1, skyline_s *sky2 )
{
    skyline_s *new_S = new_skylines();
    
    int currentH1 = 0;
    int currentH2 = 0;
    int maxH = 0;
    int currentX = 0;
    int currentX2 = 0;
    
    while ( (sky1->size > 0) && (sky2->size > 0) )
    {
        if ( sky1->_skyline[0].start < sky2->_skyline[0].start )
        {
            currentX = sky1->_skyline[0].start;
            currentH1 = sky1->_skyline[0].height;
            
            if ( currentH1 > currentH2 )
            {
                currentH2 = currentH1;
            }
            else
            {
                if ( currentH1 < sky2->_skyline[0].height )
                    currentH2 = currentH1;
            }
            
            if ( maxH != currentH2)
                append_skyline(new_S, currentX, currentH2);
            remove_skyline(sky1, 0);
            
            maxH = currentH2;
            
            currentH2 = currentH1;
            
        } else
        {
            currentX = sky2->_skyline[0].start;
            currentH1 = sky2->_skyline[0].height;
            
            if ( currentH1 > currentH2 )
            {
                currentH2 = currentH1;
            }
            else
            {
                if ( currentH1 < sky1->_skyline[0].height )
                    currentH2 = currentH1;
            }
            
            if ( maxH != currentH2)
                append_skyline(new_S, currentX, currentH2);
            remove_skyline(sky2, 0);
            
            maxH = currentH2;
            
            currentH2 = currentH1;
            
        }
    }
    
    while (sky1->size > 0) {
        append_skyline(new_S, sky1->_skyline[0].start, sky1->_skyline[0].height);
        remove_skyline(sky1, 0);
    }
    while (sky2->size > 0) {
        append_skyline(new_S, sky2->_skyline[0].start, sky2->_skyline[0].height);
        remove_skyline(sky2, 0);
    }
    
    free(sky1->_skyline);
    free(sky2->_skyline);
    free(sky1);
    free(sky2);
    
    printf("result\n");
    for ( int i = 0 ; i < new_S->size ; i++ )
        printf("(%d,%d)",new_S->_skyline[i].start, new_S->_skyline[i].height);
    printf("\n");
    
    return new_S;
}



#endif /* Skyline_h */
