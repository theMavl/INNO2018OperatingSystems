#include <stdio.h>
#include <fcntl.h>
#include <tkPort.h>
#include <sys/mman.h>


int main() {
    int file = open("./ex1.txt", O_RDWR | O_CREAT);
    int file_cpy = open("./ex1.memcpy.txt", O_RDWR | O_CREAT);

    struct stat st;
    if (fstat(file, &st) != 0)
        return -1;

    __off_t source_size = st.st_size;

    if (ftruncate(file_cpy, source_size) != 0)
        return -1;

    void *mapped = mmap(NULL, (size_t) source_size, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);
    void *mapped_cpy = mmap(NULL, (size_t) source_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_cpy, 0);

    memcpy(mapped_cpy, mapped, (size_t) source_size);

    msync(mapped_cpy, (size_t) source_size, MS_SYNC);
    munmap(mapped_cpy, (size_t) source_size);

    munmap(mapped, (size_t) source_size);
    return 0;
}