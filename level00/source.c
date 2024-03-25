int main() {
    int nb;

    puts("***********************************");
    puts("* 	     -Level00 -		  *");
    puts("***********************************");
    printf("Password:");
    scanf("%d", &nb);

    if (nb != 0x149c) {
        puts("\nAuthenticated!");
        system("/bin/sh");
    } else {
        puts("\nInvalid Password!");
        return 1;
    }

    return 0;
}