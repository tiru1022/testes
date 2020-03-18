#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Blackjack.h"
#include "../truth.h"
#include "../trump.h"

//プロトタイプ宣言
char* Make_trump(int*, int);       //送られてきた乱数をトランプに変換
int Takehand(int);                 //手札を引く処理
char* Judge(int, int, const int);  //勝敗を判定して文字列を返す

typedef enum tag_turn{
    PLAYER,   //自分の番
    COMPUTER, //相手の番
    MAX      //参加者の数
}TURN;

int Blackjackmain(void){
    int playerhand_sum;   //自分の手札の合計値
    int computerhand_sum; //相手の手札の合計値
    TURN p1,p2;           //参加者

    p1 = PLAYER;
    p2 = COMPUTER;

    srand((unsigned int)time(NULL));
    
    system("clear");
    
    //プレイヤー・コンピュータの手札を引く処理
    //引数：どちらのターンか（int型）
    //戻り値：手札の合計値（int型）
    playerhand_sum = Takehand(p1);
    computerhand_sum = Takehand(p2);
    
    printf("\n");
    printf("自分の手札:%d\n", playerhand_sum);
    printf("相手の手札:%d\n", computerhand_sum);
    printf("\n");

    //勝ちか負けかを判定
    //引数：プレイヤーの合計値（int型）、コンピュータの合計値（int型）、バースト値（const int型）
    //戻り値：勝敗の文字列（char型）
    printf("%s\n", Judge(playerhand_sum, computerhand_sum, BURST));

    return 0;
}

//手札を引く処理
int Takehand(int whichturn){
    char name[MAX][100] = {"あなた","あいて"};    //誰の手札か判別
    char hand_suank[MAXHAND];                   //引いた手札の柄を保存する
    int hand_value[MAXHAND];                    //引いた手札の値を保存する
    int count = 0;                              //引いた手札の回数
    int number = 0;                             //トランプに変換するための乱数
    int card_value = 0;                         //手札の値
    int sum = 0;                                //手札の合計値
    int take_hand = TRUE;                       //もう一度手札を引くかどうかの判断
    int input = 0;
    int i;
    
    //初期化
    for(i = 0; i < MAXHAND; i++){
        hand_value[i] = 0;
    }
    
    //take_handにFALSEが入るまで繰り返す
    while(take_hand == TRUE){
        count++; //引いた回数追加

        //手札を引いて、それを手札用配列に格納
        number = rand() % TRUMPCARD;                            //トランプ変換用の乱数生成
        hand_suank[count] = *Make_trump(&card_value, number); //トランプの柄を配列に入れる
        hand_value[count] = card_value;                       //トランプの値を配列に入れる

        //引いた手札が10を超えていた場合、10として計算
        if(card_value > LIMIT){
            card_value = LIMIT;
        }

        sum += card_value; //合計値の計算
        //合計値がバースト値を超えた場合、ループを抜ける
        if(sum > BURST){
            break;
        }
        
        //もう一度引くか引かないか
        if(whichturn == 0){//自分のターンだった場合
            printf("||あなたのターンです||\n");
            printf("引いた手札：");
            //手札を表示
            for(i = 1; i <= count; i++){
                printf("%c%d ", hand_suank[i], hand_value[i]);
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
    //手札を表示
    for(i = 1; i <= count; i++){
        printf("%c%d ", hand_suank[i], hand_value[i]);
    }
    printf("\n");

    return sum;
}

//勝敗を判定して文字列を返す
char* Judge(int player, int computer, const int burst){
    char *result;                                          //戻り値用変数
    int burst_computer = (computer > burst);               //相手がバースト
    int burst_player = (player > burst);                   //自分がバースト
    int draw = (computer == player);                       //お互いが同じ数
    int draw_burst = (player > burst && computer > burst); //お互いがバースト
    int win_player = (player > computer);                  //自分の数が相手よりも大きい
    int win_computer = (player < computer);                //自分の数が相手よりの小さい

    if(draw || draw_burst){
        result = "引き分けです。";
    }
    else if(burst_player){
        result = "あなたの負けです...";
    }
    else if(burst_computer){
        result = "あなたの勝ちです！！";
    }
    else{
        if(win_player){
            result = "あなたの勝ちです！！";
        }
        else if(win_computer){
            result = "あなたの負けです...";
        }
    }
    return result;
}