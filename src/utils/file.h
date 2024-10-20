#pragma once

#include "memory.h"
#include "optional.h"

optional_p(char) read_file_to_char(const char* file_path);
optional_p(char) get_file_path();
