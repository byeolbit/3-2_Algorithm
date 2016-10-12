//
//  main.c
//  maxHeap
//
//  Created by Sang-Gyeong Jo on 2016. 9. 27..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#include "Heap.h"

void get_menu(struct priority_queue *p_queue);
struct node get_node();

int do_insert_node(struct priority_queue *p_queue);
int do_get_max(struct priority_queue *p_queue);
int do_extract_max(struct priority_queue *p_queue);
int do_increase_key(struct priority_queue *p_queue);
int do_h_delete(struct priority_queue *p_queue);
int check_queue(struct priority_queue *p_queue);
int check_exist(struct node target_node);

int main(int argc, const char * argv[]) {
    
    struct priority_queue p_queue;
    
    p_queue = build_heap_data(open_file("data03.txt", "r+"));
    build_max_heap(&p_queue);
    print_queue(&p_queue);
    printf("\n원하는 메뉴에 해당하는 숫자를 입력하세요");
    printf("\n--------------------------------------------------------\n");
    printf("1. 작업 추가\t\t2. 최대값\t\t3. 최대 우선순위 작업 처리\n");
    printf("4. 원소 키값 증가\t5. 작업제거\t6. 종료\n");
    printf("--------------------------------------------------------\n");
    get_menu(&p_queue);
}

void get_menu(struct priority_queue *p_queue){
    int menu_num = -1;
    scanf("%d",&menu_num);

    do{
        switch(menu_num){
            case 1 :
                menu_num = do_insert_node(p_queue);
                break;
            case 2 :
                menu_num = do_get_max(p_queue);
                break;
            case 3 :
                menu_num = do_extract_max(p_queue);
                break;
            case 4 :
                menu_num = do_increase_key(p_queue);
                break;
            case 5:
                menu_num = do_h_delete(p_queue);
                break;
            case 6:
                free(p_queue->heap);
                exit(0);
            case 0:
                printf("\n원하는 메뉴에 해당하는 숫자를 입력하세요");
                printf("\n--------------------------------------------------------\n");
                printf("1. 작업 추가\t\t2. 최대값\t\t3. 최대 우선순위 작업 처리\n");
                printf("4. 원소 키값 증가\t5. 작업제거\t6. 종료\n");
                printf("--------------------------------------------------------\n");
                scanf("%d",&menu_num);
                break;
            default:
                printf("\n잘못된 입력입니다. 원하는 메뉴에 해당하는 숫자를 입력하세요");
                printf("\n--------------------------------------------------------\n");
                printf("1. 작업 추가\t\t2. 최대값\t\t3. 최대 우선순위 작업 처리\n");
                printf("4. 원소 키값 증가\t5. 작업제거\t6. 종료\n");
                printf("--------------------------------------------------------\n");
                scanf("%d",&menu_num);
                break;
        }
    } while (1);
    
}

struct node get_node(int k, char *v){
    struct node new_node;
    new_node.key = k;
    new_node.value = v;
    
    return new_node;
}

int do_insert_node(struct priority_queue *p_queue){
    
    int new_key;
    char new_value[4096];
    
    printf("다음의 형식으로 추가할 작업을 입력해주세요.\n형식 : 우선순위, 작업이름\n");
    scanf("%d, %s",&new_key, new_value);
    insert(p_queue, get_node(new_key, new_value));
    print_queue(p_queue);
    
    return 0;
}

int do_get_max(struct priority_queue *p_queue){
    
    if(check_queue(p_queue)) return 0;
    
    printf("최대 우선순위 작업은 : %d, %s 입니다.\n\n",max(p_queue).key, max(p_queue).value);
    print_queue(p_queue);
    
    return 0;
    
}

int do_extract_max(struct priority_queue *p_queue){
    
    if(check_queue(p_queue)) return 0;
    
    struct node extracted = extract_max(p_queue);
    
    printf("처리된 작업 : %d, %s\n", extracted.key, extracted.value);
    print_queue(p_queue);
    
    return 0;
    
}

int do_increase_key(struct priority_queue *p_queue){
    
    if(check_queue(p_queue)) return 0;
    
    struct node increased;
    
    int key;
    int inc;
    
    printf("우선순위를 증가시키고 싶은 작업의 우선순위와, 증가치를 입력해주세요.\n형식 : 우선순위, 증가량\n");
    scanf("%d, %d",&key, &inc);
    increased = increase_key(p_queue, key, inc);
    
    if(check_exist(increased)) return 0;
    
    printf("작업 결과 : %d, %s\n",increased.key, increased.value);
    
    print_queue(p_queue);
    
    return 0;

}

int check_exist(struct node target_node) {
    if(target_node.key == -1){
        printf("존재하지 않는 작업입니다.\n");
        return 1;
    }
    
    return 0;
}

int do_h_delete(struct priority_queue *p_queue){
    
    if(check_queue(p_queue)) return 0;

    struct node deleted;
    
    int key;
    
    printf("삭제하고 싶은 작업의 우선순위를 입력해주세요.\n");
    scanf("%d",&key);
    deleted = h_delete(p_queue, key);
    
    if(check_exist(deleted)) return 0;
    
    printf("삭제된 작업 : %d, %s\n",deleted.key, deleted.value);
    
    print_queue(p_queue);
    
    return 0;
    
}

int check_queue(struct priority_queue *p_queue) {
    if(p_queue->size == 0){
        printf("더 이상 처리할 작업목록이 없습니다.\n");
        return 1;
    }
    return 0;
}
