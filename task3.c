#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// msString data type definition
typedef void * msString;

// Function prototypes for msString functions
msString msSetString(char *);
char *msGetString(msString);
void msCopy(msString *, msString);
void msConcatenate(msString *, msString);
long int msLength(msString);
int msCompare(msString, msString);
int msCompareString(msString, char *);
void msFree(msString);

// Function prototype for error handling function
static void msError(char *);

// Function to create a new msString from a standard C string
msString msSetString(char *str) {
    // Calculate length of input string
    long int length = strlen(str);
    
    // Allocate memory for msString
    msString newString = malloc(sizeof(long int) + length);

    if (newString == NULL) {
        msError("Memory allocation failed");
    }

    // Copy length to the beginning of the memory block
    memcpy(newString, &length, sizeof(long int));

    // Copy string data after the length
    memcpy(newString + sizeof(long int), str, length);

    return newString;
}

// Function to get a standard C string from an msString
char *msGetString(msString str) {
    // Pointer to the length stored at the beginning of the memory block
    long int *lengthPtr = (long int *)str;

    // Return pointer to string data after the length
    return (char *)(str + sizeof(long int));
}

// Function to copy one msString to another
void msCopy(msString *dest, msString src) {
    long int length = msLength(src);

    // Allocate memory for destination msString
    *dest = malloc(sizeof(long int) + length);

    if (*dest == NULL) {
        msError("Memory allocation failed");
    }

    // Copy length and string data
    memcpy(*dest, src, sizeof(long int) + length);
}

// Function to concatenate two msStrings
void msConcatenate(msString *dest, msString src) {
    long int destLength = msLength(*dest);
    long int srcLength = msLength(src);
    long int totalLength = destLength + srcLength;

    // Reallocate memory for destination msString to fit both strings
    msString newDest = realloc(*dest, sizeof(long int) + totalLength);

    if (newDest == NULL) {
        msError("Memory reallocation failed");
    }

    *dest = newDest;

    // Update length in the destination msString
    memcpy(*dest, &totalLength, sizeof(long int));

    // Copy source string data after the destination string data
    memcpy(*dest + sizeof(long int) + destLength, src + sizeof(long int), srcLength);
}

// Function to free memory allocated for an msString
void msFree(msString str) {
    free(str);
}

// Function to get the length of an msString
long int msLength(msString str) {
    // Read length from the beginning of the memory block
    long int length;
    memcpy(&length, str, sizeof(long int));
    return length;
}

// Function to compare two msStrings
int msCompare(msString str1, msString str2) {
    long int length1 = msLength(str1);
    long int length2 = msLength(str2);

    // Compare lengths
    if (length1 != length2) {
        return 1;
    }

    // Compare string data
    return memcmp(str1 + sizeof(long int), str2 + sizeof(long int), length1);
}

// Function to compare an msString with a standard C string
int msCompareString(msString str1, char *str2) {
    // Get length of msString
    long int length = msLength(str1);

    // Compare length with length of standard C string
    if (length != strlen(str2)) {
        return 1;
    }

    // Compare string data
    return memcmp(str1 + sizeof(long int), str2, length);
}

// Function to print an error message and exit the program
static void msError(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

// Main function
int main() {
    // Creating msString variables
    msString ms = msSetString("Hello");
    msString ms2 = msSetString(" World !");
    msString mscopy = NULL;

    // Displaying information about msString variables
    printf("String |%s| is %ld characters long (%p).\n", msGetString(ms), msLength(ms), (void *)ms);
    msCopy(&mscopy, ms);
    printf("Copied string |%s| is %ld characters long (%p).\n", msGetString(mscopy), msLength(mscopy), (void *)mscopy);

    // Comparing msString variables
    printf("Compare ms with mscopy: %d\n", msCompare(ms, mscopy));
    printf("Compare ms with ms2 : %d\n", msCompare(ms, ms2));
    printf("Compare ms with Hello : %d\n", msCompareString(ms, "Hello"));
    printf("Compare ms with HelloX: %d\n", msCompareString(ms, "HelloX"));
    printf("Compare ms with Hella : %d\n", msCompareString(ms, "Hella"));

    // Concatenating msString variables
    msConcatenate(&mscopy, ms2);
    printf("Concatenated string |%s| is %ld characters long (%p).\n", msGetString(mscopy), msLength(mscopy), (void *)mscopy);

    // Freeing memory allocated for msString variables
    msFree(ms);
    msFree(ms2);
    msFree(mscopy);

    return 0;
}
