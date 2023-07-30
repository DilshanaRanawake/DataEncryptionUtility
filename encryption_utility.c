/*
 * This file is part of Data Encryption Utility.
 *
 * Data Encryption Utility is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Data Encryption Utility is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Data Encryption Utility. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 1024

void encryptData(const char input[], const char key[], char output[], size_t inputSize) {// Function to encrypt data using a specified key
    size_t keyLength = strlen(key);

    for (size_t i = 0; i < inputSize; i++) {
        output[i] = input[i] ^ key[i % keyLength];
    }
}

void decryptData(const char input[], const char key[], char output[], size_t inputSize) {// Function to decrypt data using a specified key
    size_t keyLength = strlen(key);

    for (size_t i = 0; i < inputSize; i++) {
        output[i] = input[i] ^ key[i % keyLength];
    }
}

void handleError(const char* errorMessage) {// Function to handle errors
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

    fseek(inputFile, 0, SEEK_END);// Determine the size of the input file
    long inputSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char buffer[MAX_BUFFER_SIZE];
    char encrypted[MAX_BUFFER_SIZE];
    char decrypted[MAX_BUFFER_SIZE];

    if (strcmp(mode, "encrypt") == 0) {// Read the input file

        size_t bytesRead = fread(buffer, 1, inputSize, inputFile);
        if (bytesRead != (size_t)inputSize) {
            handleError("Error reading the input file.");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        encryptData(buffer, encryptionKey, encrypted, inputSize);
        fwrite(encrypted, 1, inputSize, outputFile);
    } else if (strcmp(mode, "decrypt") == 0) {// Read the input file to be decrypted

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
