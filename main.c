//Author: Kyle Watson
//Course: CS 3503- Comp Org & Arch
//Assignment: A2 - Data Representation & Mapping
//Language: C Programming
//Topics:Direct mapping, signed representations


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

typedef struct {
    char function_name[50];
    char input[100];
    char expected[200];
} TestCase;



int main() {
    FILE *f = fopen("a2_test.txt", "r");
    if (!f) {
        perror("Failed to open file");
        return 1;
    }

    char line[512];
    int test_num = 0, passed = 0,failed = 0;

    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '#' || strlen(line) <= 1)continue;

        TestCase t;
        char input2[100];
        int count = sscanf(line, "%s %s %s", t.function_name, t.input, t.expected);

        char actual[256] = "";

        if (strcmp(t.function_name, "oct_to_bin") == 0) {
            oct_to_bin(t.input, actual);
        } else if (strcmp(t.function_name, "oct_to_hex") == 0) {
            oct_to_hex(t.input, actual);
        } else if (strcmp(t.function_name, "hex_to_bin") == 0) {
            hex_to_bin(t.input, actual);
        } else if (strcmp(t.function_name, "to_sign_magnitude") == 0) {
            int32_t n = atoi(t.input);
            to_sign_magnitude(n, actual);
        } else if (strcmp(t.function_name, "to_ones_complement") == 0) {
            int32_t n = atoi(t.input);
            to_ones_complement(n, actual);
        } else if (strcmp(t.function_name, "to_twos_complement") == 0) {
            int32_t n = atoi(t.input);
            to_twos_complement(n, actual);
        } else {
            continue;
        }

        test_num++;
        if (strcmp(actual, t.expected) == 0) {
            printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [PASS]\n",
                   test_num, t.function_name, t.input, t.expected, actual);
            passed++;
        } else {
            printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [FAIL]\n",
                   test_num, t.function_name, t.input, t.expected, actual);
            failed++;
        }
    }
    fclose(f);
    printf("\nSummary: %d/%d tests passed\n", passed, test_num);
    return 0;
}