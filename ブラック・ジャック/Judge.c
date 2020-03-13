#include <stdio.h>
#include "Blackjack.h"

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