#ifndef TRUMP_H
#define TRUMP_H

#define TRUMPCARD 52    //トランプのカード
#define SUANK_MAX 13    //ひとつの柄のトランプの最大値
#define SPADE 0         //スペード
#define DIAMOND 1       //ダイヤ
#define HEART 2         //ハート
#define CLOVER 3        //クローバー

//送られてきた値をトランプに変換
char* Make_trump(int*, int);

#endif