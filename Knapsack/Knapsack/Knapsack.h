//
//  Knapsack.h
//  Knapsack
//
//  Created by Sang Gyeong Jo on 2016. 11. 18..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//
//  System will do memory management
//

#ifndef Knapsack_h
#define Knapsack_h

#include "Essential.h"

#define MINWEIGHT 1     //Min weight of knapsack
#define MAXWEIGHT 50    //Max weight of knapsack
#define MAXITEM 2000    //Max number of item

int knap_w;     //Weight of knapsack
int item[MAXITEM][MAXITEM];     //Data of items. Value and Weight
int OPT_tbl[MAXWEIGHT][MAXITEM];  //OPT table

void get_opt(int i, int w);     //Get OPT table
void get_best();                //Get best answer from opt table
void get_data(FILE *fp);        //Get problem data from datafile
int chk_weight_range(int i);    //Validate weight of knapsack




#endif /* Knapsack_h */
