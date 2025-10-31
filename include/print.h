#pragma once

#include "main.h"

enum class Color {
    BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, RESET
};

void usage();
void about();
void coloredout(const std::string& str, int color);
void infoout(int tape);