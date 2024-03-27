char *a_user_name = "";

int verify_user_name(char *buffer) {
	puts("verifying username....\n");
	return strncmp(a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *buffer) { return strncmp(buffer, "admin", 5); }

int main() {
	int	 nb = 0;
	char buffer[64];

	bzero(buffer, 16);

	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(a_user_name, 256, 0);

	nb = verify_user_name();
	if (nb == 0) {
		puts("Enter Password: ");
		fgets(buffer, 100, 0);

		nb = verify_user_pass(buffer);
		puts("nope, incorrect password...\n");

		return 1;
	} else {
		puts("nope, incorrect username...\n");
		return 1;
	}

	return 0;
}
