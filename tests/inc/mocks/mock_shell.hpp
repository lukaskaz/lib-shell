#pragma once

#include "shellcommand.hpp"

#include <gmock/gmock.h>

class CommandsMock : public shell::ShellCommand
{
  public:
    MOCK_METHOD(int, run, (const std::string&), (override));
    MOCK_METHOD(int, run, (const std::string&, std::vector<std::string>&),
                (override));
};
