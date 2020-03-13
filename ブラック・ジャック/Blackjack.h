#ifndef BLACKJACK_H
#define BLACKJACK_H

//ゲーム進行に関するもの
#define TRUE 0
#define FALSE 1
#define TURN_PLAYER 0   //自分のターン
#define TURN_COMPUTER 1 //相手のターン

//手札についてのもの
#define MAXVALUE 13     //手札として引いた値の最大値
#define LIMIT 10        //計算する上での上限値
#define BURST 21        //バースト値
#define COMPUTER_GET 17 //コンピュータのドロー判断基準
#define MAXHAND 22      //手札の最大数
#define MAXCARD 52      //トランプのカード
#define SPADE 0         //スペード
#define DIAMOND 1       //ダイヤ
#define HEART 2         //ハート
#define CLOVER 3        //クローバー

#endif