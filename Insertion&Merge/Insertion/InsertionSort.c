//
//  InsertionSort.c
//
//  Created by Sang Gyeong Jo on 2016. 9. 8..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int *data;
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
    data = (int *) malloc(sizeof(int));
    
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
    
    int count = 1;
    
    if(EOF != (ch = fgetc(data_file_pointer))){
        
        while(ch != ','){
            
            realloc(data, sizeof(int) * (count+1));
            
            data[count] = ch -'0';
            
            count++;
            
            return 1;
            
        } else {
            return 0;
        }
    }
}

void insertion_sort(){
    
}