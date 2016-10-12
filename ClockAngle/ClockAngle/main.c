//
//  main.c
//  ClockAngle
//
//  Created by Sang-Gyeong Jo on 2016. 10. 7..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

void run_program();
void get_input(int *hour, int *min);
void print_result(int hour, int min, float result_angle);

float calc_angle(int hour, int min);
float get_difference(float h_angle, float m_angle);
float get_hour_angle(int hour, int min);
float get_min_angle(int min);


int main(int argc, const char * argv[])
{
    run_program();
    return 0;
}

void get_input(int *hour, int *min)
{
    while(1){
        printf("Please input time(hh:mm)\n");
        scanf("%d:%d",hour, min);
        if(*hour < 0 || *hour > 11) printf("Wrong hour input\n");
        else if(*min < 0 || *min >59) printf("Wrong minute input\n");
        else break;
    }
}

float get_difference(float h_angle, float m_angle)
{
    if(h_angle>m_angle) return h_angle - m_angle;
    else return m_angle - h_angle;
}

float get_hour_angle(int hour, int min)
{
    return (hour*30) + (min*0.5);
}

float get_min_angle(int min)
{
    return min*6;
}

float calc_angle(int hour, int min)
{
    return get_difference(get_hour_angle(hour, min), get_min_angle(min));
}

void print_result(int hour, int min, float result_angle)
{
    printf("The angle difference of %2d:%2d is %0.1f\n",hour, min, result_angle);
}

void ask_exit()
{
    while(1){
        char ans;
        printf("Exit?(y/n)\n");
        scanf("%c", &ans);
        if(ans =='Y' || ans=='y') exit(1);
        else if(ans == 'N'|| ans == 'n') break;
        else printf("Wrong input\n");
    }
}

void run_program()
{
    while(1)
    {
        int hour, min;
        get_input(&hour, &min);
        print_result(hour, min, calc_angle(hour, min));
        ask_exit();
    }
    
}
