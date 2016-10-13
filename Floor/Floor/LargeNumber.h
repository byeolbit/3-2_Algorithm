//
//  LargeNumber.h
//  Floor
//
//  Created by Sang-Gyeong Jo on 2016. 10. 13..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#ifndef LargeNumber_h
#define LargeNumber_h

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


struct large_num { size_t size; char *num; };

struct large_num get_large_num()
{
    struct large_num new_ln;
    
    new_ln.num = NULL;
    
    printf("input number\n");
    while(getline(&new_ln.num,&new_ln.size, stdin) == -1) printf("No input\n");
    
    return new_ln;
}

#endif /* LargeNumber_h */
