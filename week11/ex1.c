#include <stdio.h>
#include <fcntl.h>
#include <tkPort.h>
#include <sys/mman.h>


int main() {
    int file = open("./ex1.txt", O_RDWR | O_CREAT);
    struct stat st;
    if (fstat(file, &st) != 0)
        return -1;

    __off_t file_size = st.st_size;

    char *hi = "This is a nice day";
    size_t hi_size = strlen(hi);

    if (ftruncate(file, hi_size) != 0)
        return -1;

    void *mapped = mmap(NULL, hi_size, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);

    memcpy(mapped, hi, hi_size);

    msync(mapped, file_size, MS_SYNC);
    munmap(mapped, file_size);
    return 0;
}