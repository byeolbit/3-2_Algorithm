//
//  InsertionSort.c
//
//  Created by Sang Gyeong Jo on 2016. 9. 8..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int *data_set;
char *data;
File *data_file_pointer;
File *result_file_pointer;

void read_file(char *file_path);
void open_file(char *flie_path);
void get_original_data(void);
int insertion_sort(void);
void write_sorted_data();

int main(void){
    
    //Init variables;
    char *file_path = "./data02.txt";
    char *result_file = "sort.txt";
    data_set = (int *) malloc(sizeof(int));
    
    read_file(*file_path);
    
    get_original_data();
    
    while(insertion_sort()) write_sorted_data();
    
    fclose(data_file_pointer);  //close data file pointer
    fclose(result_file_pointer);  //close result file pointer
    
}

//Read file from file path and return File pointer
void read_file(char *file_path){
    
    // File opening exception handling
    if(!(data_file_pointer = fopen(file_path, "r"))){
        
        perror("File open error!");
        exit(1);
        
    }
}

//Open file to write sorted data
void open_file(char *file_path){
    
    // File opening exception handling
    if(!(result_file_pointer; = fopen(file_path, "w"))){
        
        perror("File open error!");
        exit(1);
        
    }
}

//Get a set of data from file
int get_original_data(){
    
    int count_int;
    int count_loop = 0;
    
    while(EOF != (ch = fgetc(data_file_pointer))){
    
        count_int = 0;
        
        data = (char *) malloc(sizeof(char));
        
        while(ch != ',' || ch != EOF){
            
            realloc(data, sizeof(char) * (count_int+1));
            
            data[count_int] = ch;
            
            ++count;
            
        }
        
        data_set[count_loop] = atoi(data);
        
        free(data);
        
        ++count_loop;
        
        if(ch == EOF) break;
        
        realloc(data_set, sizeof(int) * (count_loop+1));

    }
    
    return count_loop;
    
}

void insertion_sort(){
    
}