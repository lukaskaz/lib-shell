#include "shellcommand.hpp"

#include <boost/process.hpp>

namespace shell
{

using shellParams = std::vector<std::string>;

BashCommand::BashCommand() :
    shellProg{boost::process::search_path(shellType).string()}
{}

int BashCommand::run(const std::string& cmd)
{
    return boost::process::system(shellProg, shellParams{"-c", cmd});
}

int BashCommand::run(const std::string& cmd, std::vector<std::string>& output)
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

} // namespace shell
