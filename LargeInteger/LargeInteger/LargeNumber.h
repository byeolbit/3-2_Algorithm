//
//  LargeNumber.h
//  Datatype for calculate over 64-bit unsgined integer
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

large_int li_comp( large_int ln_a, large_int ln_b );

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

large_int li_comp ( large_int ln_a, large_int ln_b )
{
    if ( ln_a.size > ln_b.size ) return ln_a;
    else if ( ln_a.size < ln_b.size ) return ln_b;
    else
    {
        int i_cmp = 0;
        int size = ( int ) ln_a.size;
        
        while ( i_cmp < size )
        {
            int a_cmp = ln_a.num[i_cmp]-'0';
            int b_cmp = ln_b.num[i_cmp]-'0';
            
            if ( a_cmp > b_cmp )
                return ln_a;
            else if ( a_cmp < b_cmp )
                return ln_b;
            
            i_cmp++;
        }
        
        return new_li( NULL );
    }
    
}

large_int li_plus ( large_int ln_a, large_int ln_b )
{
    large_int li_result;
    
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
