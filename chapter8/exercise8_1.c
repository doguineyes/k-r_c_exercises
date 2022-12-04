/*
  Exercise 8-1 Rewrite the program cat from Chapter7 using read, write, open, and close 
  instead of their standard library equivalents.
*/
#include <stdio.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>

int cat_low(int argc, char* argv[]) {
  if (argc == 1) {
    printf("Usage: cat file...\n");
    return -1;
  }

  char* filename;
  int fd;
  int i;
  char buff[BUFSIZ];
  int n = 0;

  for(i = 1; i < argc; i++) {
    filename = argv[i];
    if ((fd = open(filename, O_RDONLY, 0)) == -1) {
      printf("can not open file %s\n", filename);
      return -2;
    }
    while((n = read(fd, buff, BUFSIZ)) > 0) {
      if (write(1, buff, n) != n) {
        printf("write error on file %s\n", filename);
        return -3;
      }
    }
    close(fd);
  }

  return 0;
}

int main(int argc, char* argv[]) {
  cat_low(argc, argv);
}