//
//  main.c
//  Fibonacci
//
//  Created by Sang-Gyeong Jo on 2016. 10. 15..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#include "LargeNumber.h"
#include "Fibonacci.h"
#include <time.h>

void run_test ();
void test_rec (int n);
void test_arr (int n);
void test_squ (int n);
void test_squ_2 (int n);


int main(int argc, const char * argv[]) {

    run_test ();
    
    return 0;
}

void test_rec (int n)
{
    LI_ONE
    LI_TWO
    printf("---------------------------------------------\n");

    for ( int i = 0 ;  i <= n ; i++ )
    {
        //if ( i>10 && i%10 == 1 ) printf("---------------------------------------------\n");
        
        large_int _n = cast_from(i);
        clock_t start_time = clock();
        large_int r = fibo_rec(_n, li_one, li_two);
        clock_t end_time = clock();
        
        float msec = (((float)end_time - start_time) / CLOCKS_PER_SEC);
        
        printf("f<%3d> = %s\t\t\t\t\t%0.10f sec\n",i,r.num,msec);
    }
    printf("---------------------------------------------\n");

    free(li_one.num);
    free(li_two.num);
}

void test_arr (int n)
{
    printf("---------------------------------------------\n");
    
    for ( int i = 0 ;  i <= n ; i++ )
    {
        //if ( i>10 && i%10 == 1 ) printf("---------------------------------------------\n");
        
        clock_t start_time = clock();
        large_int r = fibo_array(i);
        clock_t end_time = clock();
        
        float msec = (((float)end_time - start_time) / CLOCKS_PER_SEC);
        printf("f<%3d> = %s\t%0.10f sec\n",i,r.num,msec);
        
        free(r.num);
    }
    printf("---------------------------------------------\n");

}

void test_squ (int n)
{
    printf("---------------------------------------------\n");
    
    for ( int i = 0 ;  i <= n ; i++ )
    {
        //if ( i>10 && i%10 == 1 ) printf("---------------------------------------------\n");
        
        large_int _n = cast_from(i);
        clock_t start_time = clock();
        large_int r = fib_rec_sqr(_n);
        clock_t end_time = clock();
        
        float msec = ((float)(end_time - start_time) / CLOCKS_PER_SEC);
        
        printf("f<%3d>\t=\t%s\t\t\t\t\t%0.10f sec\n",i,r.num,msec);
    }
    printf("---------------------------------------------\n");
}

void test_squ_2 (int n)
{
    printf("---------------------------------------------\n");
    
    for ( int i = 0 ;  i <= n ; i++ )
    {
        //if ( i>10 && i%10 == 1 ) printf("---------------------------------------------\n");
        
        large_int _n = cast_from(i);
        clock_t start_time = clock();
        large_int r = fib_sqr(_n);
        clock_t end_time = clock();
        
        float msec = ((float)(end_time - start_time) / CLOCKS_PER_SEC);
        printf("f<%3d>\t=\t%s\t\t\t\t\t%0.10f sec\n",i,r.num,msec);
    }
    printf("---------------------------------------------\n");
}

void run_test ()
{
    int test_case = -1;
    int type = 0;
    
    while(!type)
    {
        printf("테스트 하고자 하는 알고리즘을 선택해주세요\n1. Recursive\n2. Array\n3. Recursive squaring\n");
        scanf("%d",&type);
        printf("테스트 하고자 하는 최대 숫자를 입력해주세요(양의정수)\n");
        while (test_case<0)
        {
            scanf("%d",&test_case);
            if ( test_case < 0 )
                printf("0이상의 정수를 입력해주세요\n");
        }
        switch (type)
        {
            case 1:
                if( test_case > 40 )
                    printf("주의! 40번째 수 위로는 연산이 오래 걸리거나 메모리가 부족할 수 있습니다.\n");
                test_rec(test_case);
                break;
            case 2:
                test_arr(test_case);
                break;
            case 3:
                test_squ(test_case);
                break;
            case 4:
                test_squ_2(test_case);
                break;
            default:
                printf("올바른 번호를 입력해주세요\n");
        }
    }
}
