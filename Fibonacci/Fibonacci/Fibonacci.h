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
    if ( n == 0 )
        return cast_from(0);
    if ( n < 3 )
        return cast_from(1);
    
    
    large_int *fib_arr = calloc(n, sizeof(large_int) );
    
    int i = 0;
    fib_arr[i] = new_li("0");
    fib_arr[++i] = new_li("1");
    i++;
    
    while ( i <= n )
    {
        fib_arr[i] = li_plus(fib_arr[i-2], fib_arr[i-1]);
        i++;
    }
    
    large_int result = new_li(fib_arr[n].num);
    
    for ( i = 0 ; i < n ; i++ )
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
        for ( int j = 0 ; j < 2 ; j ++ )
            result[i][j] = cast_from(0);
    }
    
    for ( int i = 0 ; i < 2; i++ )
    {
        for ( int j = 0 ; j < 2 ; j ++ )
        {
            for ( int k = 0 ; k < 2 ; k ++ )
            {
                result[i][j] = li_plus( li_mul( mat_a[i][k], mat_b[k][j] ), result[i][j] );
            }
        }
    }
    return result;
}

large_int **fib_pow ( large_int **mat_A, large_int **fib_mat, large_int n )
{
    LI_ONE
    LI_TWO
    
    if ( li_comp( n, li_one ) > 0 )
    {
        mat_A = fib_pow(mat_A, fib_mat, li_div(n, li_two));
        mat_A = fib_mul(mat_A, mat_A);
        
        if( li_is_odd( n ) )
            mat_A = fib_mul(mat_A, fib_mat);

    }
    
    free(li_one.num);
    free(li_two.num);
    
    return mat_A;
}

large_int fib_rec_sqr ( large_int n )
{
    LI_ZERO
    LI_ONE
    
    if ( !li_comp(n, li_zero) )
    {
        free(li_one.num);
        free(li_zero.num);
        return n;
    }
    
    
    if ( !li_comp(n, li_one) )
    {
        free(li_one.num);
        free(li_zero.num);
        return n;
    }
    
    free(li_one.num);
    free(li_zero.num);
    
    large_int **fib_mat = calloc(2,sizeof(large_int*));
    fib_mat[0] = calloc(2,sizeof(large_int));
    fib_mat[1] = calloc(2,sizeof(large_int));
    
    fib_mat[0][0] = cast_from(1);
    fib_mat[0][1] = cast_from(1);
    fib_mat[1][0] = cast_from(1);
    fib_mat[1][1] = cast_from(0);
    
    large_int **fib_mat_a = calloc(2,sizeof(large_int*));
    fib_mat_a[0] = calloc(2,sizeof(large_int));
    fib_mat_a[1] = calloc(2,sizeof(large_int));
    
    fib_mat_a[0][0] = cast_from(1);
    fib_mat_a[0][1] = cast_from(1);
    fib_mat_a[1][0] = cast_from(1);
    fib_mat_a[1][1] = cast_from(0);
    
    large_int result = fib_pow(fib_mat, fib_mat_a, n)[0][1];
    
    for ( int i = 0 ; i < 2; i++ )
    {
        for ( int j = 0 ; j < 2 ; j ++ )
        {
            free(fib_mat_a[i][j].num);
            free(fib_mat[i][j].num);
        }
    }
    
    return result;
}

large_int fib_sqr ( large_int n )
{
    LI_ZERO
    LI_ONE
    LI_TWO
    
    if ( !li_comp(n, li_zero) )
    {
        free(li_one.num);
        free(li_zero.num);
        return n;
    }
    
    
    if ( !li_comp(n, li_one) )
    {
        free(li_one.num);
        free(li_zero.num);
        return n;
    }
    
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
    
    while ( li_comp(n, li_zero) > 0 )
    {
        if( li_is_odd( n ) )
            ret_mat = fib_mul(ret_mat, fib_mat);

        fib_mat = fib_mul(fib_mat, fib_mat);
    
        n = li_div(n, li_two);
    }
    
    large_int result = new_li( ret_mat[0][1].num );
    
    for ( int i = 0 ; i < 2; i++ )
    {
        for ( int j = 0 ; j < 2 ; j ++ )
        {
            free(ret_mat[i][j].num);
            free(fib_mat[i][j].num);
        }
    }
    
    free(li_zero.num);
    free(li_one.num);
    free(li_two.num);
    
    return result;
}

#endif /* Fibonacci_h */
