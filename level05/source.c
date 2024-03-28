#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int	 i = 0;
	char buff[100];
	fgets(buff, 100, stdin);
	while (i < strlen(buff)) {
		if (buff[i] > 64 && buff[i] <= 90)
			buff[i] ^= 32;
		i++;
	}
	printf(buff);
	exit(0);
}
