#include "disk_reader.h"
namespace UTSample {

size_t DiskReader::read(char* buffer, size_t offset, size_t count) {
    FILE *file_ptr = fopen(file, "r");
    if (NULL == file_ptr) {
        std::cout << "file not found" << std::endl;
        return 0;
    }

    fseek(file_ptr, offset, SEEK_SET);
    size_t read_size = fread((void*)buffer, 1, count, file_ptr);
    fclose(file_ptr);
    return read_size;
}

uint_64 DiskReader::get_total_size() {
    FILE *file_ptr = fopen(file, "r");
    if (NULL == file_ptr) {
        return 0;
    }
    fseek(file_ptr, 0L, SEEK_END);
    fpos_t pos;
    fgetpos(file_ptr, &pos);
    fclose(file_ptr);
    return (uint_64)pos.__pos;
}

}

