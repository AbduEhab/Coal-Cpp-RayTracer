#pragma once

#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <array>

#ifdef _WIN32

#include <windows.h>
#include <direct.h>

const std::string BINARY_DIRECTORY(std::string(_getcwd(NULL, 0)) + '/');

//TCHAR buffer[MAX_PATH] = { 0 };
//GetModuleFileName(NULL, buffer, MAX_PATH);
//std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
//auto t = std::wstring(buffer).substr(0, pos);

#else

#include <unistd.h>
#include <filesystem>

const std::string BINARY_DIRECTORY(std::string((char*)std::filesystem::current_path().c_str()) + "/");
const std::string BINARY_DIRECTORY_TEST(std::string(get_current_dir_name()) + "/");

#endif

#define _unlikely [[UNLIKELY]]


template <typename Base, typename T>
inline constexpr int instanceof (const T *)
{
    return std::is_base_of<Base, T>::value;
}