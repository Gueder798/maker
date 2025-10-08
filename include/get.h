#pragma once

#include "main.h"

std::vector<std::string> paser(YAML::Node config, const std::string& target);
int make(YAML::Node config, std::string target, bool pass);