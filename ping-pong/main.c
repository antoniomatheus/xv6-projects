#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  char buffer[10];
  int count;

  int p1[2];
  int p2[2];
  pipe(p1);
  pipe(p2);

  if (fork() == 0) {
    count = 0;
    while (1) {
      write(p1[1], "Hello", 5);
      sleep(0);
      read(p2[0], &buffer, 10);
      printf("[%d] Child process received: %s\n", count, buffer);
      count++;
    }
  } else {
    count = 0;
    while (1) {
      read(p1[0], &buffer, 10); 
      printf("[%d] Parent process received: %s\n",count , buffer);
      count++;
      write(p2[1], "Hello", 5);
      sleep(0);
    }
  }
}
