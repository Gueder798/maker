#pragma once

#include <stdio.h>
#include "yaml-cpp/yaml.h"
#ifdef WIN32
#include <string.h>
#else 
#include <strings.h>
#endif
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
#define stricmp strcasecmp
#endif