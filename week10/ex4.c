#include <stdio.h>
#include <dirent.h>
#include <tkPort.h>

#define I_NODES_MAX 100
#define FILES_PER_NODE_MAX 100
#define FILE_NAME_CHARS_MAX 256

typedef struct {
    __ino_t i_node;
    char files[FILES_PER_NODE_MAX][FILE_NAME_CHARS_MAX];
    int files_n;
} i_node_files;

int main() {
    DIR *dirp = opendir("tmp");

    i_node_files *i_nodes = malloc(I_NODES_MAX * sizeof(i_node_files));
    int len = 0;

    if (dirp == NULL) { return (1); }
    struct dirent *dp;
    __ino_t i_node;
    BOOL exists;

    while ((dp = readdir(dirp)) != NULL) {
        i_node = dp->d_ino;
        exists = False;
        for (int i = 0; i < len; i++) {
            if (i_nodes[i].i_node == i_node) {
                if (i_nodes[i].files_n < FILES_PER_NODE_MAX) {
                    strcpy(i_nodes[i].files[i_nodes[i].files_n], dp->d_name);
                    i_nodes[i].files_n++;
                } else {
                    printf("I-Node %li reached its files limit - some files will not be shown. Increase FILES_PER_NODE_MAX.",
                           i_node);
                }
                exists = True;
                break;
            }
        }
        if (!exists) {
            if (len < I_NODES_MAX) {
                i_nodes[len].i_node = i_node;
                strcpy(i_nodes[len].files[i_nodes[len].files_n], dp->d_name);
                i_nodes[len].files_n = 1;
                len++;
            } else {
                printf("Directory has reached I-Node limit. Some nodes will not be shown. Increase I_NODES_MAX.");
            }
        }

    }

    for (int i = 0; i < len; i++) {
        if (i_nodes[i].files_n > 1) {
            printf("%li: ", i_nodes[i].i_node);
            for (int j = 0; j < i_nodes[i].files_n; j++) {
                printf("%s ", i_nodes[i].files[j]);
                fflush(stdout);
            }
            printf("\n");
        }
    }
    return 0;
}