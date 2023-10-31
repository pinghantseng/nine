#include <stdio.h>
#define SIZE 8
#define BOUND (x+((a+1) * dx) != -1) && (x+((a+1) * dx) != 8) && (y+((a+1) * dy) != -1) && (y+((a+1) * dy) != 8)

int chess[SIZE][SIZE];
int next[2][SIZE][SIZE] = {0};

void inputArray(void) {
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++)
            scanf("%1d", &(chess[i][j]));
    }
    return;
}

void find(void){
    for (int x = 0; x < 8; x++){
        for (int y = 0; y < 8; y++){
            int color = chess[x][y];
            int antiColor = 0;
            if(color == 1) antiColor = 2;
            if(color == 2) antiColor = 1;
            if(chess[x][y] != 0){
                for(int dy = -1; dy < 2; dy++){
                    for(int dx = -1; dx < 2; dx++){
                        if(dx != 0 || dy != 0){
                            for(int a = 1; a < 7; a++){
                                if(BOUND){
                                    if(chess[x+(a * dx)][y+(a * dy)] == antiColor)
                                        if(chess[x+((a+1) * dx)][y+((a+1) * dy)] == 0){
                                            next[color][x+((a+1) * dx)][y+((a+1) * dy)] = 1;
                                            break;
                                        }
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

void checkNewStepByColor(int color) 
{
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++)
            if(next[color][i][j] == 1)
                printf("(%d, %d) ", i, j);
    }
    return;
}

int main()
{
    inputArray();
    find();
    printf("黑子可下的位置：");
    checkNewStepByColor(1);
    printf("\n");
    printf("白子可下的位置：");
    checkNewStepByColor(2);
    printf("\n");
    return 0;
}

// 橫軸是Y
// 縱軸是X
