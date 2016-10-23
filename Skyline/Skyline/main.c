//
//  main.c
//  Skyline
//
//  Created by Sang Gyeong Jo on 2016. 10. 12..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#include "Skyline.h"

void run_test();

int main(int argc, const char * argv[]) {
    run_test();
    return 0;
}

void run_test ()
{
    int n;
    scanf("%d", &n);
    building *new_B = build_buildings(n);
    skyline_s *new_S = find_skyline(new_B, 0, n-1);
    
    for ( int i = 0 ; i < new_S->size ; i++ )
    {
        printf("%d,%d",new_S->_skyline[i].start,new_S->_skyline[i].height);
        if ( i+1 < new_S->size ) printf(",");
    }
}
