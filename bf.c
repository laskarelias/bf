#include <stdio.h>

#define SIZE 30000

int main(int argc, char** argv) {
    
    char mem[SIZE] = {0};
    char* p = mem;
    char c;
    long int stack[SIZE] = {0};
    int pos = 0;
    int br = 0;

    if (argc != 2) {
        printf("Usage: bf [FILE]\n");
        return 0;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        printf("Could not open file %s\n", argv[1]);
        return -1;
    }

    while ((c = fgetc(f)) != 255) { // != EOF
        switch (c) {
            case '+': ++*p; break;
            case '-': --*p; break;
            case '>': if (p - mem < SIZE) ++p;
                      else return -1;
                      break;
            case '<': if (p - mem > 0) --p;  
                      else return -1; 
                      break;
            case '.': printf("%c", *p); fflush(stdout); break;
            case ',': *p = getchar(); break;
            case '[': 
                if (*p != 0) stack[pos++] = ftell(f);
                else {
                    br = 1; 
                    while (br != 0) {
                        c = fgetc(f);
                        if (c == '[') br++;
                        if (c == ']') br--;
                    }
                }
                break;
            case ']': 
                if (*p != 0) fseek(f, stack[pos - 1], SEEK_SET);
                else --pos;
                break;
            default: break;
        }
    }

    return 0;
}
