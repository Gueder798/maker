#pragma once

#include "main.h"

int execute_command(const std::string& command);
int execute(const std::vector<std::string>& task, std::string target, int depth = 0);