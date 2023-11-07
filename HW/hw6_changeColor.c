#include <stdio.h>
#define SIZE 8
#define BLANK 0  //空白
#define BLACK 1
#define WHITE 2
#define BOUND (x+((a+1) * dx) > -1) && (x+((a+1) * dx) < SIZE) && (y+((a+1) * dy) > -1) && (y+((a+1) * dy) < SIZE)  //判斷是否超出邊界

// 橫軸是 y, 縱軸是 x
// 電腦白棋, 人類黑棋

int chess[SIZE][SIZE] ={{0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,1,2,0,0,0},
                        {0,0,0,2,1,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}};

int next[2][SIZE][SIZE] = {0};
int position[2] = {0};  //函數回傳值

//將next陣列裡的值設為0
void clear(void){
    for(int a = 1; a < 3; a++)
        for (int x = 0; x < SIZE; x++)
            for (int y = 0; y < SIZE; y++)
                next[a][x][y] = 0;
    return;
}

//尋找黑棋與白棋所有可以下的位置及可翻轉棋子的數目儲存在next陣列中
void findChessToFlip(void){
    for (int x = 0; x < SIZE; x++){
        for (int y = 0; y < SIZE; y++){

            int flip = 0;
            int antiColor = 0;
            int color = chess[x][y];
            if(color == BLACK) antiColor = WHITE;
            if(color == WHITE) antiColor = BLACK;

            if(chess[x][y] != BLANK){
                for(int dy = -1; dy < 2; dy++){
                    for(int dx = -1; dx < 2; dx++){
                        if(dx != 0 || dy != 0){
                            flip = 0;
                            for(int a = 1; a < (SIZE-1); a++){
                                if(BOUND){
                                    if(chess[x+(a * dx)][y+(a * dy)] == antiColor){
                                        flip++;
                                        if(chess[x+((a+1) * dx)][y+((a+1) * dy)] == 0){
                                            next[color][x+((a+1) * dx)][y+((a+1) * dy)] += flip;
                                            break;
                                        }
                                    }
                                    else break;
                                }
                                else break;
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}

//輸入顏色 輸出該顏色所有可以下的位置及可翻轉棋子的數目
void checkNewStep(int color){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            if(next[color][i][j] > 0)
                printf("(%c, %d) 可翻轉 %d 子\n", j+'a', i+1, next[color][i][j]);
    }
    return;
}

//輸出棋盤
void outputArray(void){
    printf("  a b c d e f g h\n");
    for (int i = 0; i < SIZE; i++){
        printf("%d ", (i+1));
        for (int j = 0; j < SIZE; j++)
            printf("%d ", chess[i][j]);
        printf("\n");
    }
    return;
}

//輸入顏色 找出該顏色可以翻最多棋子的位置 並輸出該位置
void findMostValueChess(int color){
    int value = 0;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if(next[color][i][j] > value){
                value = next[color][i][j];
                position[1] = i;
                position[2] = j;
            }
        }
    }
    if(color == 1)
        printf("黑棋下 (%c, %d)\n", position[2]+'a', position[1]+1);
    if(color == 2)
        printf("白棋下 (%c, %d)\n", position[2]+'a', position[1]+1);
    return;
}

//輸入顏色 判斷該顏色是否有棋子可下 有回傳1 無回傳0
int noChessToFlip(int color){
    int u = 0;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if(next[color][i][j] > 0){
                u++;
            }
        }
    }
    if(u == 0) return 0;
    if(u > 0) return 1;
}

//輸入下的棋子及顏色 翻棋子更改棋盤
void flipChess(int x, int y, int color){
    int flipCheck = next[BLACK][x][y];
    int flip, antiColor;
    if(color == BLACK) antiColor = WHITE;
    if(color == WHITE) antiColor = BLACK;
    chess[x][y] = color;
    for(int dy = -1; dy < 2; dy++){
        for(int dx = -1; dx < 2; dx++){
            if(dx != 0 || dy != 0){
                flip = 0;
                for(int a = 1; a < (SIZE-1); a++){
                    if(BOUND){
                        if(chess[x+(a * dx)][y+(a * dy)] == antiColor){
                            flip++;
                            if(chess[x+((a+1) * dx)][y+((a+1) * dy)] == color){
                                flipCheck -= flip;
                                int b = a;
                                for(b; b > 0; b--){
                                    chess[x+(b * dx)][y+(b * dy)] = color;
                                }
                                break;
                            }
                        }
                        else break;
                    }
                    else break;
                }
            }
        }
    }
    // if(flipCheck == 0){
    //     printf("OK");
    // }
    return;
}

//輸入顏色 輸入下棋的位置 無法下棋則重新輸入 並翻棋子
void input(int color){
    char a;
    int b, x, y;
    while(1){
        printf("輸入您要下的位置");
        scanf("%1c %1d", &a, &b);
        x = b - 1;
        y = a - 'a';
        if(next[color][x][y] > 0)
            break;
        else
            continue;
    }
    flipChess(x, y, color);
    return;
}

//統計終局棋盤各顏色棋子的數目 並輸出比賽結果
void resultOfTheGame(void){
    int numOfWhite=0, numOfBlack=0;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            if(chess[i][j] == BLACK)
                numOfBlack++;
            else if(chess[i][j] == WHITE)
                numOfWhite++;
    }

    if(numOfBlack > numOfWhite)
        printf("黑方勝 %d:%d", numOfBlack, numOfWhite);
    else if(numOfBlack < numOfWhite)
        printf("白方勝 %d:%d", numOfWhite, numOfBlack);
    else if(numOfBlack == numOfWhite)
        printf("和局 %d:%d", numOfBlack, numOfWhite);
    return;
}

int main(){
    char b, c;
    int a, x, y, time=0, num;
    int color, antiColor;
    
    printf("棋局開始\n黑棋先下白棋後下\n請選擇棋子顏色\n");
    while(1){
        printf("選擇黑棋請輸入B;選擇白棋請輸入W\n");
        scanf("%c", &c);
        if(c == 'B'){
            color = BLACK;
            break;
        }
        else if(c == 'W'){
            color = WHITE;
            break;
        }
        else
            continue;
    }

    if(color == BLACK){
        antiColor = WHITE;
        num = 0;
    }
    if(color == WHITE){
        antiColor = BLACK;
        num = 1;
    }

    findChessToFlip();
    for(int time = 0; noChessToFlip(BLACK) + noChessToFlip(WHITE) > 0; time++){
        if(time % 2 == num && noChessToFlip(color) > 0){
            outputArray();
            printf("玩家可下的位置：\n");
            checkNewStep(color);
            input(color);
            clear();
            findChessToFlip();
        }
        if(time % 2 == !num && noChessToFlip(antiColor) > 0){
            findMostValueChess(antiColor);
            flipChess(position[1], position[2], antiColor);
            clear();
            findChessToFlip();
        }

    }

    printf("棋局結束\n");
    resultOfTheGame();

    return 0;
}
