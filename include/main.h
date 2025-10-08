#pragma once

#include <stdio.h>
#include "yaml-cpp/yaml.h"
#include <string.h>
#include <vector>
#include "get.h"
#include <stdlib.h>
#include "execute.h"

#ifdef WIN32
#define popen _popen
#define pclose _pclose
#elif __LINUX__
#define popen popen
#define pclose pclose
#endif