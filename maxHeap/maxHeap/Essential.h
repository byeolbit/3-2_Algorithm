//
//  Essential.h
//  maxHeap
//
//  Created by Sang-Gyueong Jo on 2016. 9. 27..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#ifndef Essential_h
#define Essential_h

#include <stdio.h>
#include <stdlib.h>

FILE *open_file(char *file_path, char *op);

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



#endif /* Essential_h */
