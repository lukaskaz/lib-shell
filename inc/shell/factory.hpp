#pragma once

#include "shell/interfaces/shell.hpp"

#include <memory>

namespace shell
{

class Factory
{
  public:
    template <typename T>
    static std::shared_ptr<ShellIf> create()
    {
        return std::shared_ptr<T>(new T());
    }
};

} // namespace shell
