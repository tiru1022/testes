#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Blackjack.h"

//プロトタイプ宣言
char* Make_trump(int*, int);       //トランプの設定
int Takehand(int);      //手札を引く処理
char* Judge(int, int);  //勝敗を判定して文字列を返す

int main(void){
    int playerhand_sum;   //自分の手札の合計値
    int computerhand_sum; //相手の手札の合計値

    srand((unsigned int)time(NULL));
    
    //system("clear");
    
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

char* Make_trump(int* value, int hand){
    int card[MAXCARD];
    int kind = 0;
    char suank[][10] = {"S", "D", "H", "C"};


        if(hand >= 1 && hand <= 13){
            kind = SPADE;
            *value = hand;
        }
        else if(hand >= 14 && hand <= 26){
            kind = DIAMOND;
            *value = hand - MAXVALUE;
        }
        else if(hand >= 27 && hand <= 39){
            kind = HEART;
            *value = hand - MAXVALUE * 2;
        }
        else if(hand >= 40 && hand <= 52){
            kind = CLOVER;
            *value = hand - MAXVALUE * 3;
        }
        return suank[kind];
}

//手札を引く処理
int Takehand(int whichturn){
    char name[2][100] = {"あなた","あいて"}; //誰の手札か判別
    int hand_value[MAXHAND];               //引いた手札の値を保存する
    char hand_suank[MAXHAND][10] = {};               //引いた手札の柄を保存する
    int count = 0;                             //引いた手札の数
    int hand = 0;                          //トランプに変換する値
    int card_value = 0;                    //手札の値
    char card_suank[10] = {};                    //手札の柄
    int sum = 0;                               //手札の合計値
    int take_hand = TRUE;                         //もう一度手札を引くかどうかの判断
    int input = 0;
    int i;
    
    //初期化
    for(i = 0; i < MAXHAND; i++){
        hand_suank[i] = "a";
        hand_value[i] = 0;
    }
    
    //take_handにFALSEが入るまで繰り返す
    while(take_hand == TRUE){
        count++;

        //手札を引いて、それを手札用配列に格納
        hand = rand() % MAXCARD;
        hand_suank[count] = Make_trump(&card_value, hand);

        printf("%s", card_suank);

        hand_value[count] = card_value;
        
        if(card_value > LIMIT){//引いた手札が10を超えていた場合、10として計算
            card_value = LIMIT;
        }
        sum += card_value;     //合計値の計算

        if(sum > BURST){//合計値がバースト値を超えた場合、ループを抜ける
            break;
        }
        
        //もう一度引くか引かないか
        if(whichturn == 0){//自分のターンだった場合
            printf("||あなたのターンです||\n");
            printf("引いた手札：");
            for(i = 1; i <= count; i++){
                printf("%s%d ", hand_suank[i], hand_value[i]);
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
        printf("%s%d ", hand_suank[i], hand_value[i]);
    }
    printf("\n");

    return sum;
}

//勝敗を判定して文字列を返す
char* Judge(int player, int computer){
    if(player > BURST){//自分がバーストした時
        if(computer > BURST){
            return "引き分けです。";
        }
        else{
            return "あなたの負けです...";
        }
    }
    else if(player <= BURST){//自分がバーストしていない時
        if(computer > BURST || player > computer){
            return "あなたの勝ちです！！";
        }
        else if(player < computer){
            return "あなたの負けです...";
        }
        else{
            return "引き分けです。";
        }
    }
    return 0;
}