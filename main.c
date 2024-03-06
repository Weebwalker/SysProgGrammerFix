#include "stdio.h"
#include <stdlib.h>
#include <locale.h>
#include "string.h"

#define INITIAL_BUFFER_SIZE 100
#define BUFFER_INCREMENT 100

int main (){

    setlocale(LC_ALL, "Bulgarian");

    FILE *filePointerReader, *filePointerWrite ;
    filePointerReader = fopen("C:\\Docs\\BPE C\\findandfix\\test.txt", "r");
    filePointerWrite = fopen("C:\\Docs\\BPE C\\findandfix\\output.txt", "w");

    if (filePointerReader == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char *buf = (char *)malloc(INITIAL_BUFFER_SIZE + 1);
    if (buf == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    size_t bufSize = INITIAL_BUFFER_SIZE;
    size_t bytesRead;
    int foundSentenceEnd = 0;

    int sentanceFound = 0;

    while (!foundSentenceEnd && (bytesRead = fread(buf, sizeof(char), bufSize, filePointerReader)) > 0) {
        buf[bytesRead] = '\0'; // Null-terminate the buffer

        // Search for the end of sentence in the buffer
        char *sentenceEnd = strstr(buf, ".");
        if (!sentenceEnd)
            sentenceEnd = strstr(buf, "!");
        if (!sentenceEnd)
            sentenceEnd = strstr(buf, "?");

        if (sentenceEnd) {
            // If sentence end found, write up to the end of the sentence to output file
            *sentenceEnd = '\0'; // Null-terminate at the end of the sentence
            fprintf(filePointerWrite, "%s", buf);
            foundSentenceEnd = 1;
        } else {
            // If sentence end not found, increase buffer size and read more characters
            bufSize += BUFFER_INCREMENT;
            buf = realloc(buf, bufSize + 1);
            if (buf == NULL) {
                printf("Memory reallocation failed\n");
                return 1;
            }
        }
    }

    fclose(filePointerReader);
    return 0;
}