//
//  main.c
//  Floor
//
//  Created by Sang Gyeong Jo on 2016. 10. 12..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#include "Floor.h"

void run_test();

int main(int argc, const char * argv[])
{
    run_test();
    return 0;
}

void run_test()
{
    printf("경계를 테스트합니다. 각각 테스트값의 -1,+0,+1\n\n");
    for(int i=0; i<64; i++)
    {
        unsigned long test = pow(2,i);
        printf("test number : %lu\n",test);
        printf("result\n");
        printf("%d, %d, %d\n",floor_log2(test-1),floor_log2(test), floor_log2(test+1));
        printf("must have to be\n");
        if(i == 0)
        {
            printf("%d, %d, %d\n",i-1, i,i+1);
            if (floor_log2(test-1) == i-1 && floor_log2(test) == i && floor_log2(test+1) == i+1)
                printf("Test result : pass!\n\n");
            else printf("Test result : fail!\n\n");
        } else
        {
            printf("%d, %d, %d\n",i-1, i,i);
            if (floor_log2(test-1) == i-1 && floor_log2(test) == i && floor_log2(test+1) == i)
                printf("Test result : pass!\n\n");
            else printf("Test result : fail!\n\n");
        }
    }
}
