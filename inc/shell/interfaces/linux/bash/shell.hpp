#pragma once

#include "shell/factory.hpp"

namespace shell::lnx::bash
{

class Shell : public ShellIf
{
  public:
    ~Shell();
    int32_t run(const std::string&) override;
    int32_t run(const std::string&, std::vector<std::string>&) override;

  private:
    friend class shell::Factory;
    Shell();

    struct Handler;
    std::unique_ptr<Handler> handler;
};

} // namespace shell::lnx::bash
