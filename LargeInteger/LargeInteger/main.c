//
//  main.c
//  LargeInteger
//
//  Created by Sang-Gyeong Jo on 2016. 10. 16..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#include "LargeNumber.h"

void test_li_cmp ();

int main(int argc, const char * argv[]) {
    
    test_li_cmp();
    
    return 0;
}

void test_li_cmp ()
{
    large_int li_test_a = new_li("1231231231231231345315114321344243");
    large_int li_test_b = new_li("1231231231231231345315114371344243");
    
    printf("%s\n",li_comp(li_test_a, li_test_b).num);
}
