//
//  main.c
//  Inversion
//
//  Created by Sang-Gyeong Jo on 2016. 10. 31..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#include "Inversion.h"
#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    FILE *fp = open_file("data07_inversion.txt","r+");
    
    array *result = sort_and_cnt(build_data(fp));
    
    printf("sort result : ");
    for( int i = 0 ; i < result -> size ; i++ )
        printf("%d ",result->data[i]);

    printf("\ninversion count : %d\n",result->count);
    
    return 0;
    
}
