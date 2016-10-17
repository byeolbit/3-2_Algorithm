//
//  main.c
//  LargeInteger
//
//  Created by Sang-Gyeong Jo on 2016. 10. 16..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#include "LargeNumber.h"

void test_li_cmp ();
void test_li_plus ();
void test_li_minus ();
void test_li_mul ();
void test_li_pow ();

int main(int argc, const char * argv[]) {
    
    //test_li_cmp();
    //test_li_plus();
    //test_li_minus();
    //test_li_mul ();
    test_li_pow ();
    return 0;
}

void test_li_cmp ()
{
    large_int li_test_a = new_li("1231231231231231345315114321344243");
    large_int li_test_b = new_li("1231231231231231345315114371344243");
    
    printf("%d\n",li_comp(li_test_a, li_test_b));
    free(li_test_a.num);
    free(li_test_b.num);
}

void test_li_plus ()
{
    large_int li_test_a = new_li("1010101010101010101010101010101010101010101010101010101010101010101010110101010101010101010101010101010101");
    large_int li_test_b = new_li("101010101010101010101010101010101010101010101010101010101010101010101011010101010101010101010101010101010");
    large_int result = li_plus(li_test_a, li_test_b);
    printf("size_a = %lu, size_b = %lu, result = %lu, %s\n",li_test_a.size,li_test_b.size, result.size, result.num);
    free(li_test_a.num);
    free(li_test_b.num);
    free(result.num);
}

void test_li_minus ()
{
    large_int li_test_a = new_li("99999999999999999999999999999999999999999999999");
    large_int li_test_b = new_li("1");
    large_int result = li_minus(li_test_a, li_test_b);
    printf("size_a = %lu, size_b = %lu, result = %lu, %s\n",li_test_a.size,li_test_b.size, result.size, result.num);
    free(li_test_a.num);
    free(li_test_b.num);
    free(result.num);
}

void test_li_mul ()
{
    large_int li_test_a = new_li("99999999999999999999");
    large_int li_test_b = new_li("99999999999999999999");
    large_int result = li_mul(li_test_a, li_test_b);
    printf("size_a = %lu, size_b = %lu, result = %lu, %s\n",li_test_a.size,li_test_b.size, result.size, result.num);
    free(li_test_a.num);
    free(li_test_b.num);
    free(result.num);
}

void test_li_pow ()
{
    large_int li_test_a = new_li("2");
    large_int result = li_pow(li_test_a, 222);
    printf("size_a = %lu, size_b = %d, result = %lu, %s\n",li_test_a.size, 10, result.size, result.num);
    printf("%d\n",li_comp(result, new_li("6739986666787659948666753771754907668409286105635143120275902562304")));
    free(li_test_a.num);
    free(result.num);
}
