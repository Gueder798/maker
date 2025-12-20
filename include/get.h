#pragma once

#include "main.h"

YAML::Node yml_paser();
std::string command_paser(std::string command);
std::string cleaner(const std::string& input);
std::vector<std::string> get_task(std::string target);