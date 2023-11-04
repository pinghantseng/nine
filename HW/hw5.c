#include <stdio.h>
#define SIZE 8
#define BLANK 0
#define BLACK 1
#define WHITE 2
#define BOUND (x+((a+1) * dx) > -1) && (x+((a+1) * dx) < 8) && (y+((a+1) * dy) > -1) && (y+((a+1) * dy) < 8)

// 橫軸是 y
// 縱軸是 x

//電腦 白棋
//人類 黑棋

int chess[SIZE][SIZE] = {0};
int next[2][SIZE][SIZE] = {0};

void inputArray(void){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            scanf("%1d", &(chess[i][j]));
    }
    return;
}

void find(void){
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

void checkNewStepByColor(int color){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            if(next[color][i][j] > 0)
                printf("(%d, %d) 可翻轉 %d 子\n", i, j, next[color][i][j]);
    }
    return;
}

void outputArray(void){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            printf("%d ", chess[i][j]);
        printf("\n");
    }
    return;
}

void flipChess(int x, int y){
    int flipCheck = next[BLACK][x][y];
    int flip;
    chess[x][y] = BLACK;
    for(int dy = -1; dy < 2; dy++){
        for(int dx = -1; dx < 2; dx++){
            if(dx != 0 || dy != 0){
                flip = 0;
                for(int a = 1; a < (SIZE-1); a++){
                    if(BOUND){
                        if(chess[x+(a * dx)][y+(a * dy)] == WHITE){
                            flip++;
                            if(chess[x+((a+1) * dx)][y+((a+1) * dy)] == BLACK){
                                flipCheck -= flip;
                                int b = a;
                                for(b; b > 0; b--){
                                    chess[x+(b * dx)][y+(b * dy)] = BLACK;
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
    if(flipCheck == 0){
        printf("OK");
    }
    return;
}

int main(){
    int x, y;
    inputArray();
    find();
    outputArray();
    printf("黑子可下的位置：\n");
    checkNewStepByColor(BLACK);
    printf("白子可下的位置：\n");
    checkNewStepByColor(WHITE);
    printf("輸入要下的位置");   //黑棋
    scanf("%d %d", &x, &y);

    flipChess(x, y);
    outputArray();
    printf("黑子可下的位置：\n");
    checkNewStepByColor(BLACK);
    printf("白子可下的位置：\n");
    checkNewStepByColor(WHITE);
    return 0;
}
