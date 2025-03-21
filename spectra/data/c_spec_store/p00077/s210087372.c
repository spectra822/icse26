#include <stdio.h>
#include <string.h>

#define MAX 100

int main(void) {
  char str[MAX];
  int i, j;
  int length;

  while(scanf("%s", str) != EOF) {
    length = strlen(str);
    for(i=0; i<length; ++i) {
      if(str[i] == '@') {
        for(++i, j=0; j<str[i]-'0'; ++j) {
          printf("%c", str[i+1]);
        }
        i += 1;
        continue;
      }
      else {
        printf("%c", str[i]);
      }
    }
    printf("\n");
  }

  return 0;
}

