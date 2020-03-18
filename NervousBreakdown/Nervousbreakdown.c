#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Nervousbreakdown.h"
#include "../truth.h"
#include "../trump.h"

int Nervousbreakdownmain(void){
    char suank[TRUMPCARD];
    int card[TRUMPCARD];
    int trump[CARD_X][CARD_Y];
    int i, j, k;
    int x1,x2,y1,y2,buffer;
    
    //初期化
    for(i = 1; i < TRUMPCARD + 1; i++){
        card[i - 1] = i;
    }
    k = 0;

    /* カードをシャッフル */
    srand((unsigned int)time(NULL));
    //srand( time(0) );
    
    for(i = 0; i < CARD_X; i++){
        for(j = 0; j < CARD_Y; j++){
            trump[i][j] = card[k];
            k++;
        }
    }

    for (i = 1;i <= 100;i++) {
        x1 = rand() % CARD_X;                     /* rand() は乱数 */
        y1 = rand() % CARD_Y;
        x2 = rand() % CARD_X;
        y2 = rand() % CARD_Y;

        buffer      = trump[x1][y1] ;
        trump[x1][y1] = trump[x2][y2] ;
        trump[x2][y2] = buffer ;
    }
    
    k = 0;
    for(i = 0; i < CARD_X; i++){
        for(j = 0; j < CARD_Y; j++){
            suank[k] = *Make_trump(&trump[i][j], trump[i][j]);

            if(j < CARD_Y - 1){
                printf(" %2c%2d",suank[k], trump[i][j]);
            }
            else{
                printf(" %2c%2d\n",suank[k], trump[i][j]);
            }
            k++;
        }
    }

    return 0;
}