#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 0
#define FALSE 1
#define TURN_PLAYER 0   //自分のターン
#define TURN_COMPUTER 1 //相手のターン

#define MAXVALUE 13     //手札として引いた値の最大値
#define LIMIT 10        //計算する上での上限値
#define BURST 21        //バースト値
#define COMPUTER_GET 17 //コンピュータのドロー判断基準
#define MAXHAND 22      //手札の最大数

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