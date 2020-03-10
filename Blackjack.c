#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int true = 0;
const int false = 1;

int Takehand(int whichturn){
    const int maxhand = 22;
    char name[2][100] = {"あなた","あいて"};
    int taked_hand[maxhand];
    int count;
    int hand;
    int sum;
    int take_hand;
    int input;
    int i;

    count = 0;
    hand = 0;
    sum = 0;
    take_hand = true;
    input = 0;

    for(i = 0; i < maxhand; i++){
        taked_hand[i] = 0;
    }
    
    while(take_hand == true){

        hand = rand() % 13 + 1;
        count++;

        taked_hand[count] = hand;

        if(hand > 10){
            hand = 10;
        }

        sum += hand;

        if(sum > 21){
            break;
        }
            
        if(whichturn == 0){
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
        else{
            if(sum > 17){
                input = 1;
            }
        }

        if(input == 1){
            take_hand = false;
        }
    }

    printf("%sが引いた手札：", name[whichturn]);
    for(i = 1; i <= count; i++){
        printf("%d ", taked_hand[i]);
    }
    printf("\n");

    return sum;
}

void Judge(int player, int computer){
    const int burstline = 21;

    if(player == computer){
        printf("引き分けです。\n");
    }
    else if(player > burstline){
        printf("バーストしました。\n");

        if(computer > burstline){
            printf("相手もバーストしました。\n\n引き分けです。\n");
        }
        else{
            printf("\nあなたの負けです...\n");
        }
    }
    else{
        if(computer > burstline){
            printf("相手がバーストしました。\n\nあなたの勝ちです！！\n");
        }
        else{
            if(player > computer){
                printf("あなたの勝ちです！！\n");
            }
            else{
                printf("あなたの負けです...\n");
            }
        }
    }
}

int main(void){
    int computer_hand;
    int i;
    int playerhand_sum;
    int computerhand_sum;
    const int turn_player = 0;
    const int turn_conputer = 1;

    playerhand_sum = 0;
    computer_hand = 0;

    srand((unsigned int)time(NULL));
    
    system("clear");
    
    //プレイヤー・コンピュータの手札を引く処理
    //引数：どちらのターンか（int型）
    //戻り値：手札の合計値（int型）
    playerhand_sum = Takehand(turn_player);
    computerhand_sum = Takehand(turn_conputer);
    
    printf("\n");
    printf("自分の手札:%d\n", playerhand_sum);
    printf("相手の手札:%d\n", computerhand_sum);
    printf("\n");

    //勝ちか負けかを判定し、表示する
    //引数：プレイヤーの合計値（int型）、コンピュータの合計値（int型）
    //戻り値：無し（void型）
    Judge(playerhand_sum, computerhand_sum);

    return 0;
}