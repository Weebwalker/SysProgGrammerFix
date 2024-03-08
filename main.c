#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int main() {

    setlocale(LC_ALL, "Bulgarian");

    FILE* filePointerReader, * filePointerWrite;
    filePointerReader = fopen("D:\\SP\\SysProgGrammerFix\\test.txt", "r");
    filePointerWrite = fopen("D:\\SP\\SysProgGrammerFix\\output.txt", "w");

    if (filePointerReader == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Determine the size of the file
    fseek(filePointerReader, 0, SEEK_END);
    long fileSize = ftell(filePointerReader);
    rewind(filePointerReader);

    // Read the entire file into memory
    char* buf = (char*)malloc(fileSize + 1);
    if (buf == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    fread(buf, sizeof(char), fileSize, filePointerReader);
    buf[fileSize] = '\0'; // Null-terminate the buffer

    // Split the buffer into sentences and write them to the output file
    char *bufStart = buf;
    while (1) {
        // Search for the end of sentence in the buffer
        char *sentenceEnd = strpbrk(bufStart, ".!?");

        if (sentenceEnd) {
            // If sentence end found, write up to the end of the sentence to the output file
            *(sentenceEnd+1) = '\0'; // Null-terminate at the end of the sentence
            fprintf(filePointerWrite, "%s", bufStart); // Add a space after the sentence

            // Move the start of the buffer to the start of the next sentence
            bufStart = sentenceEnd + 2;
            while (*bufStart == ' ' || *bufStart == '\n') {
                bufStart++;
            }
        } else {
            // If sentence end not found, break the loop
            break;
        }
    }

    fclose(filePointerReader);
    fclose(filePointerWrite);
    free(buf);
    return 0;
}