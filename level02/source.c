int main() { 
    char username[100];
    bzero(username, 12);

    char flag[48];
    bzero(flag, 5);

    char password[112];
    bzero(password, 12);

    FILE *file = fopen("/home/users/level03/.pass", "r");
    
    if (file == NULL) {
        fwrite("ERROR: failed to open password file\n", 36, 1, 2);
        exit(1);
    }

    fread(flag, 1, 41, file);
    int pos = strcspn(flag, "\n");
    flag[pos] = '\0';

    if (pos != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 36, 2);
        fwrite("ERROR: failed to read password file\n", 1, 36, 2);
        exit(1);
    }

    fclose(file);
    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\***************************************/");
    printf("--[ Username: ");

    fgets(username, 100, 0);
    username[strcspn(username, "\n")] = '\0';

    printf("--[ Password: ");
    fgets(password, 100, 0);
    password[strcspn(password, "\n")] = '\0';
    puts("*****************************************");
    
    if (strncmp(flag, password, 41) == 0) {
        printf("Greetings, %s!\n", username);
        system("/bin/sh");
    } else {
        printf(username);
        puts(" does not have access!");
        exit(1);
    }

    return 0;
}