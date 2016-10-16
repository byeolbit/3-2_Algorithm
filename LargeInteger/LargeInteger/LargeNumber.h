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

large_int li_op ( large_int ln_a, large_int ln_b, char op );
large_int li_plus ( large_int ln_a, large_int ln_b );
large_int li_minus ( large_int ln_a, large_int ln_b );
large_int li_mul ( large_int ln_a, large_int ln_b );
large_int li_div ( large_int ln_a, large_int ln_b );

int li_comp( large_int ln_a, large_int ln_b );

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
    }
    
    return new_li;
}

large_int get_li ()
{
    large_int new_li;
    
    new_li.num = NULL;
    
    printf("input number\n");
    while(getline(&new_li.num,&new_li.size, stdin) == -1) printf("No input\n");
    
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
        li_result.num = ( char* )malloc( li_result.size );
    } else
    {
        chk = 1;
        ttl_sz = ( int ) ln_b.size;
        lss_sz = ( int ) ln_a.size;
        li_result.size = ln_b.size;
        li_result.num = ( char* )malloc( li_result.size );
    }
    
    int i = 0;
    int carry = 0;
    while( i < lss_sz )
    {
        int result = ( int )( ln_a.num[lss_sz-i]-'0' ) + ( int )( ln_b.num[lss_sz-i]-'0' ) + carry;
        
        carry = result/10;
        result = result%10;
        char result_c = '0' + result;
        
        li_result.num[li_result.size-i] = result_c;
    }
    
    while( i < ttl_sz)
    {
        int result = 0;
        
        if ( chk ) result = ( int )( ln_b.num[ttl_sz-i] - '0' ) + carry;
        else result = ( int )( ln_a.num[ttl_sz-i] - '0' ) + carry;
        
        carry = result/10;
        result = result%10;
        char result_c = '0' + result;
        
        li_result.num[li_result.size-i] = result_c;
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
    large_int li_result;
    
    return li_result;
}

large_int li_mul ( large_int ln_a, large_int ln_b )
{
    large_int li_result;
    
    return li_result;
}

large_int li_div ( large_int ln_a, large_int ln_b )
{
    large_int li_result;
    
    return li_result;
}


large_int li_op ( large_int ln_a, large_int ln_b, char op )
{
    large_int result;
    
    switch( op )
    {
        case '+' :
            result = li_plus(ln_a, ln_b);
            break;
            
        case '-' :
            result = li_minus(ln_a, ln_b);
            break;
            
        case '*' :
            result = li_mul(ln_a, ln_b);
            break;
            
        case '/' :
            result = li_div(ln_a, ln_b);
            break;
            
        default :   //error
            break;
            
    }
    
    return result;
}

#endif /* LargeNumber_h */
