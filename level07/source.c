#include <stdio.h>
#include <string.h>

void clear_stdin() {
  char c = 0;
  
  while (c != '\n')
    c = getchar();
}

unsigned int get_unum() {
  unsigned int num = 0;

  fflush(stdout);
  scanf("%u", &num);
  clear_stdin();
  return num;
}

int store_number(int **storage) {
  unsigned int index = 0; // -0xc
  unsigned int num = 0;   // -0x10

  printf(" Number: ");
  num = get_unum();
  printf(" Index: ");
  index = get_unum();
  if (index % 3 == 0 || (index >> 24) == 0xb7) {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    return 1;
  }
  (*storage)[index] = num;
  return 0;
}

int read_number(char *storage) {
  unsigned int index = 0;

  printf(" Index: ");
  index = get_unum();
  printf(" Number at data[%u] is %u\n", index, storage[index]);
  return 0;
}

int main(int ac, char **av, char **envp) {
  // int canary = *0x14; // 0x1cc
  char buff[20] = {0}; // 0x1b8
  int a = 0;           // 0x1b4
  int storage[100];    // 0x24
  char **args = av;    // 0x1c
  char **env = envp;   // 0x18
  int b = 0;           // 0x14

  while (*args != NULL) {
    memset(*args, 0, strlen(*args) - 1);
    args++;
  }
  while (*env != NULL) {
    memset(*env, 0, strlen(*env) - 1);
    env++;
  }
  puts("----------------------------------------------------");
  puts("  Welcome to wil's crappy number storage service!  ");
  puts("----------------------------------------------------");
  puts(" Commands:");
  puts("    store - store a number into the data storage");
  puts("    read  - read a number from the data storage");
  puts("    quit  - exit the program");
  puts("----------------------------------------------------");
  puts("   wil has reserved some storage :>");
  puts("----------------------------------------------------");
  while (1) {
    printf("Input command: ");
    fgets(buff, 20, stdin);
    buff[strlen(buff) - 1] = 0;
    if (strncmp("store", buff, 5) == 0)
      a = store_number(&storage);
    if (strncmp("read", buff, 4) == 0)
      a = read_number(&storage);
    if (strncmp("quit", buff, 4) == 0)
      break;
    if (a == 0)
      printf(" Completed %s command successfully\n", buff);
    else
      printf(" Failed to do %s command\n", buff);
    bzero(buff, 20);
  }
  //  if (canary != *0x14)
  //    __stack_chk_fail();
  return 0;
}
