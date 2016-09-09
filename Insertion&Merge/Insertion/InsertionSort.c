//
//  InsertionSort.c
//  
//
//  Created by Sang Gyeong Jo on 2016. 9. 8..
//
//

#include <stdio.h>

int main(void){
    
    
    FILE *fp;           //File pointer
    
    int **arr;          //2d array pointer
    char ch;            //variable for read data
    int test_case = 0;  //iterator for test cases
    int size = 0;       //iterator for array size
    
    
    if ((fp = fopen("./data02.txt", "r"))){
    /* File opening exception handling */
        
        perror("File open error!");
        exit(1);
    } else {
      /* Read file data and store to memory */
        
        //init 2D array
        arr = (int**) malloc (sizeof(int*) * (test_case+1));
        arr[test_case] = (int*) malloc (sizeof(int) * (size+1));
        
        /* Read data and store at each case */
        while(EOF != (ch = fgetc(fp))){
            
            /* Read a case */
            while(ch != ','){
                //
                arr[test_case][size] = atoi(ch);
                arr[test_case] = realloc(&arr[test_case], sizeof(int) * (size+1));
            
                //read next data
                ch = fgetc(fp);
                
                //increase interator
                ++size;
            }
            
            //init iterators
            ++test_case;
            size = 0;
            
            arr = realloc(arr, sizeof(int) * (test_case+1));
        }
    }
    
    fclose(fp); //close file pointer
}