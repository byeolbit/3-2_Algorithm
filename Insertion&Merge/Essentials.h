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
long check_loop;

FILE *open_file(char *file_path, char *op);

int min(int a, int b, int c);
int calculate_time();
int get_data_size(int *data_set);
int binary_search(int *array, int target, int size);
int *get_original_data(char *file_path);
int *merge(int *arr1, int *arr2, int size_a, int size_b);
int *merge_sort(int *data_set, int size);
int *three_way_merge(int *arr1, int *arr2, int *arr3, int size_a, int size_b, int size_c);
int *three_way_merge_sort(int *data_set, int size);
int *insertion_sort(int *data_set, int size);
int *binary_insertion_sort(int *data_set, int size);

void set_timer();
void stop_timer();
void write_sorted_data(int *data_set, char *file_path, int size);
void display_two_array(int *part_a, int *part_b, int size_a, int size_b);
void sort_extra(int **merged_arr_p, int *i_p, int total_size, int *k_p, int *arr2, int *j_p, int *arr1, int size_b, int size_a);

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
        if (array[mid] > target) high = mid -1;
        else if (array[mid] < target) low = mid +1;
        else break;
    }
    
    return low;
    
}

int *insertion_sort(int *data_set, int size){
    
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
    
    return data_set;
}

int *binary_insertion_sort(int *data_set, int size){
    
    check_loop = 0;
    
    int i,key;
    
    for (i=1; i<size; i++){
        
        check_loop++;
        
        key = data_set[i];
        
        int target = binary_search(data_set, key, i);
        
        memmove(data_set+target+1, data_set+target, sizeof(int)*(i-target));
        
        data_set[target] = key;
        
    }
    
    return data_set;
}



int *merge(int *arr1, int *arr2, int size_a, int size_b){
    
    check_loop++;
    
    int *merged_arr = (int*) calloc(1,sizeof(int));
    
    int i,j,k;
    
    i = 0;
    j = 0;
    k = 0;
    
    sort_extra(&merged_arr, &i, size_a+size_b, &k, arr2, &j, arr1, size_b, size_a);
    
    free(arr1);     //avoid memory leak
    free(arr2);     //avoid memory leak
    
    return merged_arr;
    
}

void display_two_array(int *part_a, int *part_b, int size_a, int size_b){
    
    int i;
    printf("part a, size : %d\n",size_a);
    for( i=0; i<size_a ; i++){
        printf("%d ", part_a[i]);
    }
    printf("\n");
    printf("part b, size : %d\n",size_b);
    for( i=0; i<size_b ; i++){
        printf("%d ", part_b[i]);
    }
    printf("\n");
    
}

void display_three_array(int *part_a, int *part_b, int *part_c, int size_a, int size_b, int size_c){
    
    int i;
    printf("part a, size : %d\n",size_a);
    for( i=0; i<size_a ; i++){
        printf("%d ", part_a[i]);
    }
    printf("\n");
    printf("part b, size : %d\n",size_b);
    for( i=0; i<size_b ; i++){
        printf("%d ", part_b[i]);
    }
    printf("\n");
    printf("part c, size : %d\n",size_c);
    for( i=0; i<size_c ; i++){
        printf("%d ", part_c[i]);
    }
    printf("\n");
}


int *merge_sort(int *data_set, int size){
    
    if(size == 1) return data_set;  //end of depth
    
    int size_a = size/2;
    int size_b = size - size_a;
    
    int *part_a = (int*)calloc(size_a, sizeof(int));
    int *part_b = (int*)calloc(size_b, sizeof(int));
    
    memmove(part_a, data_set, sizeof(int)*size_a);
    memmove(part_b, data_set + size_a, sizeof(int)*size_b);
    
    //display_two_array(part_a, part_b, size_a, size_b);  // Display values
    
    free(data_set);     //avoid memory leak
    
    if (size == 2) return merge(part_a, part_b, size_a, size_b);
    
    else return merge(merge_sort(part_a, size_a), merge_sort(part_b, size_b), size_a, size_b);
    
}

int min(int a, int b, int c){
    
    int min = 0;
    
    if(a < b) min = a;
    else min = b;
    
    if(min > c) return c;
    else return min;
    
}

void sort_extra(int **merged_arr_p, int *i_p, int total_size, int *k_p, int *arr2, int *j_p, int *arr1, int size_b, int size_a) {
    while(*i_p <= total_size){
        
        if (*j_p == size_a){                            // end of part_a
            (*merged_arr_p)[(*i_p)] = arr2[(*k_p)];     // put b
            ++(*k_p);
        } else if (*k_p == size_b){                     // end of part_b
            (*merged_arr_p)[(*i_p)] = arr1[(*j_p)];     // put a
            ++(*j_p);
        } else {
            if (arr1[(*j_p)] < arr2[(*k_p)]) {
                (*merged_arr_p)[(*i_p)] = arr1[(*j_p)];
                ++(*j_p);
            } else {
                (*merged_arr_p)[(*i_p)] = arr2[(*k_p)];
                ++(*k_p);
            }
        }
        
        if(++(*i_p) != total_size){
            int *temp = realloc(*merged_arr_p, sizeof(int) *(*i_p+1));    //increase array size
            *merged_arr_p = temp;
        } else break;
    }
}

int *three_way_merge(int *arr1, int *arr2, int *arr3, int size_a, int size_b, int size_c){
    
    check_loop++;
    
    int *merged_arr = NULL;
    
    int i,j,k,l, total_size;
    
    i = 0;
    j = 0;
    k = 0;
    l = 0;
    
    total_size = size_a + size_b + size_c;
    
    while(i <= total_size){
        
        if (merged_arr == NULL) merged_arr = (int*) calloc(1,sizeof(int));
        else {
            int *temp = realloc(merged_arr, sizeof(int) *(i+1));    //increase array size
            merged_arr = temp;
        }
        
        if (!(j == size_a || k == size_b || l == size_c)){
            
            int min_value = min(arr1[j],arr2[k],arr3[l]);
            
            if (min_value == arr1[j]){
                merged_arr[i] = arr1[j];
                ++j;
            } else if (min_value == arr2[k]){
                merged_arr[i] = arr2[k];
                ++k;
            } else {
                merged_arr[i] = arr3[l];
                ++l;
            }
            
        }
        
        //If one array has end, sort with extra two arrays
        
        else if (j == size_a) sort_extra(&merged_arr, &i, total_size, &l, arr3, &k, arr2, size_c, size_b);
        
        else if (k == size_b) sort_extra(&merged_arr, &i, total_size, &l, arr3, &j, arr1, size_c, size_a);
        
        else sort_extra(&merged_arr, &i, total_size, &k, arr2, &j, arr1, size_b, size_a);
        
        i++;        //increase iterator
        
    }
    
    free(arr1);     //avoid memory leak
    free(arr2);     //avoid memory leak
    free(arr3);
    
    return merged_arr;
    
}

int *three_way_merge_sort(int *data_set, int size){
    
    if (size == 1) return data_set;
    
    if (size == 2) {
        
        if(data_set[0]>data_set[1]) {
            
            int temp;
            
            temp = data_set[0];
            data_set[0] = data_set[1];
            data_set[1] = temp;
            
        }
        
        return data_set;
    }
    
    int size_a = size/3;
    int size_b = (size - size_a)/2;
    int size_c = size-(size_a+size_b);
    
    int *part_a = (int*)calloc(size_a, sizeof(int));
    int *part_b = (int*)calloc(size_b, sizeof(int));
    int *part_c = (int*)calloc(size_c, sizeof(int));
    
    memmove(part_a, data_set, sizeof(int)*size_a);
    memmove(part_b, data_set + size_a, sizeof(int)*size_b);
    memmove(part_c, data_set + size_a + size_b, sizeof(int)*size_c);
    
    //display_three_array(part_a, part_b, part_c, size_a, size_b, size_c);
    
    free(data_set);
    
    return three_way_merge(three_way_merge_sort(part_a, size_a), three_way_merge_sort(part_b, size_b), three_way_merge_sort(part_c, size_c), size_a, size_b, size_c);
}

void check_loops(){
    printf("%ld loops\n",check_loop);
    check_loop = 0;
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
    fclose(result_file_pointer);  //close result file pointer
}

#endif /* Essentials_h */
