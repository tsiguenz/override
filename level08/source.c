#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void log_wrapper(FILE *backup, char *str, char *input) {
  char dest[264];
  strcpy(dest, str);
  snprintf(&dest[strlen(dest)], strlen(input), input);
  dest[strcspn(dest, "\n")] = '\0';
  fprintf(backup, "LOG: %s\n", dest);
}

int main(int ac, char **av) { // rbp-0x94 and rbp-0xa0
  if (ac != 2) {
    printf("Usage: %s filename\n", av[0]);
  }
  int fd;
  char dest[104];
  char ret;
  FILE *file;   // rbp-0x80
  FILE *backup; // rbp-0x88
  int i;

  backup = fopen("./backups/.log", "r");
  if (backup == NULL) {
    printf("ERROR: Failed to open %s\n", "./backups/.log");
    exit(1);
  }
  log_wrapper(backup, "Starting back up: ", av[1]);
  file = fopen(av[1], "r");
  if (file == NULL) {
    printf("ERROR: Failed to open %s\n", av[1]);
    exit(1);
  }
  strcpy(dest, "./backups/");
  strncat(dest + 10, av[1], strlen(av[1]));
  fd = open(dest, 193, 432);
  if (fd < 0) {
    printf("ERROR: Failed to open %s%s\n", "./backups/", av[1]);
    exit(1);
  }
  while (1) {
    ret = fgetc(file);
    if (ret == -1)
      break;
    write(fd, &ret, 1);
  }
  log_wrapper(backup, "Finished back up ", av[1]);
  fclose(file);
  close(fd);
}
