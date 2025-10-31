#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "yaml-cpp/yaml.h"
#include "print.h"
#include "get.h"
#include "execute.h"

#ifdef _WIN32
#include <string.h>
#include <Windows.h>
#else
#include <strings>
#endif

//#define DEBUG