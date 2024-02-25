#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Task 1: Read memory in bytes
void printBytes(void *ptr, int numBytes) {
    // Cast pointer to unsigned char pointer to access individual bytes
    unsigned char *bytePtr = (unsigned char *)ptr;

    // Print memory address header
    printf("Starting at memory address %p:\n", ptr);

    // Move variable declaration outside of the loop initializer
    int i;
    for (i = 0; i < numBytes; i++) {
        printf("%03d: %d\n", i + 1, bytePtr[i]);
    }
}




// Task 2: Read data from one file and output it to another
void reverseFile(char *fileIn, char *fileOut) {
    // Open input file for reading and output file for writing
    FILE *inputFile = fopen(fileIn, "r");
    FILE *outputFile = fopen(fileOut, "w");
    if (inputFile == NULL || outputFile == NULL) {
        fprintf(stderr, "Error: Unable to open files.\n");
        return;
    }

    // Determine input file size
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    // Allocate buffer to hold file contents
    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return;
    }

    // Read file contents into buffer and null-terminate
    fread(buffer, 1, fileSize, inputFile);
    buffer[fileSize] = '\0';

    // Move variable declaration outside of the loop initializer
    int i;
    for (i = fileSize - 1; i >= 0; i--) {
        fputc(buffer[i], outputFile);
    }

    // Free allocated memory and close files
    free(buffer);
    fclose(inputFile);
    fclose(outputFile);
}


// Task 3: msString module
typedef void * msString;

// Function prototypes for msString module
extern msString  msSetString     (char *);
extern char     *msGetString     (msString);
extern void      msCopy          (msString *, msString);
extern void      msConcatenate   (msString *, msString);
extern long int  msLength        (msString);
extern int       msCompare       (msString, msString);
extern int       msCompareString (msString, char *);
static void      msError         (char *);

// Function to create an msString from a standard C string
msString msSetString(char *str) {
    long int length = strlen(str);
    msString newString = malloc(sizeof(long int) + length);

    if (newString == NULL) {
        msError("Memory allocation failed");
    }

    // Copy length and string data to allocated memory
    memcpy(newString, &length, sizeof(long int));
    memcpy(newString + sizeof(long int), str, length);

    return newString;
}

// Function to get a standard C string from an msString
char *msGetString(msString str) {
    return (char *)(str + sizeof(long int));
}

// Function to copy one msString to another
void msCopy(msString *dest, msString src) {
    long int length = msLength(src);
    *dest = malloc(sizeof(long int) + length);

    if (*dest == NULL) {
        msError("Memory allocation failed");
    }

    // Copy length and string data to destination
    memcpy(*dest, src, sizeof(long int) + length);
}

// Function to concatenate two msStrings
void msConcatenate(msString *dest, msString src) {
    long int destLength = msLength(*dest);
    long int srcLength = msLength(src);
    long int totalLength = destLength + srcLength;

    msString newDest = realloc(*dest, sizeof(long int) + totalLength);

    if (newDest == NULL) {
        msError("Memory reallocation failed");
    }

    // Update length and concatenate string data
    *dest = newDest;
    memcpy(*dest, &totalLength, sizeof(long int));
    memcpy(*dest + sizeof(long int) + destLength, src + sizeof(long int), srcLength);
}

// Function to free memory allocated for an msString
void msFree(msString str) {
    free(str);
}

// Function to get the length of an msString
long int msLength(msString str) {
    long int length;
    memcpy(&length, str, sizeof(long int));
    return length;
}

// Function to compare two msStrings
int msCompare(msString str1, msString str2) {
    long int length1 = msLength(str1);
    long int length2 = msLength(str2);

    if (length1 != length2) {
        return 1;
    }

    return memcmp(str1 + sizeof(long int), str2 + sizeof(long int), length1);
}

// Function to compare an msString with a standard C string
int msCompareString(msString str1, char *str2) {
    long int length = msLength(str1);

    if (length != strlen(str2)) {
        return 1;
    }

    return memcmp(str1 + sizeof(long int), str2, length);
}

// Function to print an error message and exit the program
static void msError(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

// Main function for testing all tasks
int main() {
    // Task 1: Testing printBytes function
    int num = 145;
    printBytes(&num, sizeof(int));
    printf("\n");

    // Task 2: Testing reverseFile function
    reverseFile("input.txt", "output.txt");
    printf("File has been reversed. Check 'output.txt' for result.\n\n");

    // Task 3: Testing msString module
    msString ms = msSetString("Hello");
    msString ms2 = msSetString(" World !");
    msString mscopy = NULL;

    // Display information about msString variables
    printf("String |%s| is %ld characters long (%p).\n", msGetString(ms), msLength(ms), (void *)ms);
    msCopy(&mscopy, ms);
    printf("Copied string |%s| is %ld characters long (%p).\n", msGetString(mscopy), msLength(mscopy), (void *)mscopy);

    // Comparing msString variables
    printf("Compare ms with mscopy: %d\n", msCompare(ms, mscopy));
    printf("Compare ms with ms2 : %d\n", msCompare(ms, ms2));
    printf("Compare ms with Hello : %d\n", msCompareString(ms, "Hello"));
    printf("Compare ms with HelloX: %d\n", msCompareString(ms, "HelloX"));
    printf("Compare ms with Hella : %d\n", msCompareString(ms, "Hella"));

    // Freeing memory allocated for msString variables
    msFree(ms);
    msFree(ms2);
    msFree(mscopy);

    return 0;
}

