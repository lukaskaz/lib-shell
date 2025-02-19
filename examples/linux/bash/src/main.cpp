#include "shell/interfaces/linux/bash/shell.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <ranges>

int32_t main(int32_t argc, [[maybe_unused]] char** argv)
{
    if (argc > 1)
    {
        try
        {
            using namespace shell::lnx::bash;
            auto iface = shell::Factory::create<Shell>();
            std::string command{argv[1]};
            std::vector<std::string> outputs;
            iface->run(command, outputs);

            std::cout << "Command: " << std::quoted(command) << " ";
            if (!outputs.empty())
            {
                std::cout << "returns:\n";
                std::ranges::for_each(outputs, [](const auto& out) {
                    static uint32_t cnt;
                    std::cout << "[output " << ++cnt << "] " << out << "\n";
                });
            }
            else
            {
                std::cout << "has no output\n";
            }
        }
        catch (std::exception& err)
        {
            std::cerr << "[ERROR] " << err.what() << '\n';
        }
    }
    return 0;
}
