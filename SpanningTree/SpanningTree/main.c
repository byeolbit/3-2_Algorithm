//
//  main.c
//  SpanningTree
//
//  Created by Sang Gyeong Jo on 2016. 11. 16..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#include "PrimMST.h"

int main(int argc, const char * argv[]) {
    
    int start_point = 0;
    
    build_path_static();
    prim(start_point);
    
    return 0;
}
