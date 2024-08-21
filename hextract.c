#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void extract_hex_values(const char *filename) {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "objdump -d %s", filename);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    char line[BUFFER_SIZE];
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Check if the line contains an instruction
        if (strstr(line, ":") != NULL) {
            char *token = strtok(line, "\t");
            token = strtok(NULL, "\t");
            if (token != NULL) {
                // Add \0x before each hex value and concatenate them
                char *hex_value = strtok(token, " ");
                while (hex_value != NULL) {
                    printf("\\x%s", hex_value);
                    hex_value = strtok(NULL, " ");
                }
            }
        }
    }

    pclose(fp);
    printf("\n"); 
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    extract_hex_values(argv[1]);
    return 0;
}

