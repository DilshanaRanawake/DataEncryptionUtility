#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

// Function to encrypt data using the specified key
void encryptData(const char input[], const char key[], char output[], size_t inputSize) {
    size_t keyLength = strlen(key);

    for (size_t i = 0; i < inputSize; i++) {
        output[i] = input[i] ^ key[i % keyLength];
    }
}

// Function to decrypt data using the specified key
void decryptData(const char input[], const char key[], char output[], size_t inputSize) {
    size_t keyLength = strlen(key);

    for (size_t i = 0; i < inputSize; i++) {
        output[i] = input[i] ^ key[i % keyLength];
    }
}

// Function to handle errors and display an error message
void handleError(const char* errorMessage) {
    printf("Error: %s\n", errorMessage);
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        handleError("Insufficient arguments. Usage: encryption_utility [encrypt/decrypt] [input_file] [output_file] [encryption_key]");
        return 1;
    }

    char* mode = argv[1];
    char* inputFileName = argv[2];
    char* outputFileName = argv[3];
    char* encryptionKey = argv[4];

    FILE* inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL) {
        handleError("Failed to open the input file.");
        return 1;
    }

    FILE* outputFile = fopen(outputFileName, "wb");
    if (outputFile == NULL) {
        handleError("Failed to create the output file.");
        fclose(inputFile);
        return 1;
    }

    // Determine the size of the input file
    fseek(inputFile, 0, SEEK_END);
    long inputSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char buffer[MAX_BUFFER_SIZE];
    char encrypted[MAX_BUFFER_SIZE];
    char decrypted[MAX_BUFFER_SIZE];

    if (strcmp(mode, "encrypt") == 0) {
        // Read the entire input file content
        size_t bytesRead = fread(buffer, 1, inputSize, inputFile);
        if (bytesRead != (size_t)inputSize) {
            handleError("Error reading the input file.");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        encryptData(buffer, encryptionKey, encrypted, inputSize);
        fwrite(encrypted, 1, inputSize, outputFile);
    } else if (strcmp(mode, "decrypt") == 0) {
        // Read the entire input file content
        size_t bytesRead = fread(buffer, 1, inputSize, inputFile);
        if (bytesRead != (size_t)inputSize) {
            handleError("Error reading the input file.");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        decryptData(buffer, encryptionKey, decrypted, inputSize);
        fwrite(decrypted, 1, inputSize, outputFile);
    } else {
        handleError("Invalid mode specified. Please use 'encrypt' or 'decrypt'.");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Operation completed successfully.\n");

    return 0;
}
