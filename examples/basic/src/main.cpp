#include "shellcommand.hpp"

#include <iostream>
#include <memory>

int main()
{
    try
    {
        auto cmdshandler = std::make_shared<BashCommand>();
    }
    catch (std::exception& err)
    {
        std::cerr << "[ERROR] " << err.what() << '\n';
    }
    return 0;
}
