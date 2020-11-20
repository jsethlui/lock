#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <termios.h>

const int SIZE = 1024;
const int CAESAR_KEY = 25283;   // random prime number
const char* PASSWORDS_FILE_NAME = "data.txt";

void get_password(char password[]) {
    static struct termios old_termios, new_termios;
    int i = 0;
    int c;

    // saving settings of actual terminal
    tcgetattr(STDIN_FILENO, &old_termios);

    // do not echo characters
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ECHO);

    // setting as new terminal setting
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    // getting password
    while ((c = getchar()) != '\n' && c != EOF && i < SIZE) {
        password[i++] = c;
    }
    password[i] = '\0';

    // restore to old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

int check_encryption_flag() {
    char encryption_flag_char;
    FILE* a_file = popen("head -1 data.txt", "r");
    fscanf(a_file, "%c", &encryption_flag_char);
    pclose(a_file);
    // printf("Char: %s\n", &encryption_flag_char);
    if (encryption_flag_char == 'A') {  // if success
        printf("%c\n", encryption_flag_char);
        printf("sucess\n");
        return EXIT_SUCCESS;
    } else {    // if error
        return EXIT_FAILURE;
    }
}

void read_and_encrypt() {
    FILE* a_file = fopen(PASSWORDS_FILE_NAME, "r");
    if (a_file == NULL) {
        fprintf(stderr, "Error: cannot read data.txt");
        exit(EXIT_FAILURE);
    }
    char line[SIZE];
    while (fgets(line, sizeof(line), a_file)) {
        printf("%s", line);     // line is of type string
        int i;
        for (i = 0; i < strlen(line); i++) {
            // printf("%c ", line[i]);
            line[i] += CAESAR_KEY;
            printf("%c" , line[i]);
        }
    }
    fclose(a_file);
}

void decrypt_and_decrypt() {

}

int main(int argc, char* argv[]) {
    if (check_encryption_flag()) { // if data.txt is somehow unencrypted
        fprintf(stderr, "Error: file is already somehow unencrypted\n");
        printf("Forcing data.txt to be encrypted\n");
        exit(EXIT_FAILURE);
    }

    int c;
    int emacs_flag, nano_flag, vim_flag, help_flag, all_flag;
//    int clear_screen = system("clear");

    // check if flag in data.txt is encrypted
    read_and_encrypt();

    while (1) {
        int option_index;
        option_index = 0;
        static struct option long_options[] = {
            {"all", no_argument, NULL, 'a'},
            {"emacs", no_argument, NULL, 'e'},
            {"nano", no_argument, NULL, 'n'},
            {"vim", no_argument, NULL, 'v'},
            {"help", no_argument, NULL, 'h' },
            {0, 0, 0, 0}
        };

        c = getopt_long (argc, argv, "", long_options, &option_index);
        if (c == -1) {
            break;
        }

        switch (c) {
            case 'a':
                all_flag = 1;
                break;
            case 'e':
                emacs_flag = 1;
                break;
            case 'n':
                nano_flag = 1;
                break;
            case 'v':
                vim_flag = 1;
                break;
            case 'h':
                help_flag = 1;
                break;
            case '?':
                fprintf(stderr, "Error: incorrect usage\n");
                exit(EXIT_FAILURE);
            default:
                abort();
            }
    }

    // char password[SIZE];
    // printf("Password: ");
    // get_password(password);
    // printf("%s", password);

    if (all_flag) {

    }

    if (emacs_flag) {
        int open_with_emacs = system("emacs data.txt");
    }

    if (nano_flag) {
        int open_with_emacs = system("nano data.txt");
    }

    if (vim_flag) {
        int open_with_emacs = system("vim data.txt");
    }

    if (all_flag) {
        printf("all flag\n");
    }

    exit(EXIT_SUCCESS);
}