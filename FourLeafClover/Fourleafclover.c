#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Fourleafclover.h"
#include "../trump.h"
#include "../truth.h"
#include "../ECS.h"

//プロトタイプ宣言
void Display(void);               //画面にカードを表示
void Clear_screen(void);      //画面を一度クリアする
void Playgame(void);              //ゲームのプレイ部分

char suank[TRUMPCARD];        //トランプの柄
int trump[CARD_X][CARD_Y];    //トランプの値
int choose_card[15] = {};     //選んだカード
int x[15] = {};               //選んだカードのx座標
int y[15] = {};               //選んだカードのy座標

int Fourleafclovermain(void){
    int card[TRUMPCARD];        //トランプ作成用
    int num = 0;                //配列の番号
    int i, j;                   //ループ文用
    int change1, change2, temp; //シャッフル用

    
    //初期化
    for(i = 1; i < TRUMPCARD + 1; i++){
        card[i - 1] = i;
    }

    // カードをシャッフル
    srand((unsigned int)time(NULL));
    for (i = 1;i <= SHUFFLE;i++) {
        change1 = rand() % TRUMPCARD;
        change2 = rand() % TRUMPCARD;

        temp = card[change1];
        card[change1] = card[change2];
        card[change2] = temp;
    }

    //シャッフルされた値をそれぞれトランプの柄と数字に変換
    for(i = 0; i < CARD_X; i++){
        for(j = 0; j < CARD_Y; j++){
            trump[i][j] = card[num];
            suank[num] = *Make_trump(&trump[i][j], trump[i][j]);
            num++;
        }
    }
    
    //ゲーム開始
    Playgame();

    return 0;
}

//画面にカードを表示
void Display(void){
    int i,j;         //ループ文用
    int suank_num = 0; //配列の番号
    
    Clear_screen();  //画面を一度クリア

    printf("  Y  0    1    2    3    4    5    6    7    8    9    10   11   12\n");
    printf("X   ----------------------------------------------------------------\n");
    //カードを表示
    for(i = 0; i < CARD_X; i++){
        printf("%d |", i);
        for(j = 0; j < CARD_Y; j++){
            if(trump[i][j] == NONUMBER){ //当たったカードは手前に＊をつける
                printf("*");
            }
            else{                        //それ以外は空白を入れる
                printf(" ");
            }
            printf("%c%2d ",suank[suank_num], trump[i][j]);
            suank_num++;
        }
        printf(" |\n");
    }
    printf("   -----------------------------------------------------------------\n");
}

//画面を一度クリアする
void Clear_screen(void){
    CLR;                        //画面をクリア
    LOCATION(0, 0);             //表示位置を一番上に
}

//ゲームのプレイ部分
void Playgame(void){
    int count = 0;              //カードを選んだ回数
    int arr_num = 0;;           //配列の番号
    int second = 2;             //停止させる秒数
    int sum = 0;                //選んだカードの合計値
    int max_card = TRUMPCARD;   //残り枚数
    int i, j;                   //ループ文用

    while(TRUE){
        //GIVEUP値が入力されたら処理を抜け、ゲーム終了
        if(x[arr_num] == GIVEUP || y[arr_num] == GIVEUP){
            printf("|* ギブアップしました *|\n");
            break;
        }

        arr_num = 0;
        Display();
        
        //全て当てたらゲーム終了
        if(max_card == 0){
            printf("|* ゲームクリア *|\n");
            break;
        }
        
        //プレイヤーが入力し、結果を表示
        while(TRUE){
            count++;                          
            printf("残り枚数： %d\n",max_card);
            printf("合計値： %d\n", sum);       

            printf("%d枚目のカードを選んでください↓\n", count);
            //プレイヤーが入力をする
            printf("X -> ");
            scanf("%d", &x[arr_num]);
            if(x[arr_num] == -1) break;
            printf("Y -> ");
            scanf("%d", &y[arr_num]);
            if(y[arr_num] == -1) break;
            
            //選んだカードを配列に入れ、合計値に追加
            choose_card[arr_num] = trump[x[arr_num]][y[arr_num]];
            trump[x[arr_num]][y[arr_num]] = NONUMBER;
            sum += choose_card[arr_num];
            
            //合計値が15以上になったら判定開始
            if(sum >= 15){
                if(sum == 15){
                    printf("あたり！！\n");
                    max_card -= count;             //残り枚数を減らす
                }
                else{
                    printf("ハズレ...\n");
                    for(i = 0; i <= arr_num; i++){ //選んだカードを元に戻す
                        trump[x[i]][y[i]] = choose_card[i];
                    }
                }
                sleep(second);                     //数秒間停止
                sum = 0;
                count = 0;
                break;
            }
            Display();
            arr_num++;
        }
    }
}