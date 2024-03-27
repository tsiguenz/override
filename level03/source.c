void decrypt(int offset) {
	int	 canary		= *0x14;
	char buffer[17] = {0x33617c7d, 0x7b66737e, 0x67667360, 0x757c7d51, '\0'};

	int len = strlen(buffer);
	int i	= 0;

	while (len < i) {
		buffer[i] += offset;
		i++;
	}

	if (strncmp(buffer, "Congratulations!", 17) == 0) {
		system("/bin/sh");
	}

	if (canary != *0x14) {
		__stack_chk_fail(void);
	}
}

void test(int input, int nb) {
	int diff = nb - input;

	if (diff > 21) {
		decrypt(rand());
		return;
	}

	register int eax = diff << 2;
	eax += 0x80489f0;
	void (*fct)(void) = (void (*)()) eax;
	fct();

	decrypt(diff);
}

int main() {
	srand(time(NULL));

	puts("***********************************");
	puts("*		level03		**");
	puts("***********************************");
	printf("Password:");

	int nb;
	scanf("%d" & nb) test(nb, 0x1337d00d);

	return 0;
}
