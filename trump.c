#include <stdio.h>
#include "trump.h"

//送られてきた乱数をトランプに変換
char* Make_trump(int* value, int number){
    char *card;                          //戻り値用変数
    char suank[] = {'S', 'D', 'H', 'C'}; //トランプの柄

        if(number >= 1 && number <= 13){
            card = &suank[SPADE];
            *value = number;
        }
        else if(number >= 14 && number <= 26){
            card = &suank[DIAMOND];
            *value = number - SUANK_MAX;
        }
        else if(number >= 27 && number <= 39){
            card = &suank[HEART];
            *value = number - SUANK_MAX * 2;
        }
        else if(number >= 40 && number <= 52){
            card = &suank[CLOVER];
            *value = number - SUANK_MAX * 3;
        }
        return card;
}