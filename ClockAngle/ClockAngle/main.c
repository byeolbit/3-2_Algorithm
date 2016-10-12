//
//  main.c
//  ClockAngle
//
//  Created by Sang-Gyeong Jo on 2016. 10. 7..
//  Copyright © 2016년 Sang-Gyeong Jo. All rights reserved.
//

#include <stdio.h>

void run_program();
void get_input(int *hour, int *min);
void print_result(int hour, int min, float result_angle);

float calc_angle(int hour, int min);
float get_difference(float h_angle, float m_angle);
float get_hour_angle(int hour);
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
        if(*hour < 0 || *hour > 12) printf("Wrong hour input\n");
        else if(*min < 0 || *min >59) printf("Wrong minute input\n");
        else break;
    }
}

float calc_angle(int hour, int min)
{
    return get_difference(get_hour_angle(hour), get_min_angle(min));
}

void run_program()
{
    while(1)
    {
        int hour, min;
        get_input(&hour, &min);
        print_result(hour, min, calc_angle(hour, min));
    }
    
}
