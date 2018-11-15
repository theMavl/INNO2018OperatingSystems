#include <stdio.h>
#include <tkPort.h>

// Can't be bothered dealing with argv, so put dimension settings in compilation flags
// E.g.: gcc ex1.c -o ex1 -DRES_N=4 -DPROC_N=6 -DLINE_LEN=128
#ifndef RES_N
#define RES_N 3
#endif

#ifndef PROC_N
#define PROC_N 5
#endif

#ifndef LINE_LEN
#define LINE_LEN 8
#endif


int main(int argc, char *argv[]) {
    // For exercise it is not necessary to store all resources separately, just sum is enough
    int E = 0;
    int A = 0;
    int C[PROC_N] = {0};
    int R[PROC_N] = {0};

    BOOL finished[PROC_N] = {False};
    char *file_path;

    // Ability to read some other file name
    if (argc > 1)
        file_path = argv[1];
    else
        file_path = "input.txt";

    FILE *input = fopen(file_path, "r");
    if (input == NULL) {
        printf("Can't open file.\n");
        return -1;
    }

    char buffer[LINE_LEN];
    char *ptr;

    /*
     * All values are read by blocks separately:
     *
     * BLOCK 0 - E (existing resources)
     * BLOCK 1 - A (currently available processes)
     * BLOCK 2 - C (current allocation)
     * BLOCK 3 - R (requests)
     */
    for (int block = 0; block < 4; block++) {
        for (int line = 0; line < PROC_N; line++) {
            ptr = fgets(buffer, LINE_LEN, input);
            // Ignore empty lines
            while (ptr == NULL || strlen(buffer) <= 1)
                fgets(buffer, LINE_LEN, input);

            // Convert string to integers iteratively
            ptr = buffer;
            for (int row = 0; row < RES_N; row++) {
                switch (block) {
                    case 0:
                        E += (int) strtol(ptr, &ptr, 10);
                        break;
                    case 1:
                        A += (int) strtol(ptr, &ptr, 10);
                        break;
                    case 2:
                        C[line] += (int) strtol(ptr, &ptr, 10);
                        break;
                    case 3:
                        R[line] += (int) strtol(ptr, &ptr, 10);
                        break;
                }
            }
            // BLOCKS 0 and 1 have just one line, move to the next BLOCK
            if (block < 2)
                break;
        }
    }

    // Finding deadlocks
    BOOL found = True;
    while (found) {
        found = False;
        for (int i = 0; i < PROC_N; i++) {
            if (!finished[i] && R[i] <= A) {
                A += C[i];
                found = True;
                finished[i] = True;
                break;
            }
        }
    }

    found = False;
    for (int i = 0; i < PROC_N; i++)
        if (!finished[i]) {
            printf("Process %d is deadlocked\n", i + 1);
            found = True;
        }

    if (!found)
        printf("No deadlocks detected\n");

    return 0;
}