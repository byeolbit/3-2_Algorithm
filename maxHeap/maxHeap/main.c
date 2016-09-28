//
//  main.c
//  maxHeap
//
//  Created by Sang-Gyeong Jo on 2016. 9. 27..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#include "Heap.h"

void get_menu(struct priority_queue p_queue);
struct node get_node();

int do_insert_node(struct priority_queue p_queue);
void do_get_max();
void do_extract_max();
void do_increase_key();
void do_h_delete();


int main(int argc, const char * argv[]) {
    
    struct priority_queue p_queue;
    
    p_queue = build_heap_data(open_file("/Users/josanggyeong/Dropbox/학교/2016년 3학년 2학기/3-2_Algorithm/maxHeap/maxHeap/data03.txt", "r+"));
    
    build_max_heap(p_queue);
    
    print_queue(p_queue);
    get_menu(p_queue);
}

void get_menu(struct priority_queue p_queue){
    int menu_num = -1;
    scanf("%d",&menu_num);

    do{
        switch(menu_num){
            case 1 :
                menu_num = do_insert_node(p_queue);
                break;
            case 2 :
                do_get_max();
                menu_num = -1;
                break;
            case 3 :
                do_extract_max();
                menu_num = -1;
                break;
            case 4 :
                do_increase_key();
                menu_num = -1;
                break;
            case 5:
                do_h_delete();
                menu_num = -1;
                break;
            case 6:
                exit(0);
                break;
            case -1:
                printf("\n입력 오류입니다. 원하는 메뉴에 해당하는 숫자를 입력하세요");
            default:
                printf("\n--------------------------------------------------------\n");
                printf("1. 작업 추가\t\t2. 최대값\t\t3. 최대 우선순위 작업 처리\n");
                printf("4. 원소 키값 증가\t5. 작업제거\t6. 종료\n");
                printf("--------------------------------------------------------\n");
                scanf("%d",&menu_num);
                break;
        }
    } while (menu_num == -1);
    
}

struct node get_node(int k, char *v){
    struct node new_node;
    new_node.key = k;
    new_node.value = v;
    
    return new_node;
}

int do_insert_node(struct priority_queue p_queue){
    
    int new_key;
    char new_value[4096];
    
    printf("다음의 형식으로 추가할 작업을 입력해주세요. 우선순위, 작업이름\n");
    scanf("%d, %s",&new_key, new_value);
    insert(p_queue, get_node(new_key, new_value));
    
    return 1;
}
void do_get_max(){
    
}
void do_extract_max(){
    
}
void do_increase_key(){
    
}
void do_h_delete(){
    
}
