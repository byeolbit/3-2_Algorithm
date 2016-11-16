//
//  main.c
//  SpanningTree
//
//  Created by Sang Gyeong Jo on 2016. 11. 16..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#include <stdio.h>
#include "PrimMST.h"

int main(int argc, const char * argv[]) {
    
    build_path_static();
    prim(0);
    
    return 0;
}
