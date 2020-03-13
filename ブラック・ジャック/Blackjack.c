#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Blackjack.h"

int main(void){
    int playerhand_sum;   //自分の手札の合計値
    int computerhand_sum; //相手の手札の合計値

    srand((unsigned int)time(NULL));
    
    system("clear");
    
    //プレイヤー・コンピュータの手札を引く処理
    //引数：どちらのターンか（int型）
    //戻り値：手札の合計値（int型）
    playerhand_sum = Takehand(TURN_PLAYER);
    computerhand_sum = Takehand(TURN_COMPUTER);
    
    printf("\n");
    printf("自分の手札:%d\n", playerhand_sum);
    printf("相手の手札:%d\n", computerhand_sum);
    printf("\n");

    //勝ちか負けかを判定
    //引数：プレイヤーの合計値（int型）、コンピュータの合計値（int型）
    //戻り値：勝敗の文字列（char型）
    printf("%s\n", Judge(playerhand_sum, computerhand_sum));

    return 0;
}