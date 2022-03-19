#pragma once

#include "Constants.h"

namespace COAL
{

    void debug_print()
    {
        std::cout << std::endl;
    }

    template <typename First, typename... Strings>
    void debug_print(First arg, const Strings &...rest)
    {

#ifdef DEBUG

        std::cout << arg << " ";
        debug_print(rest...);

#endif
    }

}
