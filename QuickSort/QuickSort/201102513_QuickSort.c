//
//  main.c
//  QuickSort
//
//  Created by Sang Gyeong Jo on 2016. 9. 29..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#include "Quick.h"

void controller(int *data_set, int op);

int main(int argc, const char * argv[]) {
    
    char *in_file = "data04.txt";
    char *out_file = "output.txt";
    float time_sum = 0;
    int *data_set = NULL;
    
    for(int i=0; i<1000; i++)
    {
        data_set = build_dataset(open_file(in_file, "r+"));
        controller(data_set, 1);
        time_sum += calculate_time();
    }
    
    printf("%f average millisec\n",time_sum/1000);
    
    fprint_int_array(data_set, size_of_dataset, open_file(out_file, "w+"), 1);
    
    
    return 0;
}

// op 1 is normal, 0 is for randomized
void controller(int *data_set, int op)
{
    if(op)
    {
        set_timer();
        quick_sort(data_set, 0, size_of_dataset-1);
        stop_timer();
    }
    else
    {
        set_timer();
        quick_sort_randomized(data_set, 0, size_of_dataset-1);
        stop_timer();
    }
}
