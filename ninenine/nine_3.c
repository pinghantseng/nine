#include <stdio.h>

int main()
{
    int i, j;
    for (int j = 1; j <= 9; j++){
        for (int i = 1; i <= 3; i++){
            if(i * j / 10 == 0)
                printf("%d x %d =  %d   ",i ,j ,i * j);
            else
                printf("%d x %d = %d   ",i ,j ,i * j);
            if(i == 3)
                printf("\n");
        }
    }

    printf("\n\n");

    for (int j = 1; j <= 9; j++){
        for (int i = 4; i <= 6; i++){
            if(i * j / 10 == 0)
                printf("%d x %d =  %d   ",i ,j ,i * j);
            else
                printf("%d x %d = %d   ",i ,j ,i * j);
            if(i == 6)
                printf("\n");
        }
    }

    printf("\n\n");

    for (int j = 1; j <= 9; j++){
        for (int i = 7; i <= 9; i++){
            if(i * j / 10 == 0)
                printf("%d x %d =  %d   ",i ,j ,i * j);
            else
                printf("%d x %d = %d   ",i ,j ,i * j);
            if(i == 9)
                printf("\n");
        }
    }

  return 0;
}