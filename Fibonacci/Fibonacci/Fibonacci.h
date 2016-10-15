//
//  Fibonacci.h
//  Fibonacci
//
//  Created by Sang-Gyeong Jo on 2016. 10. 15..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#ifndef Fibonacci_h
#define Fibonacci_h

#include <stdlib.h>

int fibo_rec(int n);
int *fibo_array(int n);
int *fibo_rec_sqr(int n);

int fibo_rec(int n)
{
    if ( n<2 ) return n;
    return fibo_rec( n-1 ) + fibo_rec( n-2 );
}

int *fibo_array(int n)
{
    int *fib_arr = calloc(n,sizeof(int));
    int i = 0;
    fib_arr[i] = 0;
    fib_arr[i++] = 1;
    
    while ( i<n ) fib_arr[i++] = fib_arr[i-1] + fib_arr[i];
    
    return fib_arr;
}

int *fibo_req_sqr(int n)
{
    return 0;
}



#endif /* Fibonacci_h */
