#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (!output) {
        perror("Error opening output file");
        fclose(input);
        return 1;
    }

    unsigned char buffer[16];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), input)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            fprintf(output, "%02X", buffer[i]);
            if (i < bytesRead - 1) {
                fprintf(output, ",");
            }
        }
        fprintf(output, "\n");
    }

    fclose(input);
    fclose(output);
    return 0;
}