#include <stdio.h>
#include <string.h>

void set_msg(char **buffer) {
	char msg[1024];

	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(msg, 1024, stdin);

	strncpy(*buffer, msg, (int) *(*buffer + 180));
}

void set_username(char **buffer) {
	int	  i;
	char *username;

	puts(">: Enter your username");
	printf(">>: ");
	fgets(username, 128, stdin);
	i = 0;

	while (i <= 40 && username[i]) {
		(*buffer)[140 + i] = username[i];
		i++;
	}

	printf(">: Welcome, %s", *buffer + 140);
}

void handle_msg() {
	char buffer[192];

	buffer[180] = 140;

	set_username(&buffer);
	set_msg(&buffer);
	puts(">: Msg sent!");
}

int main() {
	puts("--------------------------------------------\n \
		|   ~Welcome to l33t-m$n ~    v1337        |\n \
        --------------------------------------------\n");

	handle_msg();
	return 0;
}