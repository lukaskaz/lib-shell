#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace shell
{

class ShellIf
{
  public:
    ShellIf() = default;
    virtual ~ShellIf() = default;

    virtual int32_t run(const std::string&) = 0;
    virtual int32_t run(const std::string&, std::vector<std::string>&) = 0;
};

} // namespace shell
