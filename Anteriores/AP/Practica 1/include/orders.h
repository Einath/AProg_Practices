#include <stdio.h>

#define LVECT 10000

void printvec(int v[LVECT]){
  int i; 
  for (i=0; i<LVECT; i++)
    printf("%d\t", v[i]); 
}
