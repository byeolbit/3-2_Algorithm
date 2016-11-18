//
//  Knapsack.h
//  Knapsack
//
//  Created by Sang Gyeong Jo on 2016. 11. 18..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//
//

#ifndef Knapsack_h
#define Knapsack_h

#include "Essential.h"

#define MINWEIGHT 1     //Min weight of knapsack
#define MAXWEIGHT 50    //Max weight of knapsack
#define MAXITEM 10000    //Max number of item

int knap_w;     //Weight of knapsack
int item[MAXITEM][MAXITEM];     //Data of items. Value and Weight
int OPT_tbl[MAXWEIGHT][MAXITEM];  //OPT table

void get_opt(int i, int w);     //Get OPT table
void get_best();                //Get best answer from opt table
void get_knap_weight();         //Get weight of knapback
void get_data(FILE *fp);        //Get problem data from datafile
int chk_weight_range(int i);    //Validate weight of knapsack

int chk_weight_range(int i)
{
    return i <= MAXWEIGHT && i >= MINWEIGHT;
}

void get_knap_weight()
{
    while(1)
    {
        printf("Input the weight of knpasack(1~50) : ");
        scanf("%d",&knap_w);
        if(chk_weight_range(knap_w)) break;
        printf("Wrong range!\n");
    }
}

void get_data(FILE *fp)
{
    for(int i = 0; !feof(fp); i++)
        fscanf(fp,"%d,%d,%d\n",&item[i][0],&item[i][0],&item[i][1]);
    fclose(fp);
}

void get_opt(int i, int w)
{
    int best_w; //best weight in n-weight
    
}





#endif /* Knapsack_h */
