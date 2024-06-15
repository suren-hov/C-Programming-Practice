#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // for isalpha(), isalnum(), and tolower()
#include <stdbool.h>


bool isPalindrome(char* s) {
    int length = strlen(s);
    int index = 0;
    char* cleanText = (char*) malloc(length + 1);
    if (cleanText == NULL) {
        return false; // Check for memory allocation failure
    }

    // Clean the input string
    while (*s != '\0') {
        if (isalnum(*s)) { // Check if the character is alphanumeric
            cleanText[index++] = tolower(*s); // Convert to lower case for case insensitivity
        }
        s++;
    }
    cleanText[index] = '\0'; // Null-terminate the cleaned string

    // Allocate memory for the reversed text
    char* reversedText = (char*) malloc(index + 1);
    if (reversedText == NULL) {
        free(cleanText);
        return false; // Check for memory allocation failure
    }

    // Reverse the cleaned string
    int idx = 0;
    for (int i = index - 1; i >= 0; i--) {
        reversedText[idx++] = cleanText[i];
    }
    reversedText[idx] = '\0'; // Null-terminate the reversed string

    // Compare the cleaned text with the reversed text
    bool result = (strcmp(cleanText, reversedText) == 0);

    // Free the allocated memory
    free(cleanText);
    free(reversedText);

    return result;
}

// Example usage
int main() {
    char str[] = "0P";
    if (isPalindrome(str)) {
        printf("\"%s\" is a palindrome.\n", str);
    } else {
        printf("\"%s\" is not a palindrome.\n", str);
    }
    return 0;
}

