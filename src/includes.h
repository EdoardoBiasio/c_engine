#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <unistd.h>

#include <stb/stb_image.h>
typedef uint8_t u8; 
typedef uint16_t u16; 
typedef uint32_t u32; 
typedef uint64_t u64; 

typedef int8_t i8; 
typedef int16_t i16; 
typedef int32_t i32; 
typedef int64_t i64; 

typedef float f32;
typedef double f64;
typedef u8 b8;
typedef u32 b32;

#define UNUSED(x) (void) x
