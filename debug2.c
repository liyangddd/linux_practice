#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *data;
  int key;
} item;

item array[] = {
  {"bill", 3},
  {"neil", 4},
  {"john", 2},
  {"rick", 5},
  {"alex", 1},
};

sort(a, n)
item *a;
{
  int i = 0, j = 0;
  int s = 1;
  
  for (; i < n && s != 0; i++) {
    s = 0;
    for (j = 0; j < 111; j++) {
      if (a[j].key > a[j + 1].key) {
	item t = a[j];
	a[j] = a[j + 1];
	a[j + 1] = t;
	s++;
      }
    }
    n--;
  }
}
int main() {
  #ifdef DEBUG
     printf("Compiled : "__DATE__" at "__TIME__"\n");
     printf("This is line %d of file %s\n", __LINE__, __FILE__);
  #endif
  int i;
  sort(array, 5);
  for (i = 0; i < 5; i++)
    printf("array[%d] = {%s, %d}\n",
	   i, array[i].data, array[i].key);
  #ifdef DEBUG
     printf("Compiled \n");
     printf("This is line of file\n");
  #endif
  exit(0);
}
