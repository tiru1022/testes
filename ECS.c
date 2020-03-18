#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "truth.h"
#include "ECS.h"

//キーイベントの取得
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


int Cursor_move(void){
    char input;
	int loop = TRUE;
    int cursor_x, cursor_y;

    CLR;           //画面クリア
    LOCATION(0,0); //カーソルの初期位置指定
    while(loop){
        scanf("%c",&input);
	    //if(kbhit()){
            CLR;              //画面クリア
            switch (input){
            case 'd':
                RIGHT(2);     //右へ移動
                continue;
            case 'a':
                LEFT(2);      //左へ移動
                continue;
            case 'w':
                UP(2);        //上へ移動
                continue; 
            case 's':
                DOWN(2);      //下へ移動
                continue;
            case 'l':
                loop = FALSE; //処理を抜ける
                POSITION;     //カーソルの位置を取得
                LOCATION(0,0);
                break;
            default:
                continue;
            }
    	//}
    }
    scanf("\x1B[%d;%dR", &cursor_y, &cursor_x);
    printf("x = %d, y = %d\n", cursor_x, cursor_y); //カーソルの位置を表示
    return 0;
}