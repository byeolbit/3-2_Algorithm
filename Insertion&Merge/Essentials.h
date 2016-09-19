//
//  Essentials.h
//
//  Created by Sang Gyeong Jo on 2016. 9. 18..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#ifndef Essentials_h
#define Essentials_h

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

int data_size;
clock_t start_time;
clock_t end_time;
int check_loop;

FILE *open_file(char *file_path, char *op);

int calculate_time();
int get_data_size(int *data_set);
int binary_search(int *array, int target, int size);
int *get_original_data(char *file_path);
int *merge_combine(int *arr1, int *arr2, int size);
int *merge_sort(int *data_set, int size);
void set_timer();
void stop_timer();
void insertion_sort(int *data_set, int size);
void write_sorted_data(int *data_set, char *file_path, int size);

void set_timer(){
    start_time = clock();
}

void stop_timer(){
    end_time = clock();
}

int calculate_time(){
    float msec = (((float)end_time - start_time) / CLOCKS_PER_SEC) * 1000;
    printf("%f Milliseconds\n",msec);
    return (int)msec;
}

//Get length of array
int get_data_size(int *data_set){
    
    return sizeof(data_set)/sizeof(int);
    
}

//Read file from file path and return File pointer
FILE *open_file(char *file_path, char *op){
    
    FILE *fp;
    
    // File opening exception handling
    if(!(fp = fopen(file_path, op))){
        
        perror("File open error!");
        exit(1);
        
    }
    
    return fp;
}

//Get a set of data from file
int *get_original_data(char *file_path){
    
    FILE *data_file_pointer = open_file(file_path, "r");
    
    int *data_set = (int *) calloc(1,sizeof(int));
    char *data = NULL;
    int *temp;
    int count_int;
    int count_loop = 0;
    char ch;
    
    while(EOF != (ch = fgetc(data_file_pointer))){
        
        count_int = 0;
        
        while(ch != ',' && ch != EOF){
            
            if (count_int == 0) data = (char *) calloc(1,sizeof(char));
            
            else realloc(data, sizeof(char) * (count_int+1));
            
            data[count_int] = ch;
            
            ++count_int;
            
            ch = fgetc(data_file_pointer);
            
        }
        
        data_set[count_loop] = atoi(data);
        
        free(data);
        data = NULL;
        
        ++count_loop;
        
        if(ch == EOF) break;
        
        temp = realloc(data_set, sizeof(int) * (count_loop+1)); //Avoid NULL pointer error
        
        data_set = temp;
        
        if(data_set == 0){
            perror("allocation error");
        }
        
    }
    
    fclose(data_file_pointer);  //close data file pointer
    
    data_size = count_loop;
    
    return data_set; //return size of data_set
    
}

int binary_search(int *array, int target, int size){
    
    int low, high, mid;
    low = 0;
    mid = 0;
    high = size;
    
    while(low <= high){
        check_loop++;   //check loops
        mid = low + (high-low) / 2;
        if(array[mid] > target) high = mid -1;
        else if (array[mid] < target) low = mid +1;
        else break;
    }
    
    return low;
    
}

void insertion_sort(int *data_set, int size){
    
    check_loop = 0;
    
    int i,j,key;
    
    for (j=1; j<size; j++){
        key = data_set[j];
        i = j-1;
        while(i>=0 && data_set[i]>key){
            data_set[i+1] = data_set[i];
            --i;
            check_loop++;
        }
        data_set[i+1] = key;
    }
}

void binary_insertion_sort(int *data_set, int size){
    
    check_loop = 0;
    
    int i,key;
    
    for (i=1; i<size; i++){
        
        check_loop++;
        
        key = data_set[i];
        
        int target = binary_search(data_set, key, i);
        
        memmove(data_set+target+1, data_set+target, sizeof(int)*(i-target));
        
        data_set[target] = key;
        
    }
}



int *merge_combine(int *arr1, int *arr2, int size){
    
    int *merged_arr = NULL;
    
    int i,j,k;
    
    i = 0;
    j = 0;
    k = 0;
    
    while((j+k) < size){
        
        if (merged_arr == NULL) merged_arr = (int*) calloc(1,sizeof(int));
        else {
            int *temp = realloc(merged_arr, sizeof(int) *(i+1));
            merged_arr = temp;
        }
        
        if(arr1[j] > arr2[k]){
            merged_arr[i] = arr1[j];
            ++j;
        } else {
            merged_arr[i] = arr2[k];
            ++k;
        }
        
        i++;
        
    }
    
    return merged_arr;

}

int *merge_sort(int *data_set, int size){
    
    int *part_a;
    int *part_b;
    
    int size_a = size/2;
    int size_b = size - size_a;
    
    part_a = memmove(data_set, part_a, sizeof(int)*size_a);
    part_b = memmove(data_set+size_b, part_b, sizeof(int)*size_b);
    
    if (size == 2) return merge(part_a, part_b, size);
    
    else if (size == 3) return merge(part_a, merge_sort(part_b, size_b), size);
    
    else return merge(merge_sort(part_a, size_a), merge_sort(part_b, size_b), size);
    
}

void write_sorted_data(int *data_set, char *file_path, int size){
    
    FILE *result_file_pointer = open_file(file_path, "w");
    int i;
    
    for (i=0; i<size; i++){
        fprintf(result_file_pointer, "%d", data_set[i]);    //File output
        printf("%d", data_set[i]);                          //Consle output
        if(i != size-1) {
            fprintf(result_file_pointer,",");               //File output
            printf(",");                                    //Cosole output
        }
    }
    
    printf("\n");   //Console output
    printf("%d loops\n",check_loop);
    fclose(result_file_pointer);  //close result file pointer
}

#endif /* Essentials_h */
