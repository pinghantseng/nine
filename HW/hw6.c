#include <stdio.h>
#define SIZE 8
#define BLANK 0
#define BLACK 1
#define WHITE 2
#define BOUND (x+((a+1) * dx) > -1) && (x+((a+1) * dx) < SIZE) && (y+((a+1) * dy) > -1) && (y+((a+1) * dy) < SIZE)

// 橫軸是 y
// 縱軸是 x

// 橫軸 a b c d e f g h 
// 縱軸 1 2 3 4 5 6 7 8

// 電腦 白棋
// 人類 黑棋

// 當一方無處可下時，輪另一方下
// 當二方都無處可下時，棋局就結束
// 子多的那方獲勝。

int chess[SIZE][SIZE] ={{0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,1,2,0,0,0},
                        {0,0,0,2,1,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}};

int next[2][SIZE][SIZE] = {0};
int position[2] = {0};     // 函數回傳值

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

void checkNewStep(int color){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            if(next[color][i][j] > 0)
                printf("(%c, %d) 可翻轉 %d 子\n", i+'a', j+1, next[color][i][j]);
    }
    return;
}

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
    return;
}

int noChessToFlip(int color){
    int u = 0;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if(next[color][i][j] > 0){
                u++;
            }
        }
    }
    if(u == 0) return 1;
    if(u > 0) return 2;
}

void flipChess(int x, int y, int color){
    int flipCheck = next[BLACK][x][y];
    int flip, antiColor;
    if(color == BLACK) antiColor = WHITE;
    if(color == WHITE) antiColor = BLACK;

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
                                chess[x][y] = color;
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

int main(){
    char a;
    int b, x, y, time=0;
    int numOfWhite, numOfBlack;

    printf("玩家黑子 黑子先下\n");
      
    while(time == 0 || noChessToFlip(BLACK) * noChessToFlip(WHITE) > 1){
        outputArray();
        if(noChessToFlip(BLACK) > 1 || time == 0){
            findChessToFlip();
            printf("黑子可下的位置：\n");
            checkNewStep(BLACK);

            printf("輸入您要下的位置");
            scanf("%c %d", &a, &b);
            x = a - 'a';
            y = b - 1;
            flipChess(x, y, BLACK);
        }
        if(noChessToFlip(WHITE) > 1 || time == 0){
            findChessToFlip();
            findMostValueChess(WHITE);
            flipChess(position[1], position[2], WHITE);
        }
        time++;
    }

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            if(chess[x][y] == BLACK)
                numOfBlack++;
            else if(chess[x][y] == WHITE)
                numOfWhite++;
    }

    printf("棋局結束\n");
    if(numOfBlack > numOfWhite)
        printf("黑方勝 %d:%d", numOfBlack, numOfWhite);
    else if(numOfBlack < numOfWhite)
        printf("白方勝 %d:%d", numOfWhite, numOfBlack);
    else if(numOfBlack = numOfWhite)
        printf("和局 %d:%d", numOfBlack, numOfWhite);
    
    return 0;
}
