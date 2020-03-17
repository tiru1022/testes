#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define TRUE 1;
#define FALSE 0;

/* エスケープシーケンス */
#define clr		    printf("\033[2J") //画面クリア
// #define clr_right	printf("\033[0K") //カーソル位置からその行の右端までをクリア
// #define clr_left	printf("\033[1K") //カーソル位置からその行の左端までをクリア
// #define clr_line	printf("\033[2K") //カーソル位置の行をクリア
#define location(x,y)	printf("\033[%d;%dH" ,x,y) //カーソル位置を移動
#define right(x)	printf("\033[%dC" ,x) //カーソルを指定数だけ右に移動
#define left(x)		printf("\033[%dD" ,x) //カーソルを指定数だけ左に移動
#define down(x)		printf("\033[%dB" ,x) //カーソルを指定数だけ下に移動
#define up(x)		printf("\033[%dA" ,x) //カーソルを指定数だけ上に移動
#define position    printf("\x1B[6n") //カーソルの位置を取得

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


int main(void){
	int loop = TRUE;
    int cursor_x, cursor_y;

    clr;           //画面クリア
    location(0,0); //カーソルの初期位置指定
    while(loop){
	    if(kbhit()){
            clr;              //画面クリア
            switch (getchar()){
            case 'd':
                right(2);     //右へ移動
                continue;
            case 'a':
                left(2);      //左へ移動
                continue;
            case 'w':
                up(2);        //上へ移動
                continue; 
            case 's':
                down(2);      //下へ移動
                continue;
            case 'l':
                loop = FALSE; //処理を抜ける
                position;     //カーソルの位置を取得
                location(0,0);
                break;
            default:
                continue;
            }
    	}
    }
    scanf("\x1B[%d;%dR", &cursor_y, &cursor_x);
    printf("x = %d, y = %d\n", cursor_x, cursor_y); //カーソルの位置を表示
    return 0;
}