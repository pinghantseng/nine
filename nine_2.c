#include <stdio.h>

int main()
{
    int i, j;
    for (int j = 1; j <= 9; j++){
        for (int i = 1; i <= 9; i++){
            if(i % 3 == 1)
                if(i * j / 10 == 0)
                    printf("%d x %d =  %d   ",i ,j ,i * j);
                else
                    printf("%d x %d = %d   ",i ,j ,i * j);
            if(i == 7)
                printf("\n");
        }
    }

    printf("\n\n");

    for (int j = 1; j <= 9; j++){
        for (int i = 1; i <= 9; i++){
            if(i % 3 == 2)
                if(i * j / 10 == 0)
                    printf("%d x %d =  %d   ",i ,j ,i * j);
                else
                    printf("%d x %d = %d   ",i ,j ,i * j);
            if(i == 8)
                printf("\n");
        }
    }

    printf("\n\n");

    for (int j = 1; j <= 9; j++){
        for (int i = 1; i <= 9; i++){
            if(i % 3 == 0)
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