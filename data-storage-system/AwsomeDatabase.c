#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AwesomeDatabase.h"

#define MAX 15

int main(void)
{
    struct AwesomeDatabase adb;
    char command[MAX];

    printf("*-----------------------------*\n");
    printf("* Welcome To Awesome Database *\n");
    printf("*-----------------------------*\n");

    while (1)
    {
        printf("adb$: ");
        fgets(command, sizeof(command), stdin);
        printf("%s\n", command);
        command[strcspn(command, "\n")] = '\0'; // Remove trailing newline

        if (feof(stdin)) {
            printf("Bye...");
            // Close("Bye...");
        } else if (strlen(command) == 0) {
            continue;
        } else if (strcmp(command, "ADD") == 0) {
            // UserInputs();
        } else if (strcmp(command, "SEARCH") == 0) {
            // Search();
        } else if (strcmp(command, "EXIT") == 0) {
            printf("Good Bye!");
            // Close("Good Bye!");
        } else if (strcmp(command, "clear") == 0) {
            system("clear");
        } else {
            printf("Command not found\n");
        }
    }
    return 0;
}