#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <vector>

#ifdef DEBUG
#define Debug(x) x;
#define DebugPrint(x) \
    std::cout << (x) << std::endl
#endif // DEBUG

#ifdef NDEBUG
#define Debug(x) ;
#define DebugPrint(x) ;
#endif // NDEBUG

const std::string BINARY_DIRECTORY(std::string(get_current_dir_name()) + "/");