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
large_int fib_rec_sqr ( large_int n );

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

large_int **fib_mul ( large_int **mat_a, large_int **mat_b )
{
    large_int **result = calloc(2,sizeof(large_int*));
    result[0] = calloc(2,sizeof(large_int));
    result[1] = calloc(2,sizeof(large_int));
    
    for ( int i = 0 ; i < 2; i++ )
    {
        for ( int j = 0 ; j < 2 ; j ++ ){
            result[i][j] = li_plus( li_mul( mat_a[i][0], mat_b[0][j] ), li_mul( mat_a[i][1], mat_a[1][j] ) );
            printf("a[%d][0] * b[0][%d] + a[%d][1] * b[1][%d]\n",i,j,i,j);
            printf("%s*%s + %s*%s = %s\n", mat_a[i][0].num, mat_b[0][j].num,  mat_a[i][1].num, mat_a[1][j].num, result[i][j].num );
        }
    }
    return result;
}

large_int fib_rec_sqr ( large_int n )
{
    
    large_int i = cast_from(1);
    large_int li_one = cast_from(1);
    large_int li_two = cast_from(2);
    
    large_int **fib_mat = calloc(2,sizeof(large_int*));
    fib_mat[0] = calloc(2,sizeof(large_int));
    fib_mat[1] = calloc(2,sizeof(large_int));
    
    fib_mat[0][0] = cast_from(1);
    fib_mat[0][1] = cast_from(1);
    fib_mat[1][0] = cast_from(1);
    fib_mat[1][1] = cast_from(0);
    
    large_int **ret_mat = calloc(2,sizeof(large_int*));
    ret_mat[0] = calloc(2,sizeof(large_int));
    ret_mat[1] = calloc(2,sizeof(large_int));
    
    ret_mat[0][0] = cast_from(1);
    ret_mat[0][1] = cast_from(0);
    ret_mat[1][0] = cast_from(0);
    ret_mat[1][1] = cast_from(1);
    
    if ( !li_comp( n, cast_from( 0 ) ) )
        return ret_mat[0][1];
    
    while ( li_comp(i, n) < 1 )
    {
        if( li_is_odd( i ) )
            ret_mat = fib_mul(ret_mat, fib_mat);
        
        fib_mat = fib_mul(fib_mat, fib_mat);
        
        //i = li_plus(i, li_one);
        i = li_mul(i, li_two);
        
        printf("[%s][%s]\n[%s][%s]\n",ret_mat[0][0].num,ret_mat[0][1].num,ret_mat[1][0].num,ret_mat[1][1].num );
        printf("[%s][%s]\n[%s][%s]\n\n",fib_mat[0][0].num,fib_mat[0][1].num,fib_mat[1][0].num,fib_mat[1][1].num );
    }
    
    return ret_mat[0][1];
}

#endif /* Fibonacci_h */
