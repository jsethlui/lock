
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <termios.h>
 
#define _U_ __attribute__((unused))     // to surpress warnings from system()

const int SIZE = 1024;
const int CAESAR_KEY = 25283;   // random prime number  25283
const char* DATA_FILE_NAME = "data.txt";
const char* DATA_OUTPUT_FILE_NAME = "output_data.txt";
const char PASS[SIZE] = "test";
const char* title_screen = "                    \
\n================================================ \
\n||                                            || \
\n||                  WELCOME                   || \
\n||                     TO                     || \
\n||                                            || \
\n||                 .--------.                 || \
\n||                / .------. \\                || \
\n||               / /        \\ \\               || \
\n||               | |        | |               || \
\n||              _| |________| |_              || \
\n||            .' |_|        |_| '.            || \
\n||            '._____ ____ _____.'            || \
\n||            |     .'____'.     |            || \
\n||            '.__.'.'    '.'.__.'            || \
\n||            '.__  |      |  __.'            || \
\n||            |   '.'.____.'.'   |            || \
\n||            '.____'.____.'____.'            || \
\n||            '.________________.'            || \
\n||                                            || \
\n||                    LOCK                    || \
\n||                                            || \
\n================================================ \
\n      Conveniently and safely store links,       \
\n         passwords, and sensitive data           \
\n             through user password               \
\n                 authentication                  ";

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
    fscanf(a_file, "%s", &encryption_flag_char);
    pclose(a_file);
    if (encryption_flag_char == 'A') {  // if success
        return EXIT_SUCCESS;
    } else {    // if error
        return EXIT_FAILURE;
    }
}

void encrypt_data() {
    // opening data.txt
    FILE* open_file = fopen(DATA_FILE_NAME, "r");
    if (open_file == NULL) {
        fprintf(stderr, "Error: cannot read data.txt");
        exit(EXIT_FAILURE);
    }

    // opening output_data.txt
    FILE* output_file = fopen(DATA_OUTPUT_FILE_NAME, "w");
    if (output_file == NULL) {
        printf(stderr, "Error: cannot read output_data.txt");
        exit(EXIT_FAILURE); 
    }

    char line[SIZE];
    while (fgets(line, sizeof(line), open_file)) {
        unsigned long size = strlen(line);
        for (int i = 0; i < size; i++) {
            line[i] += CAESAR_KEY;
            fprintf(output_file, "%c", line[i]);  // writing encrpyed char
        }
    }
    fclose(open_file);
    fclose(output_file);
}

void read_and_decrypt() {
    // opening output_data.txt
    FILE* output_file = fopen(DATA_OUTPUT_FILE_NAME, "r");
    if (output_file == NULL) {
        printf(stderr, "Error: cannot read output_data.txt");
        exit(EXIT_FAILURE); 
    }

    char line[SIZE];
    while (fgets(line, sizeof(line), output_file)) {
        printf("test\n");
        unsigned long size = strlen(line);
        for (int i = 0; i < size; i++) {
            line[i] -= CAESAR_KEY;
            //fprintf(output_file, "%c", line[i]);  // writing encrpyed char
            printf("%c", line[i]);
        }
    }
    fclose(output_file);
}

int main(int argc, char* argv[]) {
    int c;
    int emacs_flag, nano_flag, vim_flag, help_flag;

    int clear_screen = system("clear");
    printf("%s", title_screen);
    while (1) {
        int option_index;
        option_index = 0;
        static struct option long_options[] = {
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

    if (check_encryption_flag()) { // if data.txt is somehow unencrypted
        fprintf(stderr, "\nError: file is already somehow unencrypted\n");
        exit(EXIT_FAILURE);
    }

    char password[SIZE];
    printf("\n\nEnter Password: ");
    get_password(password);
    if (strcmp(password, PASS)) {  // if password is incorrect
        fprintf(stderr, "\nError: incorrect password\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 1) {
        printf("\n========================\n");
        read_and_decrypt(); // dcrypt before reading
        printf("\n========================\n");
    }

    // if password is correct, check options (if any)
    if (emacs_flag) {
        int open_with_emacs _U_ = system("emacs data.txt");
    }

    if (nano_flag) {
        int open_with_emacs _U_ = system("nano data.txt");
    }

    if (vim_flag) {
        int open_with_emacs _U_ = system("vim data.txt");
    }

    //int remove_data = system("rm data.txt");
    //int rename_output_data = system("mv output_data.txt data.txt");
    encrypt_data();     // encrypt before leaving program
    printf("\nExiting...\n");
    exit(EXIT_SUCCESS);
}