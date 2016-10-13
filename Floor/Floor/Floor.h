//
//  Floor.h
//  Floor
//
//  Created by Sang Gyeong Jo on 2016. 10. 12..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#ifndef Floor_h
#define Floor_h

#include "Algorithm.h"
#include <stdio.h>
#include <math.h>

int floor_log2(unsigned long N);
int binary_search_log(double log2N);

int floor_log2(unsigned long N)
{
    double log2N = log2(N);
    
    return binary_search_log(log2N);
    
}

int binary_search_log(double log2N)
{
    int array[64];
    for(int i = 0; i<64; (array[i-1] = i++));
    
    return binary_search_int(array, log2N, 64);
}



#endif /* Floor_h */
