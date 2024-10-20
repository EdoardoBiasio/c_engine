#include "file.h"

optional_p(char) read_file_to_char(const char* file_path) {
    FILE* f = fopen(file_path, "r");
    if (!f) {
        berror("Unable to open file %s.", file_path);
        return optional_p_err(char, "Unable to open file.\n");
    }

    fseek(f, 0, SEEK_END);
    u32 len = ftell(f) + 1;
    rewind(f);

    managed_ptr(char) chars = managed_ptr_new_n(char, len);
    fread(managed_ptr_mem(char, chars), 1, len, f);
    (managed_ptr_mem(char, chars))[len - 1] = '\0';
    fclose(f);
    return optional_p_ok(char, chars);
}

#define PATH_SIZE_MAX 64

optional_p(char) get_file_path() {
    managed_ptr(char) ptr = managed_ptr_new_n(char, 64);
    if (getcwd(managed_ptr_mem(char, ptr), PATH_SIZE_MAX) != NULL) {
        return optional_p_ok(char, ptr);
    } else {
        return optional_p_err(char, "Unable to get current working directory");
    }
}
