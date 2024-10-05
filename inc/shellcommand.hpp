#pragma once

#include <string>
#include <vector>

namespace shell
{

class ShellCommand
{
  public:
    ShellCommand() = default;
    virtual ~ShellCommand() = default;

    ShellCommand(const ShellCommand&) = delete;

    virtual int run(const std::string&) = 0;
    virtual int run(const std::string&, std::vector<std::string>&) = 0;
};

class BashCommand : public ShellCommand
{
  public:
    BashCommand();

    int run(const std::string&) override;
    int run(const std::string&, std::vector<std::string>&) override;

  private:
    const std::string shellType{"bash"};
    const std::string shellProg;
};

} // namespace shell
