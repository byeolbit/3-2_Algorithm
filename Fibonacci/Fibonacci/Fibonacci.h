//
//  Fibonacci.h
//  Fibonacci
//
//  Created by Sang-Gyeong Jo on 2016. 10. 15..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#ifndef Fibonacci_h
#define Fibonacci_h

#include "LargeNumber.h"

large_int fibo_rec ( large_int n , large_int li_1, large_int li_2);
large_int fibo_array ( int n );
large_int *fibo_rec_sqr ( large_int n );

large_int fibo_rec ( large_int n , large_int li_1, large_int li_2)
{
    if ( li_comp(n, li_2 ) == -1 )
        return n;
    
    return li_plus ( fibo_rec ( li_minus ( n, li_1 ), li_1, li_2 ) ,fibo_rec ( li_minus( n, li_2 ), li_1, li_2 ) );
}

large_int fibo_array ( int n )
{
    
    large_int *fib_arr = calloc(n, sizeof(large_int) );
    
    //large_int fib_arr[82];
    
    int i = 0;
    fib_arr[i] = new_li("0");
    fib_arr[++i] = new_li("1");
    i++;
    
    while ( i <= n ){
        fib_arr[i] = li_plus(fib_arr[i-2], fib_arr[i-1]);
        i++;
    }
    
    large_int result = fib_arr[n];
    
    for ( i = 0 ; i <= n ; i++ )
        free(fib_arr[i].num);
    
    return result;
}

large_int *fibo_req_sqr ( large_int n )
{
    return 0;
}



#endif /* Fibonacci_h */
