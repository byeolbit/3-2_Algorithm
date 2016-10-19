//
//  LargeNumber.h
//  Datatype for calculate over 64-bit unsgined integer
//
//  생각해볼 것 : 비트연산을 통한 사칙연산
//
//  Created by Sang-Gyeong Jo on 2016. 10. 13..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//


#ifndef LargeNumber_h
#define LargeNumber_h

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct large_int_num large_int;

struct large_int_num { size_t size; char *num; };

large_int new_li ( const char *num );
large_int cast_from ( unsigned long long num );
large_int get_li ();

void chk_vld ( large_int li );

#define LI_ZERO large_int li_zero = cast_from(0);
#define LI_ONE large_int li_one = cast_from(1);
#define LI_TWO large_int li_two = cast_from(2);

large_int li_op ( large_int li_a, large_int li_b, char op );
large_int li_plus ( large_int li_a, large_int li_b );
large_int li_minus ( large_int li_a, large_int li_b );
large_int li_mul ( large_int li_a, large_int li_b );
large_int li_div ( large_int li_a, large_int li_b );
large_int li_pow ( large_int li_a, unsigned int n );

int li_is_odd ( large_int li );

int li_comp( large_int ln_a, large_int ln_b );

void chk_vld ( large_int li )
{
    for ( int i = 0 ; i < li.size - 1 ; i++ )
    {
        int test = li.num[i] - '0';
        if ( test < 0 || test > 9 )
        {
            printf("There is none number\n");
            exit(1);
        }
    }
}

large_int new_li ( const char *num )
{
    large_int new_li;
    
    if ( num == NULL )
    {
        new_li.size = 0;
        new_li.num = NULL;
    } else
    {
        new_li.size = strlen(num);
        new_li.num = (char*)malloc(new_li.size);
        new_li.num = strcpy(new_li.num, num);
        chk_vld(new_li);
    }
    
    return new_li;
}

large_int get_li ()
{
    large_int new_li;
    
    new_li.num = NULL;
    
    printf("input number\n");
    while(getline(&new_li.num,&new_li.size, stdin) == -1) printf("No input\n");
    
    chk_vld(new_li);
    
    return new_li;
}

large_int cast_from ( unsigned long long num )
{
    large_int new_li;
    
    new_li.size = snprintf(NULL, 0, "%llu",num) + 1;
    
    new_li.num = (char*)malloc(new_li.size);
    
    snprintf( new_li.num, new_li.size,"%llu",num );
    
    new_li.size--;
    
    return new_li;
}

int li_comp ( large_int ln_a, large_int ln_b )
{
    if ( ln_a.size > ln_b.size ) return 1;
    else if ( ln_a.size < ln_b.size ) return -1;
    else
    {
        int i_cmp = 0;
        int size = ( int ) ln_a.size;
        
        while ( i_cmp < size )
        {
            int a_cmp = ln_a.num[i_cmp]-'0';
            int b_cmp = ln_b.num[i_cmp]-'0';
            
            if ( a_cmp > b_cmp )
                return 1;
            else if ( a_cmp < b_cmp )
                return -1;
            
            i_cmp++;
        }
        
        return 0;
    }
    
}

large_int li_plus ( large_int ln_a, large_int ln_b )
{
    large_int li_result;
    int lss_sz;
    int ttl_sz;
    int chk; //which is big
    
    if ( ln_a.size > ln_b.size )
    {
        chk = 0;
        ttl_sz = ( int ) ln_a.size;
        lss_sz = ( int ) ln_b.size;
        li_result.size = ln_a.size;
        li_result.num = calloc(li_result.size, sizeof(char*));
    } else
    {
        chk = 1;
        ttl_sz = ( int ) ln_b.size;
        lss_sz = ( int ) ln_a.size;
        li_result.size = ln_b.size;
        li_result.num = calloc(li_result.size, sizeof(char*));
    }
    
    int i = 0;
    int carry = 0;
    while( i < lss_sz )
    {
        int result = 0;
        
        if ( chk ) result = ( ln_a.num[lss_sz-1-i] - '0' ) + ( ln_b.num[ttl_sz-1-i] - '0' ) + carry;
        else result = ( int )( ln_a.num[ttl_sz-1-i] - '0' ) + ( int )( ln_b.num[lss_sz-1-i] - '0' ) + carry;
        
        carry = result/10;
        result = result%10;
        char result_c = '0' + result;
        
        li_result.num[li_result.size-1-i] = result_c;
        i++;
    }
    
    while( i < ttl_sz)
    {
        int result = 0;
        
        if ( chk ) result = ( int )( ln_b.num[ttl_sz-1-i] - '0' ) + carry;
        else result = ( int )( ln_a.num[ttl_sz-1-i] - '0' ) + carry;
        
        carry = result/10;
        result = result%10;
        char result_c = '0' + result;
        
        li_result.num[li_result.size-1-i] = result_c;
        i++;
    }
    
    if ( carry )
    {
        char result_c = '0' + carry;
        char *tmp = realloc(li_result.num, li_result.size++);
        memmove(tmp+1, tmp, li_result.size-1);
        tmp[0] = result_c;
        li_result.num = tmp;
    }
    
    return li_result;
}

large_int li_minus ( large_int ln_a, large_int ln_b )
{
    large_int li_result = new_li(NULL);
    int lss_sz;
    int ttl_sz;
    if ( ln_a.size >= ln_b.size )
    {
        if ( li_comp( ln_a, ln_b ) == 0 ) return new_li( "0" );
        else if ( li_comp( ln_a, ln_b ) == -1 ) return new_li(NULL);
        
        ttl_sz = ( int ) ln_a.size;
        lss_sz = ( int ) ln_b.size;
        li_result.size = ln_a.size;
        li_result.num = calloc(li_result.size, sizeof(char*));
        
    } else return li_result;
    
    int i = 0;
    int carry = 0;
    while( i < lss_sz )
    {
        int result = ( ln_a.num[ttl_sz-1-i] - '0' + carry)  - ( ln_b.num[lss_sz-1-i] - '0' );
        
        if ( result < 0 )
        {
            result = 10 + result;
            carry = -1;
        }
        else carry = 0;
        
        char result_c = '0' + result;
        
        li_result.num[li_result.size-1-i] = result_c;
        i++;
    }
    
    while( i < ttl_sz )
    {
        int result = ( ln_a.num[ttl_sz-1-i] - '0' ) + carry;
        
        if ( result < 0 )
        {
            result = 10 + result;
            carry = -1;
        } else
        {
            carry = 0;
        }
        
        char result_c = '0' + result;
        
        li_result.num[li_result.size-1-i] = result_c;
        i++;
    }
    
    if ( li_result.num[0] == '0' )
    {
        li_result.size -= 1;
        char *tmp = (char*)malloc(li_result.size);
        memmove(tmp, li_result.num+1, li_result.size);
        free(li_result.num);
        li_result.num = tmp;
    }
    
    return li_result;
}

large_int li_mul ( large_int li_a, large_int li_b )
{
    LI_ZERO
    
    if( !strcmp( li_a.num, "0" ) || !strcmp(li_b.num, "0") )
        return cast_from(0);
    
    else if ( !strcmp( li_a.num, "1" ) )
        return li_b;
    
    else if ( !strcmp( li_b.num, "1" ) )
        return li_a;
    
    large_int li_result = new_li ( "0" );
    large_int li_big;
    large_int li_less;
    
    //Select bigger number
    if ( li_comp(li_a, li_b) > 0 )
    {
        li_big = new_li( li_a.num );
        li_less = new_li( li_b.num );
    } else
    {
        li_big = new_li( li_b.num );
        li_less = new_li( li_a.num );
    }
    
    for ( int i = 0 ; i < li_less.size ; i++ )
    {
        large_int li_res_tmp = new_li( li_zero.num );
        
        for ( int j = 0 ; j < ( li_less.num[li_less.size-1]-'0' ) ; j++ )
            li_res_tmp = li_plus( li_res_tmp, li_big );
        
        if ( i )
        {
            li_res_tmp.size += i;
            char *tmp = calloc(li_res_tmp.size, sizeof(char*));
            memmove(tmp, li_res_tmp.num, li_res_tmp.size-i);
            li_res_tmp.num = tmp;
            for ( int k = 0 ; k < i ; k++ ) li_res_tmp.num[li_res_tmp.size-1-k] = '0';
        }
        
        large_int res_tmp = li_result;
        li_result = li_plus ( li_result, li_res_tmp );
        free( res_tmp.num );
        free( li_res_tmp.num );
    }
    
    return li_result;
}

large_int li_div ( large_int li_a, large_int li_b )
{
    switch ( li_comp( li_a, li_b ) ){
        case 0:
            return cast_from(1);
            break;
            
        case -1:
            return cast_from(0);
            break;
            
        default:
            break;
    }
    
    large_int li_tmp = li_a;
    large_int li_result = cast_from(0);
    
    LI_ONE
    
    while ( li_comp( li_tmp, li_b ) >= 0 )
    {
        li_tmp = li_minus(li_tmp, li_b);
        li_result = li_plus(li_result, li_one);
    }
    free(li_one.num);
    return li_result;
}

large_int li_pow ( large_int li_a, unsigned int n )
{
    large_int li_result = new_li("1");
    
    for ( int i = 0 ; i < n ; i++ ) li_result = li_mul( li_result, li_a );
    
    return li_result;
}


large_int li_op ( large_int li_a, large_int li_b, char op )
{
    large_int result;
    
    switch( op )
    {
        case '+' :
            result = li_plus(li_a, li_b);
            break;
            
        case '-' :
            result = li_minus(li_a, li_b);
            break;
            
        case '*' :
            result = li_mul(li_a, li_b);
            break;
            
        case '/' :
            result = li_div(li_a, li_b);
            break;
            
        default :   //error
            break;
            
    }
    
    return result;
}

int li_is_odd ( large_int li )  //return 1 is odd, 0 is even
{
    return ( li.num[li.size-1] - '0' ) % 2;
    
}

#endif /* LargeNumber_h */
