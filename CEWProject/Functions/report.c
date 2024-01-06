#include <stdio.h>
#define MAX_BUFFER_SIZE 5000

  // Function to read the contents of a file and print it
void printFileContents(const char *filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[bytesRead] = '\0';  // Null-terminate the string

    fclose(file);

    printf("Contents of %s:\n%s\n", filename, buffer);
}
