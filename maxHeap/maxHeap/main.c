//
//  main.c
//  maxHeap
//
//  Created by Sang-Gyeong Jo on 2016. 9. 27..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#include "Heap.h"

int main(int argc, const char * argv[]) {
    
    struct priority_queue p_queue;
    
    p_queue = build_heap_data(open_file("/Users/sanggyeongjo/git/3-2_Algorithm/maxHeap/maxHeap/data03.txt", "r+"));
    
    print_queue(p_queue);
    
}
