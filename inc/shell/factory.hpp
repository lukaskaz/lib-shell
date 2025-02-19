#pragma once

#include "shell/interfaces/shell.hpp"

#include <memory>

namespace shell
{

class Factory
{
  public:
    template <typename T, typename C>
    static std::shared_ptr<ShellIf> create(const C& config)
    {
        return std::shared_ptr<T>(new T(config));
    }
};

} // namespace shell

