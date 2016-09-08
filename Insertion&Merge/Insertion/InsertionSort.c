//
//  InsertionSort.c
//  
//
//  Created by Sang Gyeong Jo on 2016. 9. 8..
//
//

#include <stdio.h>

int main(void){
    FILE *fp
    char *str;
    int buff_size;
    
    buff_size = 1024;
    
    if (!(fp = fopen("./data02.txt", "r"))){
        perror("File open error!");
        exit(1);
    }
    
    fclose(fp);
}