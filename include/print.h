#pragma once

#include "main.h"

void usage();
void about();
void colored_out(const std::string& str, int color);
void info_out(int tape);
void command_out(int argc, char**& argv, int status, int tape);
//void colored_out_extra(const std::string& str);