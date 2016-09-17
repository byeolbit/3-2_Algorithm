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

File open_file(char *file_path, char *op);
int get_original_data(char *file_path);
void insertion_sort(int size);
void write_sorted_data(char *file_path);

int main(void){
    
    //Init variables;
    char *file_path = "./data02.txt";
    char *result_file = "sort.txt";
    data_set = (int *) malloc(sizeof(int));
    int data_size = 0;
    
    get_original_data();
    
    data_size = insertion_sort();
    
    insertion_sort(data_size);
    
    open_file(*result_file);
    
    write_sorted_data();
    
}

//Read file from file path and return File pointer
File open_file(char *file_path, char *op){
    
    File *fp;
    
    // File opening exception handling
    if(!(fp = fopen(file_path, op))){
        
        perror("File open error!");
        exit(1);
        
    }
    
    return fp;
}

//Get a set of data from file
int get_original_data(char *file_path){
    
    File *data_file_pointer = open_file(*file_path, "r");
    
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
    
    fclose(data_file_pointer);  //close data file pointer
    
    return count_loop; //return size of data_set
    
}

void insertion_sort(int size){
    
    int i,j,key;
    
    for (j=1; i<size; j++){
        key = data_set[j];
        i = j-1;
        while(i>=0 && data_set[i]>key){
            data_set[i+1] = data_set[i];
            --i;
        }
        data_set[a+1] = key;
    }
}

void write_sorted_data(char *file_path, int size){
    
    File *result_file_pointer = open_file(*file_path, "w");
    
    for (i=0; i<size; i++){
        fprintf("%d",data_set[i]);
        printf("%d",data_set[i]);   //consle check
        if(i != size) {
            fprintf(",");
            printf(",");            //cosole check
        }
    }
    
    fclose(result_file_pointer);  //close result file pointer
}