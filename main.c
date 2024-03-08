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

    // Apply the rules to the buffer
    for (int i = 0; i < fileSize; i++) {
        // Rule 1: Remove spaces before "..."
        if (buf[i] == ' ' && buf[i+1] == '.' && buf[i+2] == '.' && buf[i+3] == '.') {
            memmove(&buf[i], &buf[i+1], fileSize - i);
        }
            // Rule 2: Correct ".." or "...." to "..."
        else if (buf[i] == '.' && buf[i+1] == '.' && (buf[i+2] != '.' || (buf[i+2] == '.' && buf[i+3] == '.'))) {
            memmove(&buf[i+2], &buf[i+3], fileSize - i - 1);
        }
            // Rule 3: Remove space between punctuation marks
        else if ((buf[i] == '!' || buf[i] == '?' || buf[i] == '.') && buf[i+1] == ' ' && (buf[i+2] == '!' || buf[i+2] == '?' || buf[i+2] == '.')) {
            memmove(&buf[i+1], &buf[i+2], fileSize - i - 1);
        }
            // Rule 4: Remove space before punctuation mark and add space after punctuation mark
        else if ((buf[i] == ' ' && (buf[i+1] == '!' || buf[i+1] == '?' || buf[i+1] == '.')) || ((buf[i] == '!' || buf[i] == '?' || buf[i] == '.') && buf[i+1] != ' ')) {
            memmove(&buf[i], &buf[i+1], fileSize - i);
            memmove(&buf[i+2], &buf[i+1], fileSize - i - 1);
            buf[i+1] = ' ';
        }
            // Rule 5: Remove comma before or after punctuation mark
        else if ((buf[i] == ',' && (buf[i+1] == '!' || buf[i+1] == '?' || buf[i+1] == '.')) || ((buf[i] == '!' || buf[i] == '?' || buf[i] == '.') && buf[i+1] == ',')) {
            memmove(&buf[i], &buf[i+1], fileSize - i);
        }
            // Rule 6: Add space after comma
        else if (buf[i] == ',' && buf[i+1] != ' ') {
            memmove(&buf[i+2], &buf[i+1], fileSize - i - 1);
            buf[i+1] = ' ';
        }
//            // Rule 7: Remove comma after specific words
//        else if (strncmp(&buf[i], "Например,", 9) == 0 || strncmp(&buf[i], "Всъщност,", 9) == 0 || /* add other words here */) {
//            memmove(&buf[i+strlen("Например")], &buf[i+strlen("Например,")], fileSize - i - strlen("Например"));
//        }
//            // Rule 8: Add comma after specific words
//        else if (strncmp(&buf[i], "Казват", 6) == 0 || strncmp(&buf[i], "Напротив", 8) == 0 || /* add other words here */) {
//            memmove(&buf[i+strlen("Казват")+1], &buf[i+strlen("Казват")], fileSize - i - strlen("Казват"));
//            buf[i+strlen("Казват")] = ',';
//        }
    }

    // Write the modified buffer to the output file
    fprintf(filePointerWrite, "%s", buf);

    fclose(filePointerReader);
    fclose(filePointerWrite);
    free(buf);
    return 0;
}
