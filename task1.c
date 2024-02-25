#include <stdio.h>

void printBytes(void *ptr, int numBytes) {
    unsigned char *bytePtr = (unsigned char *)ptr; // Cast void pointer to unsigned char pointer

    printf("Starting at memory address %p:\n", ptr);
    for (int i = 0; i < numBytes; i++) {
        printf("%03d: %d\n", i + 1, bytePtr[i]); // Print decimal values of bytes with index
    }
}

int main() {
    unsigned char memory[4] = {10, 20, 30, 145};
    printBytes(memory, 4);

    return 0;
}