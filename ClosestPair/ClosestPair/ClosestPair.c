//
//  main.c
//  ClosestPair
//
//  Created by Sang Gyeong Jo on 2016. 11. 3..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#include "ClosestPair.h"

int main(int argc, const char * argv[]) {
    
    FILE *fp = open_file("data07_closest.txt","r+");
    
    point_s *result = build_data(fp);
    quick_sort(result->data, 0, result->size-1);
    printf("closest dist : %lf\n",closest_pair(result).dist);
    
    return 0;
}
