#ifndef TRUMP_H
#define TRUMP_H

#define TRUMPCARD 52    //トランプのカード
#define SUANK_MAX 13    //ひとつの柄のトランプの最大値
#define SPADE 0         //スペード
#define DIAMOND 1       //ダイヤ
#define HEART 2         //ハート
#define CLOVER 3        //クローバー

#define CARD_X 4    //配置されるカードの行数
#define CARD_Y 13   //配置されるカードの列数
#define SHUFFLE 100 //シャッフルする回数
#define NONUMBER 0 //入力や表示が何もない時

//送られてきた値をトランプに変換
char* Make_trump(int*, int);

#endif