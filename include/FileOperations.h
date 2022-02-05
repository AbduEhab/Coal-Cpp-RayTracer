#pragma once

#include "Constants.h"

namespace COAL
{

    std::string read_file(const std::string &filepath)
    {
        DebugPrint(std::string("Reading file: ") + filepath);

        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);

        if (in)
        {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            if (size != -1)
            {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
            }
            else
            {
                // ToDO: handle failure to read from file
                std::cout << "-1" << std::endl;
            }
        }
        else
        {
            // ToDO: handle failure to open file
            std::cout << "-2" << std::endl;
        }

        return result;
    }

    int read_file(const std::string &filepath, const std::string &message)
    {
        std::ofstream out(filepath, std::ios::out | std::ios::binary);

        if (out)
        {
            if (message.size())
            {
                out << message << std::endl;

                out.close();
            }
            else
            { // handle empty string case

                return -1;
                DebugPrint("failed to Write to file (cannot write empty string)");
            }
        }
        else
        { // handle failure to open file

            return -2;
            DebugPrint("failed to Write to file (cannot open file)");
        }

        return 1;
    }
}
