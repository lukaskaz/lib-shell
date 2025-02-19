#pragma once

#include "shell/factory.hpp"

namespace shell::bash
{

using config_t = std::tuple<>;

class Bash : public ShellIf
{
  public:
    ~Bash();
    int32_t run(const std::string&) override;
    int32_t run(const std::string&, std::vector<std::string>&) override;

  private:
    friend class shell::Factory;
    Bash(const config_t&);

    struct Handler;
    std::unique_ptr<Handler> handler;
};

} // namespace shell::bash

