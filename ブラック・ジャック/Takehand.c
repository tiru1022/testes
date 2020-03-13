#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Blackjack.h"

//手札を引く処理
int Takehand(int whichturn){
    char name[2][100] = {"あなた","あいて"}; //誰の手札か判別
    int taked_hand[MAXHAND];               //引いた手札を保存する
    int count;                             //引いた手札の数
    int hand;                              //引いた値
    int sum;                               //手札の合計値
    int take_hand;                         //もう一度手札を引くかどうかの判断
    int input;
    int i;
    
    //初期化
    count = 0;
    hand = 0;
    sum = 0;
    take_hand = TRUE;
    input = 0;
    for(i = 0; i < MAXHAND; i++){
        taked_hand[i] = 0;
    }
    
    //take_handにFALSEが入るまで繰り返す
    while(take_hand == TRUE){
        count++;

        //手札を引いて、それを手札用配列に格納
        hand = rand() % MAXVALUE + 1;
        taked_hand[count] = hand;
        
        if(hand > LIMIT){//引いた手札が10を超えていた場合、10として計算
            hand = LIMIT;
        }
        sum += hand;     //合計値の計算

        if(sum > BURST){//合計値がバースト値を超えた場合、ループを抜ける
            break;
        }
        
        //もう一度引くか引かないか
        if(whichturn == 0){//自分のターンだった場合
            printf("||あなたのターンです||\n");
            printf("引いた手札：");
            for(i = 1; i <= count; i++){
                printf("%d ", taked_hand[i]);
            }
            printf("\n");

            printf("\nもう一度引きますか？  はい:0  いいえ:1\n=>");
            scanf("%d", &input);
            system("clear");
        }
        else{//相手のターンだった場合
            if(sum > COMPUTER_GET){
                input = 1;
            }
        }
        
        //手札を引かない判断がされたらtake_handをFALSEにする
        if(input == 1){
            take_hand = FALSE;
        }
    }
    
    printf("%sが引いた手札：", name[whichturn]);
    for(i = 1; i <= count; i++){//今まで引いた手札を表示
        printf("%d ", taked_hand[i]);
    }
    printf("\n");

    return sum;
}