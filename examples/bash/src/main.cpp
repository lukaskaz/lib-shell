#include "shell/interfaces/bash/shell.hpp"

#include <iostream>
#include <memory>

int32_t main(int32_t argc, [[maybe_unused]] char** argv)
{
    if (argc > 1)
    {
        try
        {
            using namespace shell::bash;
            auto iface = shell::Factory::create<Bash, config_t>({});
        }
        catch (std::exception& err)
        {
            std::cerr << "[ERROR] " << err.what() << '\n';
        }
    }
    return 0;
}
