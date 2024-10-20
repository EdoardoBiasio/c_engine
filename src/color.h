#pragma once

#include "includes.h"

typedef struct color {
    f32 r, g, b, a;
} color;

static color RED = {1.0, 0.0, 0.0, 1.0};
static color GREEN = {0.0, 1.0, 0.0, 1.0};
static color BLUE = {0.0, 0.0, 1.0, 1.0};
static color WHITE = {1.0, 1.0, 1.0, 1.0};
static color BLACK = {0.0, 0.0, 0.0, 1.0};
static color MAGENTA = {1.0, 0.0, 1.0, 1.0};
static color YELLOW = {1.0, 1.0, 0.0, 1.0};
static color CYAN = {0.0, 1.0, 1.0, 1.0};
