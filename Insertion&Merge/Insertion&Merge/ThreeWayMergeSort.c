//
//  ThreeWayMergeSort.c
//
//  Used compiler : Clang-703.0.31
//
//  Created by Sang Gyeong Jo on 2016. 9. 20..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#include "Essentials.h"

int main(void){
    
    //Init variables;
    int *data_set;
    char *file_path = "data02.txt";
    char *result_file = "hw02_00_201102513_3way_merge.txt";
    
    data_set = get_original_data(file_path);
    
    set_timer();
    
    data_set = three_way_merge_sort(data_set, data_size);
    
    stop_timer();
    
    write_sorted_data(data_set, result_file, data_size, TRUE);
    
    check_loops();
    
    calculate_time();
    
}
