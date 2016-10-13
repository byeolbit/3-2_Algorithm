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

int floor_log2(unsigned long N)
{
    if (N==0) return -1;
    
    unsigned long pow_set[64];
    for(int i = 0; i<64; (pow_set[i-1] = pow(2,i++)));
    
    return binary_search_unsigend_long(pow_set, N, 64);
}


#endif /* Floor_h */
