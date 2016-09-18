//
//  InsertionSort.c
//
//  Used compiler : Clang-703.0.31
//
//  Created by Sang Gyeong Jo on 2016. 9. 8..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int *data_set;

FILE *open_file(char *file_path, char *op);
int get_original_data(char *file_path);
void insertion_sort(int size);
void write_sorted_data(char *file_path, int size);

int main(void){
    
    //Init variables;
    char *file_path = "data02.txt";
    char *result_file = "hw02_00_201102513_insertion.txt";
    data_set = (int *) calloc(1,sizeof(int));
    int data_size = 0;
    
    data_size = get_original_data(file_path);
    
    insertion_sort(data_size);
    
    write_sorted_data(result_file, data_size);
    
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
int get_original_data(char *file_path){
    
    FILE *data_file_pointer = open_file(file_path, "r");
    
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
        
        temp = realloc(data_set, sizeof(int) * (count_loop+1));
        
        data_set = temp;
        
        if(data_set == 0){
            perror("allocation error");
        }
        
    }
    
    fclose(data_file_pointer);  //close data file pointer
    
    return count_loop; //return size of data_set
    
}

void insertion_sort(int size){
    
    int i,j,key;
    
    for (j=1; j<size; j++){
        key = data_set[j];
        i = j-1;
        while(i>=0 && data_set[i]>key){
            data_set[i+1] = data_set[i];
            --i;
        }
        data_set[i+1] = key;
    }
}

void write_sorted_data(char *file_path, int size){
    
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