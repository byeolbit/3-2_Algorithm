/*
 *  Essential.h
 *  maxHeap
 *
 *  Created by Sang-Gyueong Jo on 2016. 9. 27..
 *  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
 *
 *  Modified at 2016.10.5
 *  -Add get_random function
 *  -Add swap_int_arr function
 *  -Add fprint_int_array function
 *  -Add time checking function
 */

#ifndef Essential_h
#define Essential_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct point
{
    double x,y;
};

typedef struct point point;

struct point_set
{
    int size;
    point *data;
};

typedef struct point_set point_s;

clock_t start_time;
clock_t end_time;

FILE *open_file(char *file_path, char *op);
int get_random(int s, int e);
void set_timer();
void stop_timer();
float calculate_time();
void swap_int_arr(int *arr, int a, int b);
void fprint_int_array(int *arr, int size, FILE *fp, int op);

//Read file from file path and return File pointer
FILE *open_file(char *file_path, char *op)
{
    FILE *fp;
    
    // File opening exception handling
    if(!(fp = fopen(file_path, op)))
    {
        perror("File open error!");
        exit(1);
    }
    return fp;
}

// get random integer number between s and e(s <= x <= e)
int get_random(int s, int e)
{
    srand((unsigned)time(NULL)+(unsigned)getpid());
    return (rand() % (e-s+1)) + s;
}

// swap two element from int array
void swap_int_arr(int *arr, int a, int b)
{
    int t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}

// this does not work

int get_size_arr(int *arr)
{
    int size;
    size = *(arr - sizeof(int));
    return size;
}

// print data to file op 1 is print console
void fprint_int_array(int *arr, int size, FILE *fp, int op)
{
    int i = 0;
    while(i<size)
    {
        fprintf(fp,"%d",arr[i]);
        if(++i != size) fprintf(fp,",");
    }
    
    fclose(fp);
    
    if (op == 1)
    {
        i = 0;
        while(i<size)
        {
            printf("%d",arr[i]);
            if(++i != size) printf(",");
        }
    }
    printf("\n");
    
}

// functions for check performance
void set_timer(){
    start_time = clock();
}

void stop_timer(){
    end_time = clock();
}

float calculate_time(){
    float msec = (((float)end_time - start_time) / CLOCKS_PER_SEC) * 1000;
    printf("%f Milliseconds\n",msec);
    return msec;
}

#endif /* Essential_h */
