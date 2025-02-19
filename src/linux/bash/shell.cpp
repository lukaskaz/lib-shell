#include "shell/interfaces/linux/bash/shell.hpp"

#include <boost/process.hpp>

namespace shell::lnx::bash
{

using paramstype = std::vector<std::string>;

struct Shell::Handler
{
  public:
    Handler() : type{"bash"}, path{boost::process::search_path(type).string()}
    {}

    ~Handler()
    {}

    int32_t run(const std::string& cmd)
    {
        return boost::process::system(path, paramstype{"-c", cmd});
    }

    int32_t run(const std::string& cmd, std::vector<std::string>& output)
    {
        boost::process::ipstream ips;
        auto retcode = boost::process::system(path, paramstype{"-c", cmd},
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
    const std::string type;
    const std::string path;
};

Shell::Shell() : handler{std::make_unique<Handler>()}
{}
Shell::~Shell() = default;

int32_t Shell::run(const std::string& cmd)
{
    return handler->run(cmd);
}

int32_t Shell::run(const std::string& cmd, std::vector<std::string>& output)
{
    return handler->run(cmd, output);
}

} // namespace shell::lnx::bash
