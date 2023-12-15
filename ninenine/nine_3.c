#include <stdio.h>

int main()
{
    for (int k = 0; k <= 6; k += 3){
        for (int j = 1; j <= 9; j++){
            for (int i = 1 + k; i <= 3 + k; i++)
                printf("%d x %d = %2d   ",i ,j ,i * j);
            printf("\n");
        }
    printf("\n\n");
    }

  return 0;
}