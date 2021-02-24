#include<stdio.h>
#include<stdlib.h>

int main(int argc, const char *argv[]) {

  for (int i=0; i < argc; i++) {
    system(argv[i]);
  }

  return 0;
}