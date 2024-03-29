#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth(char *buffer, unsigned int n) {
	buffer[strcspn(buffer, "\n")] = '\0';
	size_t len					  = strnlen(buffer, 32);

	if (len > 5) {
		if (0xffffffff != ptrace(PTRACE_TRACEME)) {

			int modulo = (buffer[3] ^ 0x1337) + 0x5eeded;
			int a	   = 0;

			while (a < len) {
				if (buffer[a] > 31) {

					modulo += (buffer[a] ^ modulo) % 0x539;
					a++;
				} else
					return 1;
			}
			// printf("RET %u", modulo);
			if (n == modulo)
				return 0;
		} else {
			puts("\033[32m.---------------------------.");
			puts("\033[31m| !! TAMPERING DETECTED !!  |");
			puts("\033[32m---------------------------");
			return 1;
		}
	} else
		return 1;
}

int main(int ac, char *av[]) {
	// int			 canary = *0x14;
	char		 buffer[32];
	unsigned int n;

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(buffer, 32, stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%u", &n);

	if (auth(buffer, n) != 0) {
		// if (canary == *0x14)
		// __stack_chk_fail();
		return 1;
	}

	puts("Authenticated!");
	system("/bin/sh");
	// if (canary ==  *0x14)
	// __stack_chk_fail();

	return 0;
}