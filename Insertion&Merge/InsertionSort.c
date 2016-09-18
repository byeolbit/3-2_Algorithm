//
//  InsertionSort.c
//
//  Used compiler : Clang-703.0.31
//
//  Created by Sang Gyeong Jo on 2016. 9. 8..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#include "Essentials.h"

int main(void){
    
    //Init variables;
    int *data_set;
    char *file_path = "data02.txt";
    char *result_file = "hw02_00_201102513_insertion.txt";
    
    data_set = get_original_data(file_path);
    
    insertion_sort(data_set, data_size);
    
    write_sorted_data(data_set, result_file, data_size);
    
}