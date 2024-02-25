#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000 // Maximum length of the input text

// Function to read text from input file, reverse it, and write it to output file
void reverseAndWriteToFile(const char *inputFileName, const char *outputFileName) {
    // Open input file for reading
    FILE *inputFile = fopen(inputFileName, "r");
    // Open output file for writing
    FILE *outputFile = fopen(outputFileName, "w");

    // Check if files were opened successfully
    if (inputFile == NULL || outputFile == NULL) {
        printf("Error: Unable to open files.\n");
        exit(1);
    }

    // Array to store input text
    char inputText[MAX_LENGTH];
    // Read one line of text from input file
    if (fgets(inputText, MAX_LENGTH, inputFile) != NULL) {
        // Remove newline character, if present
        size_t len = strlen(inputText);
        if (len > 0 && inputText[len - 1] == '\n') {
            inputText[len - 1] = '\0';
            len--;
        }

        // Reverse the input text and write it to the output file
        for (int i = len - 1; i >= 0; i--) {
            fputc(inputText[i], outputFile); // Write characters in reverse order to output file
        }
    }

    // Close input and output files
    fclose(inputFile);
    fclose(outputFile);
}

// Main function
int main(int argc, char *argv[]) {
    // Check if correct number of command-line arguments is provided
    if (argc != 3) {
        printf("Usage: %s fileIn fileOut\n", argv[0]);
        return 1; // Exit program with error code 1
    }

    // Call function to reverse text and write it to output file
    reverseAndWriteToFile(argv[1], argv[2]);

    // Print a message indicating successful completion
    printf("Text reversed and written to %s\n", argv[2]);
    return 0; // Exit program with success code
}
