#include <stdio.h>
#include <string.h>

int hasDup(char *str);
int main(int argc,char **argv) {
int i;  for (i=1; i<argc; i++) {   printf("Arg %d: %s has %s duplicates\n",i,argv[i],    hasDup(argv[i])?"":"no");  }  return 0; }

int hasDup(char *str) {
  int i; int j;
for (i=0;i<strlen(str);i++) {
for(j=i+1;j<strlen(str);j++) {
if (str[i]==str[j]) return 1;
}  }  return 0; }