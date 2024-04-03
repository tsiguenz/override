#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av) { // rbp-0x94 and rbp-0xa0
  if (ac != 2) {
     printf("Usage: %s filename\n", av[0]);
  }
  FILE* file; // rbp-0x80
  FILE* backup; // rbp-0x88
  int i;

  backup = fopen("./backups/.log", "r");
  if (backup == NULL) {
    printf("ERROR: Failed to open %s\n", "./backukps/.log");
    exit(1);
  }
  log_wrapper(backup, "Starting back up: ", av[1]);
  file = fopen(av[1], "r");
  if (file == NULL) {
    printf("ERROR: Failed to open %s\n", av[1]);
    exit(1);
  }
  
}
