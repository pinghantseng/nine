#include <stdio.h>

int main()
{
    int i, j;
    for (int j = 1; j <= 9; j++){
        for (int i = 1; i <= 9; i++){
            if(i * j / 10 == 0)
                printf("%dx%d= %d ",i ,j ,i * j);
            else
                printf("%dx%d=%d ",i ,j ,i * j);
            if(i == 9)
                printf("\n");
        }
    }
  return 0;
}