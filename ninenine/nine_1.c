#include <stdio.h>

int main()
{
    for (int j = 1; j <= 9; j++){
        for (int i = 1; i <= 9; i++)
            printf("%d x %d = %2d   ",i ,j ,i * j );
        printf("\n");
    }

  return 0;
}