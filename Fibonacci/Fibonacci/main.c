//
//  main.c
//  Fibonacci
//
//  Created by Sang-Gyeong Jo on 2016. 10. 15..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#include "LargeNumber.h"
#include "Fibonacci.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    //large_int li_1 = new_li("1");
    //large_int li_2 = new_li("2");

    //printf("%s\n", fibo_array(900000).num);
    printf("%s\n", fib_rec_sqr(cast_from(1)).num);
    //printf("%llu\n",fib(50));
    
    //free(li_1.num);
    //free(li_2.num);
    
    return 0;
}
