#include "shell/interfaces/bash/shell.hpp"

#include <boost/process.hpp>

namespace shell::bash
{

using shellParams = std::vector<std::string>;

struct Bash::Handler
{
  public:
    Handler([[maybe_unused]] const config_t& config) :
        shellProg{boost::process::search_path(shellType).string()}
    {}

    ~Handler()
    {}

    int32_t run(const std::string& cmd)
    {
        return boost::process::system(shellProg, shellParams{"-c", cmd});
    }

    int32_t run(const std::string& cmd, std::vector<std::string>& output)
    {
        boost::process::ipstream ips;
        auto retcode = boost::process::system(shellProg, shellParams{"-c", cmd},
                                              boost::process::std_out > ips);
        if (!retcode)
        {
            std::string line;
            while (std::getline(ips, line))
            {
                output.push_back(std::move(line));
            }
        }
        return retcode;
    }

  private:
    const std::string shellType{"bash"};
    const std::string shellProg;
};

Bash::Bash(const config_t& config) : handler{std::make_unique<Handler>(config)}
{}
Bash::~Bash() = default;

int32_t Bash::run(const std::string& cmd)
{
    return handler->run(cmd);
}

int32_t Bash::run(const std::string& cmd, std::vector<std::string>& output)
{
    return handler->run(cmd, output);
}

} // namespace shell::bash
