#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_CODE_SIZE 65536

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage:\n%s source_file\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open %s\n", filename);
        return 1;
    }
    char code[MAX_CODE_SIZE];
    uint16_t code_len = fread(code, sizeof(char), MAX_CODE_SIZE, file);
    if (ferror(file)) {
        fclose(file);
        fprintf(stderr, "Failed reading source file\n");
        return 1;
    }
    fclose(file);

    uint16_t stack[MAX_CODE_SIZE], stack_ptr = 0;
    uint16_t targets[MAX_CODE_SIZE];

    uint8_t memory[65536] = {0};
    uint16_t memory_ptr = 0;

    for (uint16_t i = 0; i < code_len; i++)
    {
        char instruction = code[i];
        if (instruction == '[') {
            stack[stack_ptr++] = i;
        }
        if (instruction == ']') {
            if (stack_ptr == 0) {
                fprintf(stderr, "Unmatched ] at %d\n", i);
                return 1;
            } else {
                stack_ptr--;
                uint16_t target = stack[stack_ptr];
                targets[i] = target;
                targets[target] = i;
            }
        }
    }
    if (stack_ptr > 0) {
        fprintf(stderr, "At least one unmatched [\n");
        return 1;
    }
    char c;
    for (uint16_t code_ptr = 0; code_ptr < code_len; code_ptr++) {
        char ins = code[code_ptr];
        switch (ins) {
            case '+':
                memory[memory_ptr]++;
                break;
            case '-':
                memory[memory_ptr]--;
                break;
            case '<':
                if (memory_ptr == 0) return 1;
                memory_ptr--;
                break;
            case '>':
                if (memory_ptr == 65535) return 1;
                memory_ptr++;
                break;
            case ',':
                c = getchar();
                if (c != EOF) {
                    memory[memory_ptr] = c == '\n' ? 10 : c;
                }
                break;
            case '.':
                c = memory[memory_ptr];
                if (c == '\n') {
                    c = 10;
                }
                putchar(c);
                break;
            case '[':
                if (memory[memory_ptr] == 0) {
                    uint16_t target = targets[code_ptr];
                    code_ptr = target;
                }
                break;
            case ']':
                if (memory[memory_ptr] != 0) {
                    uint16_t target = targets[code_ptr];
                    code_ptr = target;
                }
                break;
        }
    }
    return 0;
}