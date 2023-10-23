#include <stdio.h>
#define SIZE 8

int chess[SIZE][SIZE];

void inputArray(void) {
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++)
            scanf("%1d", &(chess[i][j]));
    }
    return;
}

void color(int x, int  y){
    if(chess[x][y] == 0)
        printf("空白\n");
    else if(chess[x][y] == 1)
        printf("黑棋\n");
    else if(chess[x][y] == 2)
        printf("白棋\n");
    return;
}

void find(int x, int  y){
    if(chess[x][y] == 0)
        printf("因為空白，所以周圍不能下\n");
    int color = chess[x][y];
    int antiColor;
    if(color == 1) antiColor = 2;
    if(color == 2) antiColor = 1;
    if(chess[x][y] != 0){
        for(int dy = -1; dy < 2; dy++){
            for(int dx = -1; dx < 2; dx++){
                if(dx != 0 || dy != 0){
                    for(int a = 1; a < 7; a++){
                        if((x+(a * dx) != -1)||(x+(a * dx) != 8)||(y+(a * dy) != -1)||(y+(a * dy) != 8)){
                            if(chess[x+(a * dx)][y+(a * dy)] == antiColor)
                                if(chess[x+((a+1) * dx)][y+((a+1) * dy)] == 0){
                                    printf("(%d, %d)", x+((a+1) * dx), y+((a+1) * dy));
                                    break;
                                }
                        }
                        break;
                    }
                }
            }
        }
    }
    return;
}

int main()
{
    int x, y;
    inputArray();
    scanf("%d %d", &x, &y);
    color(x, y);
    find(x, y);

    return 0;
}
