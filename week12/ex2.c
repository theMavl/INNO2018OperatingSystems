#include <stdio.h>
#include <malloc.h>
#include <fcntl.h>
#include <tkPort.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int *files;
    int n_of_files = argc - 1;

    if (argc > 1) {
        BOOL append = False;

        if (strcmp("-a", argv[1]) == 0) {
            append = True;
            n_of_files--;
        }

        files = malloc(sizeof(int) * (argc - 1));

        int j = 0;
        for (int i = argc - n_of_files; i < argc; i++) {
            if (append)
                files[j] = open(argv[i], O_WRONLY | O_APPEND | O_CREAT);
            else
                files[j] = open(argv[i], O_WRONLY | O_CREAT | O_TRUNC);
            if (files[j] == -1) {
                printf("File %s can not be opened/created\n", argv[i]);
                n_of_files--;
            } else {
                j++;
            }
        }
    }


    char buffer[BUFFER_SIZE];

    size_t str_len = 0;

    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        printf("%s", buffer);
        str_len = strlen(buffer);
        for (int i = 0; i < n_of_files; i++)
            write(files[i], buffer, str_len);
    }

    for (int i = 0; i < n_of_files; i++)
        close(files[i]);
}