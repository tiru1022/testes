#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Nervousbreakdown.h"
#include "../truth.h"
#include "../trump.h"
#include "../ECS.h"

//プロトタイプ宣言
void Display(int,int,int,int); //カードを画面に表示させる
void Playgame();               //ゲームのプレイ部分
void Clear_screen();           //画面を一度クリアする
void Get_location(int*, int*);

char suank[TRUMPCARD];
int trump[CARD_X][CARD_Y];
int no1_card;
int no2_card;

int Nervousbreakdownmain(void){
    int card[TRUMPCARD];        //トランプ作成用
    int num;                    //配列の番号
    int i, j;                   //ループ文用
    int change1, change2, temp; //シャッフル用
    
    //初期化
    num = 0;
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

    printf("ゲームクリア！！\n");

    return 0;
}

//選んだカードを表示
void Display(int x1, int y1, int x2, int y2){
    int x,y;
    int suank_num = 0;
    
    Clear_screen();  //画面を一度クリア

    printf("  Y  0    1    2    3    4    5    6    7    8    9    10   11   12\n");
    printf("X   ----------------------------------------------------------------\n");

    for(x = 0; x < CARD_X; x++){
        printf("%d |", x);
        for(y = 0; y < CARD_Y; y++){
            if(x == x1 && y == y1){
                printf(" %2c%2d",suank[suank_num], trump[x][y]);
                no1_card = trump[x][y];
            }
            else if(x == x2 && y == y2){
                printf(" %2c%2d",suank[suank_num], trump[x][y]);
                no2_card = trump[x][y];
            }
            else if(trump[x][y] > 0){
                printf("  *  ");
            }
            else{
                printf("     ");
            }

            suank_num++;
        }
        printf(" |\n");
    }
    printf("   -----------------------------------------------------------------\n");
}

//ゲームのプレイ部分
void Playgame(){
    int x1,x2,y1,y2; //選んだカードの座標
    int pair = 0;    //当たったペアの数
    int second = 2;  //停止時間

    while(TRUE){
        //全て当てたら処理を抜ける
        if(pair == TRUMPCARD / 2){
            break;
        }

        //カードを並べて表示
        Display(NONUMBER,NONUMBER,NONUMBER,NONUMBER);
        
        //1枚目のカードを選んで表示
        printf("1枚目のカードを選んでください\n");
        Get_location(&x1,&y1);
        Display(x1,y1,NONUMBER,NONUMBER);

        
        //2枚目のカードを選んで表示
        printf("2枚目のカードを選んでください\n");
        Get_location(&x2,&y2);
        Display(x1,y1,x2,y2);
        
        if(no1_card == no2_card){//当たったらそのカードは表示させないようにする
            printf("あたり！！\n");
            pair++;
            trump[x1][y1] = NONUMBER;
            trump[x2][y2] = NONUMBER;
        }
        else{
            printf("ハズレ...\n");
        }
        sleep(second); //数秒間待つ
    }
}

//画面を一度クリアする
void Clear_screen(){
    CLR;            //画面をクリア
    LOCATION(0, 0); //表示位置を一番上に
}

void Get_location(int* x, int* y){
    printf("X -> ");
    scanf("%d", x);
    printf("Y -> ");
    scanf("%d", y);
}